#include <Arduino.h>
#include "RobotDisplay.h"
#include "OllamaClient.h"

RobotDisplay display(172, 320);
OllamaClient ollama("http://192.168.1.100:11434/api/generate", "llama2");

String lastResponse = "";

RobotDisplay::Emotion detectEmotion(const String &response) {
  String r = response;
  r.toLowerCase();
  int happyScore = 0, sadScore = 0, surprisedScore = 0, angryScore = 0;

  if (r.indexOf("happy") != -1) happyScore += 3;
  if (r.indexOf("yay") != -1) happyScore += 2;
  if (r.indexOf(":)") != -1 || r.indexOf("glad") != -1 || r.indexOf("love") != -1) happyScore += 1;

  if (r.indexOf("sad") != -1) sadScore += 3;
  if (r.indexOf(":(") != -1 || r.indexOf("lonely") != -1 || r.indexOf("miss") != -1) sadScore += 2;
  if (r.indexOf("worried") != -1) sadScore += 1;

  if (r.indexOf("surprise") != -1) surprisedScore += 3;
  if (r.indexOf("wow") != -1 || r.indexOf(":o") != -1) surprisedScore += 2;
  if (r.indexOf("whoa") != -1 || r.indexOf("no way") != -1) surprisedScore += 1;

  if (r.indexOf("angry") != -1) angryScore += 3;
  if (r.indexOf("mad") != -1 || r.indexOf(">:(") != -1) angryScore += 2;
  if (r.indexOf("frustrated") != -1 || r.indexOf("annoyed") != -1) angryScore += 1;

  int maxScore = happyScore;
  RobotDisplay::Emotion result = RobotDisplay::HAPPY;

  if (sadScore > maxScore) { maxScore = sadScore; result = RobotDisplay::SAD; }
  if (surprisedScore > maxScore) { maxScore = surprisedScore; result = RobotDisplay::SURPRISED; }
  if (angryScore > maxScore) { maxScore = angryScore; result = RobotDisplay::ANGRY; }

  if (maxScore == 0) return RobotDisplay::NEUTRAL;
  return result;
}

void setup() {
  Serial.begin(115200);
  display.init();
  display.showWelcome();

  String initPrompt =
    "You are a small, friendly desktop robot. Imagine you are similar to WALL-E, the lovable trash-collecting robot from the movie where Earth was abandoned by humans. "
    "Your job is to patiently clean and tidy, always curious and kind-hearted. You communicate in short, gentle phrases, full of emotion and personality. "
    "Respond to prompts like you're an adorable helper bot eager to please and explore the world. Maintain a warm and friendly tone.";

  String introResponse = ollama.query(initPrompt);
  RobotDisplay::Emotion emotion = detectEmotion(introResponse);
  display.setEmotion(emotion);
  display.showText(introResponse);
  lastResponse = introResponse;
}

void loop() {
  display.animateFace();
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    display.showThinking();
    String response = ollama.query(input);
    RobotDisplay::Emotion emotion = detectEmotion(response);
    display.setEmotion(emotion);
    display.showText(response);
    lastResponse = response;
  }
  delay(100);
}
