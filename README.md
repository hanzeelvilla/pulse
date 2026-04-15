# PULSE

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

1. Go to the [Spotify Developer Dashboard](https://developer.spotify.com/dashboard/applications)

- Create a new App and obtain your `Client ID` and `Client Secret`.
- Click on Edit Settings and add the following Redirect URI: `http://127.0.0.1:8888/callback`
- Save the changes at the bottom of the page.

> [!WARNING]
> The redirect URI can't be `localhost`, for more information about what redirect URIs are valid and how to set them up, see [Redirect URIs](https://developer.spotify.com/documentation/web-api/concepts/redirect_uri).

2. Obtain an Authorization Code
   - Paste the following URL into your browser, replacing `YOUR_CLIENT_ID` with your actual Client ID:

   ```text
   https://accounts.spotify.com/authorize?client_id=YOUR_CLIENT_ID&response_type=code&redirect_uri=http://127.0.0.1:8888/callback&scope=user-read-currently-playing
   ```

   - Log in and click Agree.
   - The browser will redirect you to an address starting with `http://127.0.0.1:8888/callback?code=...`
   - Copy the code following the `code=` parameter (ignore the _"Page not found"_ error).

3. Generate the Refresh Token
   - Open your terminal and run the following command to exchange your authorization code for a `Refresh Token`. Replace the placeholders with your actual data:

   Windows

   ```bash
   curl.exe -X POST "https://accounts.spotify.com/api/token" -H "Content-Type: application/x-www-form-urlencoded" -d "grant_type=authorization_code" -d "code=YOUR_AUTHORIZATION_CODE" -d "redirect_uri=http://127.0.0.1:8888/callback" -d "client_id=YOUR_CLIENT_ID" -d "client_secret=YOUR_CLIENT_SECRET"
   ```

   Linux/Mac:

   ````bash
      curl -X POST "https://accounts.spotify.com/api/token" \
     -H "Content-Type: application/x-www-form-urlencoded" \
     -d "grant_type=authorization_code" \
     -d "code=YOUR_AUTHORIZATION_CODE" \
     -d "redirect_uri=http://
   ```bash
      curl -X POST "https://accounts.spotify.com/api/token" \
     -H "Content-Type: application/x-www-form-urlencoded" \
     -d "grant_type=authorization_code" \
     -d "code=YOUR_AUTHORIZATION_CODE" \
     -d "redirect_uri=http://127.0.0.1:8888/callback" \
     -d "client_id=YOUR_CLIENT_ID" \
     -d "client_secret=YOUR_CLIENT_SECRET"
   ````

   - The response will contain a `"refresh_token"`. Save this key; it does not expire and will allow the ESP32 to request new access tokens automatically.

4. Clone the repository:

   ```bash
   git clone https://github.com/hanzeelvilla/pulse
   cd pulse
   ```

5. Open the project in VS Code (with the PlatformIO extension) or any editor with PlatformIO CLI support.

6. Copy the template:

   ```bash
   cp include/config.h.template include/config.h
   ```

7. Open `include/config.h` and fill in your credentials:

   ```cpp
   #define WIFI_SSID     "your_wifi_ssid"
   #define WIFI_PASSWORD "your_wifi_pswd"
   #define SPOTIFY_CLIENT_ID "your_spotify_client_id"
   #define SPOTIFY_CLIENT_SECRET "your_spotify_client_secret"
   ```

8. Build and upload to the ESP32:

   ```bash
   pio run --target upload
   ```

9. Open the serial monitor to verify output (115200 baud):

   ```bash
   pio device monitor
   ```
