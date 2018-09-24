#include "fear.h"

Fear::Fear(Controller *controller, unsigned long start)
{

    Serial.println("enter Fear state");

    this->controller = controller;
    this->emotion_duration = 5000;
    this->emotion_started = start;

    this->motor_interval = 50;
    this->led_interval = 50;
    this->servo_interval = 0;
    this->sonar_interval = 0;
    this->music_interval = 0;

    this->motor_last_millis = start;
    this->servo_last_millis = start;
    this->music_last_millis = 0;
    this->led_last_millis = 0;
    this->sonar_last_millis = 0;

    this->isLedSwapped = 1;
    this->isMotorSwapped = 0;
    this->isServoSwapped = 0;
    controller->next_emotion = 6;//default the next emotion is set to search
}

Fear::~Fear()
{
    Serial.println("exiting Fear state");
}

void Fear::motorAction()
{
    Serial.println("motor action ");
    Serial.println(millis());
    //this->motor_interval = 50;
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

void Fear::servoAction()
{
    Serial.println("servo action ");
    Serial.println(millis());
    this->servo_last_millis = millis();
    this->servo_interval = this->emotion_duration;
    controller->servo[0]->close(255);
    controller->servo[1]->close(255);
    controller->servo[2]->close(255);
}

void Fear::musicAction()
{
    this->music_last_millis = millis();
    this->music_interval = this->emotion_duration;
    controller->player->setVolume(30);
    controller->player->play(9);
}

void Fear::ledAction()
{
    //this->led_interval = 50;
    this->led_last_millis = millis();
    if(isLedSwapped)
    {
        controller->led->light(150, 0, 150);
        isLedSwapped = 0;
    }
    else
    {
        controller->led->light(0, 0, 0);
        isLedSwapped = 1;
    }

}

void Fear::sonarAction() {};

void Fear::stop()
{
    controller->motor[0]->stop();
    controller->motor[1]->stop();
    controller->led->light(0, 0, 0);
    controller->player->stop();
    delete this;
}
