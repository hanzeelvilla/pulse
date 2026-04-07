# PULSE

## Hardware

- Esp32

## Installation & Setup

### Prerequisites

- [PlatformIO](https://platformio.org/install) — install via VS Code extension or the PlatformIO CLI
- A USB cable to connect the ESP32

### Steps

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

## WiFi Configuration

Credentials are kept out of version control using a local config file.

1. Copy the template:

   ```bash
   cp include/config.h.template include/config.h
   ```

2. Open `include/config.h` and fill in your credentials:

   ```cpp
   #define WIFI_SSID     "your_wifi_ssid"
   #define WIFI_PASSWORD "your_wifi_pswd"
   ```

3. Include it in your source files where needed:

   ```cpp
   #include "config.h"
   ```

>[!NOTE]
> `include/config.h` is gitignored — your credentials will never be committed.