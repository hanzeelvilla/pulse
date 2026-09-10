# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Language Policy

All code, comments, commit messages, documentation, and any other text written into this project must be in **English**, regardless of the language the request or prompt was written in.

## Project

Pulse is the **firmware** for an ESP32-driven MAX7219 LED matrix display. The long-term goal (not yet implemented) is to control the display's content from a separate web frontend ([pulse-frontend](https://github.com/hanzeelvilla/pulse-frontend)) that connects to the device and switches between multiple "screens": free text, currently-playing Spotify track, clock, timer/stopwatch, pomodoro, days until payday, GitHub contributions graph, etc. (see README.md's "Planned Screens").

The codebase was recently reset to a minimal "Hello World" scroll sketch as a clean starting point for this rebuild — there is currently no WiFi, networking, or multi-screen logic. Expect the architecture (WiFi connectivity, a display/screen abstraction, an API server or client to talk to the frontend) to be built up from here.

## Build System

This is a **PlatformIO** project (not the Arduino IDE) targeting an `esp32dev` board with the Arduino framework. There is no `.ino` file — the entry point is `src/main.cpp`.

Common commands (run from the project root; requires the PlatformIO CLI or the VS Code PlatformIO extension):

```bash
pio run                    # build
pio run --target upload    # build and flash to the ESP32
pio device monitor         # serial monitor (115200 baud)
pio run --target clean     # clean build artifacts
```

There are no automated tests or linting configured (`test/` only contains PlatformIO's boilerplate placeholder).

## Architecture

- `src/main.cpp` — entry point (`setup()`/`loop()`). Owns the single `MD_Parola` display instance.
- `include/config.h` — hardware configuration only (`HARDWARE_TYPE`, `MAX_DEVICES`, `CLK_PIN`/`DATA_PIN`/`CS_PIN`). This file is real config but **is gitignored**; `include/config.h.template` is the tracked template new setups copy from. Keep both in sync when hardware constants change.
- `lib/` — currently empty of custom code (PlatformIO auto-links anything placed here into `src/main.cpp` via the Library Dependency Finder). Previous iterations had `SpotifyClient` and `DisplayManager` libraries here; as new screens/features are built, prefer reintroducing self-contained libraries under `lib/<Name>/` (with a matching `.h`/`.cpp`/`README.md`) over growing `main.cpp` into a monolith.
- Display driver: `MD_Parola` + `MD_MAX72XX` (majicdesigns libraries), SPI-driven MAX7219 modules — not addressable RGB (no FastLED/NeoPixel). Wiring and pin mapping are documented in `README.md`.

## Notes

- `include/config.h` is gitignored because past versions stored live WiFi/Spotify credentials there. The current version has no secrets, but keep any future credentials out of source control and add corresponding placeholders to `config.h.template`.
