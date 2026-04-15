/**
 * @file SpotifyClient.h
 * @brief Library for interacting with the Spotify Web API on ESP32.
 */

#ifndef SPOTIFY_CLIENT_H
#define SPOTIFY_CLIENT_H

#include <Arduino.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

/**
 * @struct TrackInfo
 * @brief Structure to hold information about the currently playing Spotify track.
 */
struct TrackInfo {
  String name;      /**< Name of the track */
  String artist;    /**< Name of the artist(s) */
  String album;     /**< Name of the album */
  bool isPlaying = false; /**< Playback status (true if playing, false if paused/stopped) */
};

/**
 * @class SpotifyClient
 * @brief Handles authentication and track data retrieval from Spotify.
 */
class SpotifyClient {
public:
  /**
   * @brief Constructor for SpotifyClient.
   * @param clientId Spotify App Client ID.
   * @param clientSecret Spotify App Client Secret.
   * @param refreshToken Spotify Refresh Token for obtaining access tokens.
   */
  SpotifyClient(const char* clientId, const char* clientSecret, const char* refreshToken);

  /**
   * @brief Refreshes the Spotify access token using the refresh token.
   * @return true if the token was successfully refreshed, false otherwise.
   */
  bool refreshAccessToken();

  /**
   * @brief Fetches the currently playing track information.
   * @details If the access token is expired, it attempts to refresh it automatically.
   * @return A TrackInfo struct containing the current playback state and track metadata.
   */
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
