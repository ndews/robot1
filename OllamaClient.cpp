
#include "OllamaClient.h"
#include <HTTPClient.h>
#include <ArduinoJson.h>

OllamaClient::OllamaClient(const String& url, const String& model)
    : apiUrl(url), modelName(model) {}

String OllamaClient::query(const String& prompt) {
  HTTPClient http;
  http.begin(apiUrl);
  http.addHeader("Content-Type", "application/json");

  StaticJsonDocument<1024> requestJson;
  requestJson["model"] = modelName;
  requestJson["prompt"] = prompt;
  requestJson["stream"] = false;

  String requestBody;
  serializeJson(requestJson, requestBody);

  int httpResponseCode = http.POST(requestBody);

  if (httpResponseCode > 0) {
    String responseBody = http.getString();
    StaticJsonDocument<2048> responseJson;
    DeserializationError error = deserializeJson(responseJson, responseBody);
    if (!error) {
      return responseJson["response"].as<String>();
    } else {
      return "Error: Failed to parse response JSON";
    }
  } else {
    return "Error: HTTP POST failed (" + String(httpResponseCode) + ")";
  }

  http.end();
}
