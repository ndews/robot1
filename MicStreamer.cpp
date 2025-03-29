
#include "MicStreamer.h"
#include <AudioTools.h>
#include <HTTPClient.h>
#include <WiFi.h>

using namespace audio_tools;

I2SSampler sampler;
WAVEncoder encoder;
StreamCopy copier;
WiFiClient client;

void setupMicStream() {
  AudioLogger::instance().begin(Serial, AudioLogger::Warning);

  auto cfg = sampler.defaultConfig(RX_MODE);
  cfg.pin_bck = 25;
  cfg.pin_ws = 26;
  cfg.pin_data = 34;
  cfg.sample_rate = 16000;
  cfg.bits_per_sample = 16;
  sampler.begin(cfg);
}

void streamToWhisper() {
  HTTPClient http;
  http.begin("http://192.168.1.100:8080/stt");
  http.addHeader("Content-Type", "audio/wav");

  WiFiClient postStream = http.getStream();
  encoder.begin(postStream);
  copier.begin(encoder, sampler);

  uint32_t start = millis();
  while (millis() - start < 3000) {
    copier.copy();
  }

  encoder.end();
  int code = http.POST("");
  String response = http.getString();
  Serial.println("Whisper replied: " + response);
  http.end();
}
