#include "disgust.h"

Disgust::Disgust(Controller *controller, unsigned long start)
{

    Serial.println("enter Disgust state");

    this->controller = controller;

    this->emotion_duration = 5000;
    this->emotion_started = start;

    this->motor_last_millis = start;
    this->led_last_millis = 0;
    this->servo_last_millis = 0;
    this->music_last_millis = 0;
    this->sonar_last_millis = 0;

    this->servo_interval = 500;
    this->motor_interval = 70;
    this->led_interval = 0;
    this->sonar_interval = 0;
    this->music_interval = 0;

    this->isServoSwapped = 0;
    this->isMotorSwapped = 0;

    controller->next_emotion = 6; //default the next emotion is setted to search
}

Disgust::~Disgust()
{
    Serial.println("exiting Disgust state");
}

void Disgust::motorAction()
{
    Serial.println("motor action ");
    Serial.println(millis());
    if(millis() - this->emotion_started <= 1700)
    {
        if(isMotorSwapped)
        {
            this->motor_last_millis = millis();
            controller->motor[0]->forward(255);
            controller->motor[1]->reverse(255);
            isMotorSwapped = 0;
        }
        else
        {
            this->motor_last_millis = millis();
            controller->motor[0]->reverse(255);
            controller->motor[1]->forward(255);
            isMotorSwapped = 1;
        }
    }
    else if(millis() - this->emotion_started <= 2000)
    {
        controller->motor[0]->reverse(255);
        controller->motor[1]->reverse(255);
        this->motor_interval = 2000;
    }
    else
    {
        controller->motor[0]->stop();
        controller->motor[1]->stop();
        this->motor_interval = this->emotion_duration;
    }

}

void Disgust::servoAction()
{
    Serial.println("servo action ");
    Serial.println(millis());
    if(millis() - this->emotion_started >= 500)
    {
        controller->servo[0]->open(50);
        this->servo_interval = this->emotion_duration;
    }
    else
    {
        this->servo_last_millis = millis();
        controller->servo[0]->close(30);
        controller->servo[1]->close(30);
        controller->servo[2]->close(30);
    }
}

void Disgust::musicAction()
{
    this->music_last_millis = millis();
    this->music_interval = this->emotion_duration;
    controller->player->setVolume(30);
    controller->player->play(10);
}

void Disgust::ledAction()
{
    this->led_last_millis = millis();
    this->led_interval = this->emotion_duration;
    Serial.println("led");
    controller->led->light(0, 150, 0);
}

void Disgust::sonarAction() {}

void Disgust::stop()
{
    controller->motor[0]->stop();
    controller->motor[1]->stop();
    controller->led->light(0, 0, 0);
    controller->player->stop();
    delete this;
}
