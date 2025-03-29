
#include "ServoArm.h"

ServoArm::ServoArm(int pinNum) : pin(pinNum) {}

void ServoArm::attach() {
  servo.setPeriodHertz(50);
  servo.attach(pin, 500, 2400);
}

void ServoArm::setEmotion(RobotDisplay::Emotion e) {
  switch (e) {
    case RobotDisplay::HAPPY:
      servo.write(30); break;
    case RobotDisplay::SAD:
      servo.write(90); break;
    case RobotDisplay::SURPRISED:
      servo.write(150); break;
    case RobotDisplay::ANGRY:
      servo.write(70); break;
    default:
      servo.write(90); break;
  }
}
