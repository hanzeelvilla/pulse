#include <Arduino.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include "config.h"
#include "NetworkManager.h"
#include "FreeTextScreen.h"
#include "BackendClient.h"

MD_Parola display = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
FreeTextScreen freeTextScreen(display);

void onSetFreeText(const char *text) {
  freeTextScreen.setText(text);
}

void setup() {
  Serial.begin(115200);
  display.begin();
  display.setIntensity(5);

  freeTextScreen.setText("Connecting to WiFi...");
  bool connected = NetworkManager::begin(WIFI_SSID, WIFI_PASSWORD);
  freeTextScreen.setText(connected ? "Hello World" : "WiFi connection failed");

  if (connected) {
    BackendClient::begin(BACKEND_HOST, BACKEND_PORT, onSetFreeText);
  }
}

void loop() {
  static bool wasConnected = true;
  bool connected = NetworkManager::ensureConnected();

  if (connected != wasConnected) {
    freeTextScreen.setText(connected ? "Hello World" : "WiFi disconnected");
    wasConnected = connected;
  }

  if (connected) {
    BackendClient::loop();
  }

  freeTextScreen.update();
}
