# DisplayManager

A modular abstraction layer for driving MAX7219 LED matrix displays on the ESP32.

## Features

- **Hardware Abstraction:** Encapsulates the low-level setup of the `MD_Parola` and `MD_MAX72xx` libraries.
- **Smooth Scrolling:** Manages text scrolling animations automatically via an `update()` method that can be called repeatedly in the main loop.
- **Track Formatting:** Provides dedicated methods like `showTrack(song, artist)` to easily format and display "Song - Artist" strings.
- **Non-Blocking:** Designed to be called quickly in the `loop()` without using `delay()`, ensuring animations remain fluid.

## Dependencies

- `MD_Parola`: For text animations and effects.
- `MD_MAX72XX`: Low-level hardware driver for the MAX7219 matrix.
- `SPI`: Built-in Arduino library for SPI communication.

## Usage Example

```cpp
#include "DisplayManager.h"

// Initialize: Hardware Type, CS Pin, Number of Matrices
DisplayManager display(MD_MAX72XX::FC16_HW, 5, 4);

void setup() {
  display.begin();

  // Show a static text at startup
  display.showText("READY");
}

void loop() {
  // Must be called as fast as possible in the main loop for smooth animations
  display.update();

  // Example of changing text dynamically
  // display.showTrack("Never Gonna Give You Up", "Rick Astley");
}
```
