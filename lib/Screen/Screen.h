#ifndef SCREEN_H
#define SCREEN_H

// Base interface every display screen implements. A screen owns its own
// content/state and knows how to render and animate itself on the shared
// MD_Parola display; main.cpp drives it through this interface.
class Screen {
public:
  virtual ~Screen() {}

  // Called once when the screen becomes active. Clears the display and
  // (re)starts rendering the screen's current content.
  virtual void start() = 0;

  // Called every loop() iteration. Pumps per-frame work (e.g.
  // MD_Parola::displayAnimate()). Must not block.
  virtual void update() = 0;
};

#endif // SCREEN_H
