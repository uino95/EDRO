#include "controller.h"
#include "neutral.h"
#include "joy.h"
#include "anger.h"
#include "fear.h"
#include "sadness.h"
#include "disgust.h"
#include "search.h"
#include "explore.h"

Controller::Controller(MyServo * (&servoPtr)[3], Motor * (&motorPtr)[2], Led*&ledPtr, Player *&playerPtr, Sonar*&sonarPtr)
{
    this->servo[0] = servoPtr[0];
    this->servo[1] = servoPtr[1];
    this->servo[2] = servoPtr[2];
    this->motor[0] = motorPtr[0];
    this->motor[1] = motorPtr[1];
    this->led = ledPtr;
    this->player = playerPtr;
    this->sonar = sonarPtr;

    Search *s = new Search(this, millis());
    current_emotion = s;
}

void Controller::setEmotion(Emotion *e)
{
    current_emotion = e;
}

void Controller::updateEmotion(unsigned long current_millis)
{

    //until the emotion has time to do thing enter and do stuff
    if(current_millis - current_emotion->emotion_started < current_emotion->emotion_duration)
    {
        if(current_millis - current_emotion->motor_last_millis >= current_emotion->motor_interval)
        {
            current_emotion->motorAction();
        }
        if(current_millis - current_emotion->servo_last_millis >= current_emotion->servo_interval)
        {
            current_emotion->servoAction();
        }
        if(current_millis - current_emotion->led_last_millis >= current_emotion->led_interval)
        {
            current_emotion->ledAction();
        }
        if(current_millis - current_emotion->music_last_millis >= current_emotion->music_interval)
        {
            current_emotion->musicAction();
        }
        if(current_millis - current_emotion->sonar_last_millis >= current_emotion->sonar_interval)
        {
            current_emotion->sonarAction();
        }
    }
    else
    {
        changeEmotion();
    }
}

void Controller::changeEmotion()
{
    current_emotion->stop();
    switch(next_emotion)
    {
    case 1:
    {
        Joy *j = new Joy(this, millis());
        setEmotion(j);
        break;
    }
    case 2:
    {
        Anger *a = new Anger(this, millis());
        setEmotion(a);
        break;
    }
    case 3:
    {
        Disgust *d = new Disgust(this, millis());
        setEmotion(d);
        break;
    }
    case 4:
    {
        Fear *f = new Fear(this, millis());
        setEmotion(f);
        break;
    }
    case 5:
    {
        Sadness *s = new Sadness(this, millis());
        setEmotion(s);
        break;
    }
    case 6:
    {
        Search *s = new Search(this, millis());
        setEmotion(s);
        break;
    }
    case 7:
    {
        Explore *e = new Explore(this, millis());
        setEmotion(e);
        break;
    }
    default:
    {
        Neutral *n = new Neutral(this);
        setEmotion(n);
        next_emotion = 0;
    }
    }
    Serial.println("emotion changed");
}
