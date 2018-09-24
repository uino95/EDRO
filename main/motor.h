#ifndef MOTOR_H_
#define MOTOR_H_

#include <Arduino.h>

using namespace std;

class Motor
{

public:
    Motor();
    void stop();
    void forward(int speed);
    void reverse(int speed);
    void setup(int dir1Pin, int dir2Pin, int speedPin);

private:
    int dir1Pin;
    int dir2Pin;
    int speedPin;
};

#endif // MOTOR_H_