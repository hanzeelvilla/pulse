# PULSE

## Overview

Pulse is an LED matrix display (MAX7219, driven by an ESP32) that you can control from a web interface — connect to your device and switch between different content screens on the fly.

This repository holds the **firmware** running on the ESP32. The web interface lives in a separate repository: [pulse-frontend](https://github.com/hanzeelvilla/pulse-frontend).

## Hardware

- Esp32
- USB cable to connect the ESP32
- MAX7219 Matrix Display

## Wiring

| **MAX7219** | **ESP32 PIN** |
| :---------: | :-----------: |
|     VCC     |      5V       |
|     GND     |      GND      |
|     DIN     |    GPIO 23    |
|     CS      |    GPIO 5     |
|     CLK     |    GPIO 18    |

## Prerequisites

- [PlatformIO](https://platformio.org/install/ide?install=vscode) — install via VS Code extension or the PlatformIO CLI

## Installation and Setup

1. Clone the repository:

   ```bash
   git clone https://github.com/hanzeelvilla/pulse
   cd pulse
   ```

2. Open the project in VS Code (with the PlatformIO extension) or any editor with PlatformIO CLI support.

3. Build and upload to the ESP32:

   ```bash
   pio run --target upload
   ```

4. Open the serial monitor to verify output (115200 baud):

   ```bash
   pio device monitor
   ```

## Planned Screens

- [ ] Free text
- [ ] Currently playing Spotify track
- [ ] Clock
- [ ] Timer / Stopwatch
- [ ] Pomodoro
- [ ] Days until payday
- [ ] GitHub contributions graph
- [ ] Web interface to connect to the display and switch between screens
