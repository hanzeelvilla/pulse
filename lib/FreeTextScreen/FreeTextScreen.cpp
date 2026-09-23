#include "FreeTextScreen.h"

FreeTextScreen::FreeTextScreen(MD_Parola &display) : display_(display), text_("") {}

void FreeTextScreen::setText(const char *message) {
  text_ = message;
  start();
}

void FreeTextScreen::start() {
  display_.displayClear();
  display_.displayText(text_.c_str(), PA_CENTER, 50, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
}

void FreeTextScreen::update() {
  if (display_.displayAnimate()) {
    display_.displayReset();
  }
}
