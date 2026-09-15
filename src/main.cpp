#include <Arduino.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include "config.h"
#include "NetworkManager.h"

MD_Parola display = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

void showMessage(const char *message) {
  display.displayClear();
  display.displayText(message, PA_CENTER, 50, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
}

void setup() {
  Serial.begin(115200);
  display.begin();
  display.setIntensity(5);

  showMessage("Connecting to WiFi...");
  bool connected = NetworkManager::begin(WIFI_SSID, WIFI_PASSWORD);
  showMessage(connected ? "Hello World" : "WiFi connection failed");
}

void loop() {
  static bool wasConnected = true;
  bool connected = NetworkManager::ensureConnected();

  if (connected != wasConnected) {
    showMessage(connected ? "Hello World" : "WiFi disconnected");
    wasConnected = connected;
  }

  if (display.displayAnimate()) {
    display.displayReset();
  }
}
