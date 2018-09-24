#include "myServo.h"


MyServo::MyServo() {}

//closed position is set to 100
//open position is set to 0
//speed range is from 0 (min) to 255 (max)
void MyServo::move(int pos, int speed)
{
    pos = computePos(pos);
    //Serial.println("moving to " + pos + " at speed " + speed);
    servo.slowmove(pos, speed);
}

void MyServo::close(int speed)
{
    move(85, speed);
}

void MyServo::open(int speed)
{
    move(0, speed);
}

void MyServo::reset()
{
    move(85, 255);
}

int MyServo::computePos(int pos)
{
    int new_pos;
    if(this->pin == 8)
    {
        new_pos = (pos * (-1)) + 95;
    }
    else if (this->pin == 6)
    {
        new_pos = pos + 15;
    }
    else
    {
        new_pos = pos + 5;
    }
    return new_pos;
}

void MyServo::setup(int pin)
{
    servo.attach(pin);
    this->pin = pin;
    this->move(85, 255);
}

void MyServo::Detach()
{
    servo.detach();
}

