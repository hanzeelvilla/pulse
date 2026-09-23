#include "BackendClient.h"
#include <SocketIOclient.h>
#include <ArduinoJson.h>
#include <string.h>

namespace {
  SocketIOclient socketIO;
  BackendClient::FreeTextHandler freeTextHandler = nullptr;

  // Older/point releases of the Socket.IO client library don't strip the
  // namespace prefix from EVENT payloads on non-default namespaces, so the
  // raw frame can arrive either as `["event",...]` or `/device,["event",...]`.
  // Skip past the prefix if present before handing the rest to ArduinoJson.
  const uint8_t *skipNamespacePrefix(const uint8_t *payload, size_t length, size_t &outLength) {
    const char *comma = (const char *)memchr(payload, ',', length);
    if (comma != nullptr && payload[0] == '/') {
      size_t skipped = (const uint8_t *)comma + 1 - payload;
      outLength = length - skipped;
      return payload + skipped;
    }
    outLength = length;
    return payload;
  }

  void handleEvent(uint8_t *payload, size_t length) {
    size_t jsonLength;
    const uint8_t *json = skipNamespacePrefix(payload, length, jsonLength);

    JsonDocument doc;
    if (deserializeJson(doc, json, jsonLength) != DeserializationError::Ok) {
      Serial.println("BackendClient: failed to parse event payload");
      return;
    }

    const char *eventName = doc[0];
    if (eventName == nullptr || strcmp(eventName, EVENT_SET_FREE_TEXT) != 0) {
      return;
    }

    const char *text = doc[1].as<const char *>();
    if (text != nullptr && freeTextHandler != nullptr) {
      freeTextHandler(text);
    }
  }

  void socketIOEvent(socketIOmessageType_t type, uint8_t *payload, size_t length) {
    switch (type) {
      case sIOtype_CONNECT:
        Serial.println("BackendClient: connected, joining " BACKEND_DEVICE_NAMESPACE);
        socketIO.send(sIOtype_CONNECT, BACKEND_DEVICE_NAMESPACE);
        break;
      case sIOtype_DISCONNECT:
        Serial.println("BackendClient: disconnected");
        break;
      case sIOtype_EVENT:
        handleEvent(payload, length);
        break;
      default:
        break;
    }
  }
}

void BackendClient::begin(const char *host, uint16_t port, FreeTextHandler onSetFreeText) {
  freeTextHandler = onSetFreeText;
  socketIO.begin(host, port, "/socket.io/?EIO=4");
  socketIO.onEvent(socketIOEvent);
}

void BackendClient::loop() {
  socketIO.loop();
}
