# FreeTextScreen

The Free Text screen — the first concrete `Screen` implementation. Renders a
single scrolling line of text on the shared `MD_Parola` display. No message
queue, no persistence, no backend hookup — receiving text from a backend is
Phase 4/5; switching away from this screen is Phase 7.

## API

- `FreeTextScreen(MD_Parola &display)` — wraps a display the caller already
  owns and has called `begin()`/`setIntensity()` on.
- `setText(message)` — sets and immediately starts scrolling `message`.
- `start()` (from `Screen`) — (re)starts scrolling the currently set text.
- `update()` (from `Screen`) — call every `loop()`; pumps the scroll
  animation.

## Usage

```cpp
#include "FreeTextScreen.h"

MD_Parola display = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
FreeTextScreen freeTextScreen(display);

void setup() {
  display.begin();
  display.setIntensity(5);
  freeTextScreen.setText("Hello World");
}

void loop() {
  freeTextScreen.update();
}
```

## Requirements

Caller must construct and initialize the `MD_Parola` display (`begin()` +
`setIntensity()`) and pass it in by reference — this library never owns or
constructs it. Depends on `lib/Screen` (base interface) and the
`MD_Parola`/`MD_MAX72XX` libraries already declared in `platformio.ini`.
