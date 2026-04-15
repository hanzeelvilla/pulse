#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <Arduino.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

class DisplayManager {
public:
  DisplayManager(MD_MAX72XX::moduleType_t hardwareType, uint8_t csPin, uint8_t maxDevices);
  
  void begin();
  void update();
  void clear();
  void showText(const String& text);
  void showTrack(const String& song, const String& artist);

private:
  MD_Parola _display;
  String _currentText;
  bool _isScrolling;
};

#endif
