#include "config.h"

void setupWifi();

void setup() {
  Serial.begin(115200);
  setupWifi();
}

void loop() {
  if(WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi disconnected, reconnecting...");
    setupWifi();
  }

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  delay(1000);
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