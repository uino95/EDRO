#include "motor.h"

Motor::Motor() {}

void Motor::setup(int dir1Pin, int dir2Pin, int speedPin)
{
    pinMode(dir1Pin, OUTPUT);
    pinMode(dir2Pin, OUTPUT);
    pinMode(speedPin, OUTPUT);
    this->dir1Pin = dir1Pin;
    this->dir2Pin = dir2Pin;
    this->speedPin = speedPin;
}

void Motor::forward(int speed)
{
    analogWrite(speedPin, speed);
    digitalWrite(dir1Pin, LOW);
    digitalWrite(dir2Pin, HIGH);
}

void Motor::stop()
{
    analogWrite(speedPin, 0);
}

void Motor::reverse(int speed)
{
    analogWrite(speedPin, speed);
    digitalWrite(dir1Pin, HIGH);
    digitalWrite(dir2Pin, LOW);
}
