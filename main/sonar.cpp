#include "sonar.h"

Sonar::Sonar() {}

void Sonar::setup(uint8_t trigPin, uint8_t echoPin, unsigned int maxDistance)
{
    sonar.setup(trigPin, echoPin, maxDistance);
    this->trigPin = trigPin;
    this->echoPin = echoPin;
}

int Sonar::computeDistance()
{

    this->distance = sonar.ping_cm();
    // Serial.print("Ping: ");
    // Serial.print(this->distance);
    // Serial.println("cm");
    return this->distance;
}
