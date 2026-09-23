# BackendClient

Socket.IO client that connects the ESP32 to the NestJS Gateway (pulse-backend)
on the `/device` namespace and dispatches the events it receives. First
concrete piece of Phase 4 (firmware ↔ backend end-to-end loop).

## Protocol contract

- Namespace: `/device` (`BACKEND_DEVICE_NAMESPACE` in `BackendClient.h`)
- Event: `display-text` (`EVENT_DISPLAY_TEXT` in `BackendClient.h`), payload
  is a single string — the text to display. Emitted by the Gateway's
  `DeviceGateway.broadcastText()` whenever a frontend client sends
  `set-free-text` on the `/frontend` namespace (see pulse-backend).

These two macros are the source of truth for the contract with the backend;
update them here if the Gateway's namespace or event name ever changes.

## API

- `BackendClient::begin(host, port, onSetFreeText)` — connects to the
  Gateway. `onSetFreeText` is called with the text payload whenever a
  `display-text` event arrives. Non-blocking.
- `BackendClient::loop()` — call every `loop()` to pump the Socket.IO client.

## Usage

```cpp
#include "BackendClient.h"
#include "config.h"

void onSetFreeText(const char *text) {
  freeTextScreen.setText(text);
}

void setup() {
  BackendClient::begin(BACKEND_HOST, BACKEND_PORT, onSetFreeText);
}

void loop() {
  BackendClient::loop();
}
```

## Requirements

- Caller must provide `BACKEND_HOST` and `BACKEND_PORT` (see
  `include/config.h.template`).
- Only connects once WiFi is up (see `NetworkManager`) — this library has no
  dependency on WiFi state itself, it just won't succeed until the network is
  there.
- Depends on `links2004/WebSockets` (Socket.IO client) and `bblanchon/ArduinoJson`.

## Verified

Confirmed end-to-end against a running `pulse-backend` instance: the
namespace-prefix stripping in `handleEvent` correctly parses `/device`-scoped
`display-text` frames from the current `links2004/WebSockets` version.
