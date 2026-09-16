#ifndef FREE_TEXT_SCREEN_H
#define FREE_TEXT_SCREEN_H

#include <MD_Parola.h>
#include "Screen.h"

// Free Text screen: renders a single scrolling line of text on the shared
// MD_Parola display. First concrete Screen implementation.
class FreeTextScreen : public Screen {
public:
  // display: the shared MD_Parola instance owned by main.cpp. This screen
  // only reads/writes it, never owns or constructs it.
  explicit FreeTextScreen(MD_Parola &display);

  // Sets the message to show and immediately (re)starts the scroll
  // animation from the right edge. Safe to call repeatedly to change text.
  void setText(const char *message);

  // Screen interface: (re)starts scrolling the currently set message.
  void start() override;

  // Screen interface: pumps the scroll animation; call every loop().
  void update() override;

private:
  MD_Parola &display_;
  const char *text_;
};

#endif // FREE_TEXT_SCREEN_H
