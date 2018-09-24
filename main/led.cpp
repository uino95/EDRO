#include "led.h"
#include <Arduino.h>


Led::Led() {}

void Led::setup(int pinRed, int pinGreen, int pinBlue)
{
    pinMode(pinRed, OUTPUT);
    pinMode(pinGreen, OUTPUT);
    pinMode(pinBlue, OUTPUT);
    this->pinRed = pinRed;
    this->pinGreen = pinGreen;
    this->pinBlue = pinBlue;
}

void Led::light(int red, int green, int blue)
{
    if(red >= 150)
    {
        red = 150;
    }
    if(red <= 0)
    {
        red = 0;
    }
    if(green >= 150)
    {
        green = 150;
    }
    if(green <= 0)
    {
        green = 0;
    }
    if(blue >= 150)
    {
        blue = 150;
    }
    if(blue <= 0)
    {
        blue = 0;
    }
    analogWrite(this->pinRed, red);
    analogWrite(this->pinGreen, green);
    analogWrite(this->pinBlue, blue);
}

