# NetworkManager

Wi-Fi connection handling for the ESP32: initial connect, auto-reconnect, and
serial status logging. No networking features beyond connectivity (no
HTTP/WebSocket/mDNS) — that's later phases.

## API

- `NetworkManager::begin(ssid, password)` — blocking connect on boot.
  Retries up to 20 times (500ms apart, ~10s max), then logs the result over
  Serial, including the IP address on success. Returns `true` on success.
- `NetworkManager::ensureConnected()` — call every `loop()`. Returns the
  current connection state. While disconnected, attempts a reconnect (same
  blocking retry burst as `begin()`, reusing the last credentials) at most
  once every 10 seconds.

## Usage

```cpp
#include "NetworkManager.h"
#include "config.h"

void setup() {
  Serial.begin(115200);
  bool connected = NetworkManager::begin(WIFI_SSID, WIFI_PASSWORD);
}

void loop() {
  bool connected = NetworkManager::ensureConnected();
}
```

## Requirements

Caller must provide `WIFI_SSID` and `WIFI_PASSWORD` (see
`include/config.h.template`) — the library itself has no dependency on the
project's `config.h`.
