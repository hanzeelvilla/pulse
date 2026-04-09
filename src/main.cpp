#include "config.h"
#include "Spotify.h"

SpotifyClient spotify(SPOTIFY_CLIENT_ID, SPOTIFY_CLIENT_SECRET);

void setupWifi();

void setup() {
  Serial.begin(115200);
  setupWifi();
  spotify.authenticate();
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi disconnected, reconnecting...");
    setupWifi();
  }

  String token = spotify.getToken();

  if (token != "") {
    Serial.println("Token OK: " + token.substring(0, 20) + "...");
  } else {
    Serial.println("Failed to obtain Spotify token.");
  }

  delay(5000);
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
