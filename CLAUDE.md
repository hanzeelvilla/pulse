# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project

**PULSE** — an ESP32 Arduino project built with PlatformIO.

## Commands

```bash
# Build
pio run

# Build and upload to connected ESP32
pio run --target upload

# Open serial monitor (115200 baud)
pio device monitor

# Build, upload, and monitor in one step
pio run --target upload && pio device monitor

# Run tests (PlatformIO Unit Testing)
pio test

# Run a single test environment
pio test -e esp32dev

# Clean build artifacts
pio run --target clean
```

## Architecture

- `src/main.cpp` — entry point; standard Arduino `setup()` / `loop()` structure
- `include/` — project-wide header files shared across source files
- `lib/` — private project libraries; each library lives in its own subdirectory (e.g., `lib/MyLib/MyLib.h`)
- `test/` — PlatformIO unit tests
- `platformio.ini` — board/framework config; target is `esp32dev` (Espressif32, Arduino framework, 115200 baud)

Libraries declared in `platformio.ini` under `lib_deps` are auto-fetched by PlatformIO. The Library Dependency Finder (LDF) also auto-detects libraries by scanning `#include` directives in source files.
