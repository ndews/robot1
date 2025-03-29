
#include "MicStreamer.h"
#include <AudioTools.h>
#include <HTTPClient.h>
#include <WiFi.h>

WiFiClient client;
I2SStream i2s;
EncodedAudioStream encStream(i2s, new WAVEncoder());

void setupMicStream() {
  AudioLogger::instance().begin(Serial, AudioLogger::Warning);
  auto cfg = i2s.defaultConfig(RX_MODE);
  cfg.pin_bclk = 25;
  cfg.pin_ws = 26;
  cfg.pin_data = 34;
  cfg.sample_rate = 16000;
  cfg.bits_per_sample = 16;
  i2s.begin(cfg);
  encStream.begin();
}

void streamToWhisper() {
  uint8_t buffer[4096];
  int len = encStream.read(buffer, sizeof(buffer));
  if (len > 0) {
    HTTPClient http;
    http.begin("http://192.168.1.100:8080/stt");  // Change IP as needed
    http.addHeader("Content-Type", "audio/wav");
    int resp = http.POST(buffer, len);
    if (resp > 0) {
      String reply = http.getString();
      Serial.println("Whisper response: " + reply);
      // Optionally send to OllamaClient here
    }
    http.end();
  }
}
