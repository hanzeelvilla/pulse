#include "DisplayManager.h"

DisplayManager::DisplayManager(MD_MAX72XX::moduleType_t hardwareType, uint8_t csPin, uint8_t maxDevices) 
  : _display(hardwareType, csPin, maxDevices), _currentText(""), _isScrolling(false) {}

void DisplayManager::begin() {
  _display.begin();
  _display.setIntensity(5); // Brillo predeterminado
  _display.displayClear();
}

void DisplayManager::update() {
  if (_display.displayAnimate()) {
    if (_isScrolling) {
      _display.displayReset(); // Reiniciar el scroll si terminó
    }
  }
}

void DisplayManager::clear() {
  _display.displayClear();
  _currentText = "";
}

void DisplayManager::showText(const String& text) {
  if (_currentText == text) return;
  
  _currentText = text;
  _isScrolling = false;
  _display.displayClear();
  _display.displayText(_currentText.c_str(), PA_CENTER, 0, 0, PA_PRINT, PA_NO_EFFECT);
}

void DisplayManager::showTrack(const String& song, const String& artist) {
  String formattedText = song + "-" + artist;
  
  if (_currentText == formattedText) return;

  _currentText = formattedText;
  _display.displayClear();

  // Activate scrolling if text exceeds display width
  if (_currentText.length() > 8) {
    _isScrolling = true;
    _display.displayText(_currentText.c_str(), PA_LEFT, 50, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
  } else {
    _isScrolling = false;
    _display.displayText(_currentText.c_str(), PA_CENTER, 0, 0, PA_PRINT, PA_NO_EFFECT);
  }
}
