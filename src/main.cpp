#include "config.h"
#include "SpotifyClient.h"
#include <Arduino.h>
#include <WiFi.h>

SpotifyClient spotify(SPOTIFY_CLIENT_ID, SPOTIFY_CLIENT_SECRET, SPOTIFY_REFRESH_TOKEN);

void setupWifi();

void setup() {
  Serial.begin(115200);
  setupWifi();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi disconnected, reconnecting...");
    setupWifi();
  }

  static unsigned long lastUpdate = 0;
  const long interval = 5000; // Poll every 5 seconds

  if (millis() - lastUpdate > interval) {
    lastUpdate = millis();
    
    if (WiFi.status() == WL_CONNECTED) {
      TrackInfo track = spotify.getCurrentTrack();

      if (track.isPlaying) {
        Serial.println("\n==========================");
        Serial.printf("Now Playing: %s\n", track.name.c_str());
        Serial.printf("Artist(s):   %s\n", track.artist.c_str());
        Serial.printf("Album:       %s\n", track.album.c_str());
        Serial.println("==========================");
      } else {
        Serial.println("[Info] No active track found on Spotify.");
      }
    } else {
      Serial.println("[Error] WiFi Disconnected.");
    }
  }
}

void setupWifi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to " WIFI_SSID "...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
}
