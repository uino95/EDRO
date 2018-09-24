#ifndef SONAR_H_
#define SONAR_H_

#include <Arduino.h>
#include "MyNewPing.h"

using namespace std;

class Sonar
{

public:
    Sonar();
    void setup(uint8_t trigPin, uint8_t echo2Pin, unsigned int maxDistance);
    int computeDistance();

private:
    NewPing sonar;
    int trigPin;
    int echoPin;
    // int duration;
    int distance;
};

#endif // SONAR_H_
