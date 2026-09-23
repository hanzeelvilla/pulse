#ifndef BACKEND_CLIENT_H
#define BACKEND_CLIENT_H

#include <Arduino.h>

// Socket.IO namespace and event name contract shared with the NestJS
// Gateway (see pulse-backend). Keep this in sync if the backend ever
// changes either value.
#define BACKEND_DEVICE_NAMESPACE "/device"
#define EVENT_SET_FREE_TEXT "set-free-text"

namespace BackendClient {
  // Invoked with the text payload of a "set-free-text" event.
  typedef void (*FreeTextHandler)(const char *text);

  // Connects to the backend's Socket.IO Gateway on the BACKEND_DEVICE_NAMESPACE
  // namespace. Non-blocking: the actual connect/reconnect happens inside loop().
  void begin(const char *host, uint16_t port, FreeTextHandler onSetFreeText);

  // Call every loop(). Pumps the Socket.IO client (connect/reconnect, events).
  void loop();
}

#endif // BACKEND_CLIENT_H
