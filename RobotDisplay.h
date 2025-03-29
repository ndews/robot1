
#ifndef ROBOTDISPLAY_H
#define ROBOTDISPLAY_H

#include <TFT_eSPI.h>
#include <Arduino.h>

class RobotDisplay {
public:
  enum Emotion { NEUTRAL, HAPPY, SAD, SURPRISED, ANGRY };
  RobotDisplay(int w, int h);
  void init();
  void showWelcome();
  void animateFace();
  void showThinking();
  void showText(const String &text);
  void setEmotion(Emotion e, int intensity = 5);  // Fixed signature

private:
  TFT_eSPI tft;
  int width, height;
  uint32_t lastAnimTime = 0;
  bool blink = false;
  Emotion currentEmotion = NEUTRAL;
  int emotionIntensity = 5;  // Declared here
};

#endif
