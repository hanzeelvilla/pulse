#include "SpotifyClient.h"

SpotifyClient::SpotifyClient(const char* clientId, const char* clientSecret, const char* refreshToken) {
  _clientId = clientId;
  _clientSecret = clientSecret;
  _refreshToken = refreshToken;
  _accessToken = "";
}

bool SpotifyClient::refreshAccessToken() {
  WiFiClientSecure client;
  client.setInsecure();
  HTTPClient http;

  Serial.println("[Spotify] Refreshing access token...");

  http.begin(client, _authUrl);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  String body = "grant_type=refresh_token&refresh_token=" + String(_refreshToken);
  body += "&client_id=" + String(_clientId);
  body += "&client_secret=" + String(_clientSecret);

  int httpCode = http.POST(body);
  bool success = false;

  if (httpCode == 200) {
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, http.getString());
    
    if (!error) {
      _accessToken = doc["access_token"].as<String>();
      Serial.println("[Spotify] Token refreshed successfully.");
      success = true;
    } else {
      Serial.println("[Spotify] JSON parsing failed during token refresh.");
    }
  } else {
    Serial.printf("[Spotify] Token refresh failed with HTTP code: %d\n", httpCode);
  }

  http.end();
  return success;
}

TrackInfo SpotifyClient::getCurrentTrack() {
  TrackInfo info;

  // Initialize token if empty
  if (_accessToken == "") {
    if (!refreshAccessToken()) return info;
  }

  WiFiClientSecure client;
  client.setInsecure();
  HTTPClient http;

  http.begin(client, _playerUrl);
  http.addHeader("Authorization", "Bearer " + _accessToken);

  int httpCode = http.GET();

  if (httpCode == 200) {
    String payload = http.getString();
    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, payload);

    if (!error) {
      info.isPlaying = doc["is_playing"].as<bool>();
      
      // Check if item object exists (it might be null if a podcast is playing or app is transitioning)
      if (doc.containsKey("item") && !doc["item"].isNull()) {
        info.name = doc["item"]["name"].as<String>();
        info.album = doc["item"]["album"]["name"].as<String>();

        // Handle multiple artists by concatenating them with commas
        JsonArray artists = doc["item"]["artists"];
        String artistList = "";
        for (size_t i = 0; i < artists.size(); i++) {
          artistList += artists[i]["name"].as<String>();
          if (i < artists.size() - 1) {
            artistList += ", ";
          }
        }
        info.artist = artistList;
      }
    } else {
      Serial.println("[Spotify] Failed to parse currently playing JSON.");
    }
  } 
  else if (httpCode == 204) {
    // HTTP 204 means success but no track is currently active/playing
    info.isPlaying = false;
  } 
  else if (httpCode == 401) {
    // Unauthorized: Token might have expired, refresh and retry once
    Serial.println("[Spotify] Access token expired. Retrying...");
    if (refreshAccessToken()) {
        return getCurrentTrack();
    }
  } 
  else {
    Serial.printf("[Spotify] GET request failed. HTTP code: %d\n", httpCode);
  }

  http.end();
  return info;
}