# SpotifyClient

A lightweight Arduino library for the ESP32 to interact with the Spotify Web API.

## Features

- **OAuth 2.0 Integration:** Automatically refreshes the Spotify access token using a provided refresh token.
- **Currently Playing Info:** Fetches the currently playing track, artist(s), album, and play/pause status.
- **JSON Parsing:** Uses `ArduinoJson` to efficiently parse the Spotify API responses.
- **Error Handling:** Gracefully handles token expiration (HTTP 401) and empty states (HTTP 204).

## Dependencies

- `WiFiClientSecure`: Built-in ESP32 library for HTTPS requests.
- `HTTPClient`: Built-in ESP32 library for making HTTP GET/POST requests.
- `ArduinoJson` (v6 or v7): For parsing the JSON payloads from the Spotify Web API.

## Usage Example

```cpp
#include <WiFi.h>
#include "SpotifyClient.h"

// Initialize with your credentials
SpotifyClient spotify("YOUR_CLIENT_ID", "YOUR_CLIENT_SECRET", "YOUR_REFRESH_TOKEN");

void setup() {
  Serial.begin(115200);

  // Connect to WiFi here...

  TrackInfo track = spotify.getCurrentTrack();

  if (track.isPlaying) {
    Serial.printf("Now playing: %s by %s\n", track.name.c_str(), track.artist.c_str());
  } else {
    Serial.println("Playback is paused or nothing is playing.");
  }
}

void loop() {
  // Polling logic here...
}
```
