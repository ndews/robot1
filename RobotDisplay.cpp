
#include "RobotDisplay.h"

RobotDisplay::RobotDisplay(int w, int h) : width(w), height(h), tft(TFT_eSPI()) {}

void RobotDisplay::init() {
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
}

void RobotDisplay::showWelcome() {
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.setTextSize(2);
  tft.setCursor(10, height / 2 - 10);
  tft.println("Hi! I'm RoboDesk 🤖");
}

void RobotDisplay::animateFace() {
  uint32_t now = millis();
  if (now - lastAnimTime > 500) {
    blink = !blink;
    lastAnimTime = now;

    tft.fillRect(0, 0, width, 60, TFT_BLACK);

    int eyeRadius = 15;
    int pupilRadius = 5;
    int leftX = width / 3;
    int rightX = 2 * width / 3;
    int eyeY = 30;

    tft.fillCircle(leftX, eyeY, eyeRadius, TFT_WHITE);
    tft.fillCircle(rightX, eyeY, eyeRadius, TFT_WHITE);

    if (!blink) {
      tft.fillCircle(leftX, eyeY, pupilRadius, TFT_BLACK);
      tft.fillCircle(rightX, eyeY, pupilRadius, TFT_BLACK);
    }

    switch (currentEmotion) {
      case HAPPY:
        tft.fillCircle(width/2, 50, 5 + emotionIntensity, TFT_GREEN);
        break;
      case SAD:
        tft.fillCircle(width/2, 60, 4 + emotionIntensity, TFT_BLUE);
        break;
      case SURPRISED:
        tft.fillCircle(width/2, 60, 6 + emotionIntensity, TFT_YELLOW);
        break;
      case ANGRY:
        tft.drawRect(0, 0, width, 60, TFT_RED);
        break;
      default:
        break;
    }
  }
}

void RobotDisplay::showThinking() {
  tft.fillScreen(TFT_NAVY);
  tft.setTextColor(TFT_WHITE, TFT_NAVY);
  tft.setTextSize(2);
  tft.setCursor(10, 80);
  tft.println("Thinking...");
}

void RobotDisplay::showText(const String &text) {
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);
  tft.setCursor(0, 70);
  tft.setTextWrap(true);
  tft.println(text);
}

void RobotDisplay::setEmotion(Emotion e, int intensity) {
  currentEmotion = e;
  emotionIntensity = intensity;
}
