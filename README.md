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
