#ifndef SPOTIFY_CLIENT_H
#define SPOTIFY_CLIENT_H

#include <Arduino.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

struct TrackInfo {
  String name;
  String artist;
  String album;
  bool isPlaying = false;
};

class SpotifyClient {
public:
  SpotifyClient(const char* clientId, const char* clientSecret, const char* refreshToken);

  bool refreshAccessToken();
  TrackInfo getCurrentTrack();

private:
  const char* _clientId;
  const char* _clientSecret;
  const char* _refreshToken;
  String _accessToken;

  const char* _authUrl = "https://accounts.spotify.com/api/token";
  const char* _playerUrl = "https://api.spotify.com/v1/me/player/currently-playing";
};

#endif
