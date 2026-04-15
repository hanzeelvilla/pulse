#include "config.h"
#include "SpotifyClient.h"
#include "DisplayManager.h"
#include <Arduino.h>
#include <WiFi.h>

// Spotify client and Display manager
SpotifyClient spotify(SPOTIFY_CLIENT_ID, SPOTIFY_CLIENT_SECRET, SPOTIFY_REFRESH_TOKEN);
DisplayManager displayManager(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

// Global shared variables for FreeRTOS
TrackInfo sharedTrack;
SemaphoreHandle_t trackMutex;

// Function prototypes
void setupWifi();
void printTrackInfo(const TrackInfo& track);
void spotifyTask(void *pvParameters);

void setup() {
  Serial.begin(115200);

  displayManager.begin();

  setupWifi();

  // Create Mutex for thread-safe access to sharedTrack
  trackMutex = xSemaphoreCreateMutex();

  // Create Spotify Polling Task on Core 0
  // Core 1 (default) handles loop() and display updates
  if (trackMutex != NULL) {
    xTaskCreatePinnedToCore(
      spotifyTask,   /* Task function */
      "SpotifyTask", /* Name of task */
      8192,          /* Stack size in words */
      NULL,          /* Task input parameter */
      1,             /* Priority of the task */
      NULL,          /* Task handle */
      0              /* Core where the task should run (Core 0) */
    );
  }
}

void loop() {
  // Always update display as fast as possible for smooth scrolling
  displayManager.update();

  static TrackInfo lastProcessedTrack;
  TrackInfo currentTrack;

  // Safely read the latest track info from the background task
  if (xSemaphoreTake(trackMutex, (TickType_t)10) == pdTRUE) {
    currentTrack = sharedTrack;
    xSemaphoreGive(trackMutex);

    // Update display only if track info changed
    if (currentTrack.name != lastProcessedTrack.name || currentTrack.isPlaying != lastProcessedTrack.isPlaying) {
      if (currentTrack.isPlaying) {
        printTrackInfo(currentTrack);
        displayManager.showTrack(currentTrack.name, currentTrack.artist);
      } else {
        Serial.println("[Info] No active track found on Spotify.");
        displayManager.showText("PAUSED");
      }
      lastProcessedTrack = currentTrack;
    }
  }

  // Handle WiFi reconnection in main loop if necessary
  if (WiFi.status() != WL_CONNECTED) {
    // Note: This could also block briefly, but the background task handles the main networking.
    // In a fully robust system, wifi management could also be its own task.
    static unsigned long lastWifiCheck = 0;
    if (millis() - lastWifiCheck > 10000) {
      Serial.println("WiFi disconnected, reconnecting...");
      setupWifi();
      lastWifiCheck = millis();
    }
  }
}

// Background Task: Polls Spotify every 5 seconds
void spotifyTask(void *pvParameters) {
  for (;;) {
    if (WiFi.status() == WL_CONNECTED) {
      TrackInfo track = spotify.getCurrentTrack();

      // Update the shared variable safely using the mutex
      if (xSemaphoreTake(trackMutex, portMAX_DELAY) == pdTRUE) {
        sharedTrack = track;
        xSemaphoreGive(trackMutex);
      }
    } else {
      Serial.println("[Error] SpotifyTask: WiFi Disconnected.");
    }

    // Wait 5 seconds before next poll (vTaskDelay doesn't block other tasks/cores)
    vTaskDelay(pdMS_TO_TICKS(5000));
  }
}

void setupWifi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to " WIFI_SSID "...");

  int retryCount = 0;
  while (WiFi.status() != WL_CONNECTED && retryCount < 20) {
    delay(500);
    Serial.print(".");
    retryCount++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("");
    Serial.println("WiFi connected");
  } else {
    Serial.println("\nWiFi connection failed");
  }
}

void printTrackInfo(const TrackInfo& track) {
  Serial.println("\n==========================");
  Serial.printf("Now Playing: %s\n", track.name.c_str());
  Serial.printf("Artist(s):   %s\n", track.artist.c_str());
  Serial.printf("Album:       %s\n", track.album.c_str());
  Serial.println("==========================");
}
