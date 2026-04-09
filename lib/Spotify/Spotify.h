#ifndef SPOTIFY_H
#define SPOTIFY_H

#include <Arduino.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

class SpotifyClient {
public:
  SpotifyClient(const char* clientId, const char* clientSecret);

  // Fetches a new token. Returns true on success.
  bool authenticate();

  // Returns the current token, refreshing it first if expired.
  String getToken();

  // True if a token is held and has not expired yet.
  bool isTokenValid();

private:
  const char* _clientId;
  const char* _clientSecret;

  String        _accessToken;
  unsigned long _tokenExpiresAt; // millis() value when the token expires
};

#endif // SPOTIFY_H
