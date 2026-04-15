# Project: PULSE

PULSE is an ESP32-powered device that displays the currently playing Spotify track on a MAX7219 LED matrix display. It uses the Spotify Web API to fetch track information and the `MD_Parola` library to handle display animations.

## Architecture and Main Technologies

- **Microcontroller:** ESP32 (Expressif ESP32-DevKitC or similar).
- **Framework:** Arduino framework via [PlatformIO](https://platformio.org/).
- **Display:** MAX7219 8x8 LED Matrix (daisy-chained).
- **Network:** WiFi for internet connectivity.
- **Spotify API:** Uses the Spotify Web API for "Currently Playing" track info.
- **Key Libraries:**
  - `MD_Parola`: For text animations and display management.
  - `MD_MAX72XX`: Low-level MAX7219 driver.
  - `ArduinoJson`: For parsing Spotify API JSON responses.
  - `HTTPClient` / `WiFiClientSecure`: For making HTTPS requests to Spotify.

## Directory Structure

- `src/main.cpp`: Main application logic, including WiFi setup, polling Spotify, and updating the display.
- `lib/SpotifyClient/`: Custom library for interacting with the Spotify API (authentication, fetching track info).
- `include/config.h`: Local configuration for WiFi, Spotify credentials, and hardware pins (template in `include/config.h.template`).
- `platformio.ini`: Project configuration, library dependencies, and build settings.

## Building and Running

### Prerequisites

- [PlatformIO Core](https://docs.platformio.org/en/latest/core/index.html) or [PlatformIO IDE for VS Code](https://platformio.org/platformio-ide).

### Configuration

1. Copy the configuration template:

    ```bash
    cp include/config.h.template include/config.h
    ```

2. Edit `include/config.h` and provide your:
    - WiFi SSID and Password.
    - Spotify Client ID and Client Secret (from the [Spotify Developer Dashboard](https://developer.spotify.com/dashboard/)).
    - Spotify Refresh Token (follow the instructions in `README.md` to obtain this).

### Build and Upload

To build and upload the firmware to your ESP32:

```bash
pio run --target upload
```

### Serial Monitoring

To view debug output and verify the connection (115200 baud):

```bash
pio device monitor
```

## Development Conventions

- **Code Style:** Follows standard Arduino/C++ conventions.
- **Authentication:** Uses a refresh token to automatically manage access tokens for the Spotify API.
- **Hardware Configuration:** Pin definitions and display settings are centralized in `include/config.h`.
- **API Interaction:** The `SpotifyClient` class handles all communication with Spotify, keeping `main.cpp` focused on the display logic and overall control flow.
- **Polling:** The application polls the Spotify API every 5 seconds (configurable in `src/main.cpp`).
