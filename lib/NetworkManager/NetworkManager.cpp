#include "NetworkManager.h"
#include <Arduino.h>
#include <WiFi.h>

namespace {
  const int MAX_CONNECT_RETRIES = 20;
  const unsigned long RETRY_DELAY_MS = 500;
  const unsigned long RECONNECT_INTERVAL_MS = 10000;
  unsigned long lastReconnectAttempt = 0;
  const char *storedSsid = nullptr;
  const char *storedPassword = nullptr;
}

bool NetworkManager::begin(const char *ssid, const char *password) {
  storedSsid = ssid;
  storedPassword = password;

  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.print(ssid);
  Serial.print("...");

  int retryCount = 0;
  while (WiFi.status() != WL_CONNECTED && retryCount < MAX_CONNECT_RETRIES) {
    delay(RETRY_DELAY_MS);
    Serial.print(".");
    retryCount++;
  }

  Serial.println();
  if (WiFi.status() == WL_CONNECTED) {
    Serial.print("WiFi connected, IP address: ");
    Serial.println(WiFi.localIP());
    return true;
  }

  Serial.println("WiFi connection failed");
  return false;
}

bool NetworkManager::ensureConnected() {
  if (WiFi.status() == WL_CONNECTED) {
    return true;
  }

  unsigned long now = millis();
  if (now - lastReconnectAttempt < RECONNECT_INTERVAL_MS) {
    return false;
  }
  lastReconnectAttempt = now;

  Serial.println("WiFi disconnected, reconnecting...");
  return begin(storedSsid, storedPassword);
}
