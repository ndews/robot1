
#ifndef PERSONALITYSYSTEM_H
#define PERSONALITYSYSTEM_H

enum PersonalityType { CURIOUS, CHEERFUL, SHY, SNARKY };

struct PersonalityProfile {
  PersonalityType type;
  float emotionBias[5]; // Happy, Sad, Angry, Surprised, Neutral
};

PersonalityProfile profile = {
  CHEERFUL,
  { 1.5, 0.5, 1.0, 1.2, 1.0 }
};

#endif
