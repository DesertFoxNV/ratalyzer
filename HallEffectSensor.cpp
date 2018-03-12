/* Class created by Joshua Wright 3/1/2018 */

#include "Arduino.h"
#include <stdlib.h>

class HallEffectSensor
{
  int powerPin;
  int groundPin;
  int sensorPin;

  //Constructor
  public:
  HallEffectSensor(int pwrPin, int gndPin, int digitalPin)
  {
    powerPin = pwrPin;
    groundPin = gndPin;
    sensorPin = digitalPin;

    pinMode(powerPin, OUTPUT);
    pinMode(groundPin, OUTPUT);
    pinMode(sensorPin, INPUT);

    digitalWrite(powerPin, HIGH);
    digitalWrite(groundPin, LOW);
  }

  byte read()
  {
    return digitalRead(sensorPin);
  }
  
};

