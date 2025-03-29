
#ifndef OLLAMACLIENT_H
#define OLLAMACLIENT_H

#include <Arduino.h>

class OllamaClient {
public:
  OllamaClient(const String& url, const String& model);
  String query(const String& prompt);
private:
  String apiUrl;
  String modelName;
};

#endif
