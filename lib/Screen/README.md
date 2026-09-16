# Screen

Base interface for anything that can be shown on the shared `MD_Parola`
display. Defines only the render lifecycle (`start`/`update`) — it does not
own the display, decide which screen is active, or manage a collection of
screens. Screen switching/registry is Phase 7.

## API

- `Screen::start()` — called once when the screen becomes active; clears
  the display and (re)starts rendering its current content.
- `Screen::update()` — called every `loop()`; pumps per-frame work (e.g.
  animation). Must not block.

## Usage

```cpp
class MyScreen : public Screen {
public:
  void start() override { /* clear + render initial content */ }
  void update() override { /* pump animation; called every loop() */ }
};
```

See `lib/FreeTextScreen` for a real implementation.

## Requirements

None — this library has no dependency on `MD_Parola` or any hardware; that's
up to each concrete implementation.
