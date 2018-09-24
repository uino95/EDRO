#ifndef EMOTION_H_
#define EMOTION_H_

#include <Arduino.h>

using namespace std;

class Emotion
{

public:

    unsigned long emotion_duration;
    unsigned long emotion_started;

    //Intervals
    unsigned long motor_interval;
    unsigned long servo_interval;
    unsigned long music_interval;
    unsigned long led_interval;
    unsigned long sonar_interval;

    //Last call to action function
    unsigned long motor_last_millis;
    unsigned long servo_last_millis;
    unsigned long music_last_millis;
    unsigned long led_last_millis;
    unsigned long sonar_last_millis;

    //Actions to be redifined by the derived class
    virtual void motorAction();
    virtual void servoAction();
    virtual void musicAction();
    virtual void ledAction();
    virtual void sonarAction();
    virtual void stop();

};

#endif // EMOTION_H_
