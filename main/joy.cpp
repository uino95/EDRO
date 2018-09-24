#include "joy.h"

Joy::Joy(Controller *controller, unsigned long start)
{

    Serial.println("enter Joy state");

    this->controller = controller;

    this->emotion_duration = 10000;
    this->emotion_started = start;

    this->servo_interval = 350;
    this->motor_interval = 150;
    this->led_interval = 200;
    this->sonar_interval = 0;
    this->music_interval = 0;

    this->motor_last_millis = start;
    this->servo_last_millis = start;
    this->music_last_millis = 0;
    this->led_last_millis = start;
    this->sonar_last_millis = 0;

    this->isMotorSwapped = 0;
    this->isServoSwapped = 0;
    this->isLedSwapped = 0;

    controller->next_emotion = 7;

}

Joy::~Joy()
{
    Serial.println("exiting Joy state");
}

void Joy::motorAction()
{
    //Serial.println("motor action ");
    //Serial.println(millis());
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

void Joy::servoAction()
{
    //Serial.println("servo action ");
    //Serial.println(millis());
    if(isServoSwapped)
    {
        this->servo_last_millis = millis();
        controller->servo[0]->move(10, 40);
        controller->servo[1]->move(10, 40);
        controller->servo[2]->move(10, 40);
        isServoSwapped = 0;
    }
    else
    {
        this->servo_last_millis = millis();
        controller->servo[0]->move(50, 40);
        controller->servo[1]->move(50, 40);
        controller->servo[2]->move(50, 40);
        isServoSwapped = 1;
    }
}

void Joy::musicAction()
{
    this->music_last_millis = millis();
    this->music_interval = this->emotion_duration;
    controller->player->setVolume(30);
    controller->player->play(1);
}

void Joy::ledAction()
{
    this->led_last_millis = millis();
    if(isLedSwapped)
    {
        controller->led->light(150, 150, 0);
        isLedSwapped = 0;
    }
    else
    {
        controller->led->light(0, 0, 0);
        isLedSwapped = 1;
    }

}

void Joy::sonarAction() {}

void Joy::stop()
{
    controller->motor[0]->stop();
    controller->motor[1]->stop();
    controller->led->light(0, 0, 0);
    controller->player->stop();
    delete this;
}
