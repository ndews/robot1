
#ifndef SERVOARM_H
#define SERVOARM_H

#include <Arduino.h>
#include <ESP32Servo.h>
#include "RobotDisplay.h"

class ServoArm {
public:
  ServoArm(int pin);
  void attach();
  void setEmotion(RobotDisplay::Emotion e);

private:
  Servo servo;
  int pin;
};

#endif
