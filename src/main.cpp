#include <Arduino.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include "config.h"

MD_Parola display = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

void setup() {
  display.begin();
  display.setIntensity(5);
  display.displayClear();
  display.displayText("Hello World", PA_CENTER, 50, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
}

void loop() {
  if (display.displayAnimate()) {
    display.displayReset();
  }
}
