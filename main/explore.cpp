#include "Explore.h"

Explore::Explore(Controller *controller, unsigned long start)
{

    Serial.println("enter Explore state");

    this->controller = controller;

    this->emotion_duration = 10000;
    this->emotion_started = start;

    this->motor_interval = 1000;
    this->sonar_interval = 25;
    this->led_interval = 0;
    this->music_interval = 0;
    this->servo_interval = 0;

    this->motor_last_millis = 0;
    this->servo_last_millis = 0;
    this->music_last_millis = 0;
    this->led_last_millis = 0;
    this->sonar_last_millis = 500;

    this->isMotorSwapped = 1;
    this->isMotorStopped = 1;

    this->obstacleFound = 2;
    controller->next_emotion = 3; //default the next emotion is setted to disgust;
}

Explore::~Explore()
{
    Serial.println("exiting Explore state");
}

void Explore::motorAction()
{

    if(isMotorStopped)
    {
        if(isMotorSwapped)
        {
            controller->motor[0]->forward(255);
            controller->motor[1]->reverse(255);
            isMotorSwapped = 0;
        }
        else
        {
            controller->motor[0]->reverse(255);
            controller->motor[1]->forward(255);
            isMotorSwapped = 1;
        }
        this->motor_interval = 200;
        isMotorStopped = 0;
    }
    else
    {
        this->motor_interval = 1000;
        controller->motor[0]->stop();
        controller->motor[1]->stop();
        isMotorStopped = 1;
    }
    this->motor_last_millis = millis();
}

void Explore::servoAction()
{
    this->servo_last_millis = millis();
    this->servo_interval = this->emotion_duration;
    controller->servo[0]->open(80);
    controller->servo[1]->move(50, 80);
    controller->servo[2]->move(50, 80);
}

void Explore::musicAction()
{
    this->music_last_millis = millis();
    this->music_interval = this->emotion_duration;
}

void Explore::ledAction()
{
    this->led_last_millis = millis();
    this->led_interval = this->emotion_duration;
    controller->led->light(150, 150, 150);
}

void Explore::sonarAction()
{
    this->sonar_interval = 25;
    this->sonar_last_millis = millis();
    this->distance = controller->sonar->computeDistance();
    //the object is moving but not getting closer
    if((this->distance < 45 && this->distance > 35) || (this->distance > 55 && this->distance < 65))
    {
        this->consecutive ++;
        if (this->consecutive >= this->obstacleFound)
        {
            //change to joy
            Serial.println("i'm changing in joy");
            controller->next_emotion = 1;
        }
    }
    //the object is too closer
    else if(this->distance < 10 && this->distance > 0)
    {
        this->consecutive ++;
        if (this->consecutive >= this->obstacleFound)
        {
            //change to anger
            Serial.println("i'm changing in anger");
            controller->next_emotion = 2;
            this->emotion_started = millis() + this->emotion_duration;
        }
    }
    else
    {
        this->consecutive = 0;
    }
}

void Explore::stop()
{
    controller->motor[0]->stop();
    controller->motor[1]->stop();
    controller->led->light(0, 0, 0);
    delete this;
}
