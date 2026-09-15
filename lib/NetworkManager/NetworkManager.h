#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

namespace NetworkManager {
  // Blocking initial connect: up to ~10s (20 retries x 500ms delay).
  // Logs progress and result over Serial, including the IP address on success.
  // Returns true if the connection succeeded.
  bool begin(const char *ssid, const char *password);

  // Call every loop(). Returns the current connection state.
  // While disconnected, attempts a reconnect (same blocking retry burst as
  // begin()) at most once every 10 seconds; otherwise returns immediately.
  bool ensureConnected();
}

#endif // NETWORK_MANAGER_H
