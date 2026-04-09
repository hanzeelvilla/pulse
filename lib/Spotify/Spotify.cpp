#include "Spotify.h"

static const char* TOKEN_URL = "https://accounts.spotify.com/api/token";

SpotifyClient::SpotifyClient(const char* clientId, const char* clientSecret)
  : _clientId(clientId),
    _clientSecret(clientSecret),
    _accessToken(""),
    _tokenExpiresAt(0)
{}

bool SpotifyClient::authenticate() {
  WiFiClientSecure client;
  client.setInsecure();

  HTTPClient http;
  http.begin(client, TOKEN_URL);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  String body = "grant_type=client_credentials";
  body += "&client_id="     + String(_clientId);
  body += "&client_secret=" + String(_clientSecret);

  int httpCode = http.POST(body);

  if (httpCode != 200) {
    Serial.printf("[Spotify] Token request failed — HTTP %d\n", httpCode);
    Serial.println(http.getString());
    http.end();
    return false;
  }

  JsonDocument doc;
  DeserializationError err = deserializeJson(doc, http.getString());
  http.end();

  if (err) {
    Serial.print("[Spotify] JSON parse error: ");
    Serial.println(err.c_str());
    return false;
  }

  _accessToken    = doc["access_token"].as<String>();
  int expiresIn   = doc["expires_in"].as<int>(); // seconds

  // Subtract 30 s so we refresh slightly before actual expiry
  _tokenExpiresAt = millis() + ((unsigned long)(expiresIn - 30)) * 1000UL;

  Serial.printf("[Spotify] Token obtained. Expires in %d s.\n", expiresIn);
  return true;
}

bool SpotifyClient::isTokenValid() {
  return _accessToken.length() > 0 && millis() < _tokenExpiresAt;
}

String SpotifyClient::getToken() {
  if (!isTokenValid()) {
    Serial.println("[Spotify] Token missing or expired, authenticating...");
    if (!authenticate()) return "";
  }
  return _accessToken;
}
