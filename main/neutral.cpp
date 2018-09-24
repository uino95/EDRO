#include "neutral.h"

Neutral::Neutral(Controller *controller)
{

    Serial.println("enter Neutral state");

    this->controller = controller;

    this->emotion_duration = 0;//duration of the emotion in milliseconds
    this->emotion_started = 0;

    motorAction();
    servoAction();
    ledAction();
}

Neutral::~Neutral()
{
    Serial.println("exiting neutral state");
}

void Neutral::motorAction()
{
    Serial.println("motor action neutral");
    Serial.println(millis());
    controller->motor[0]->stop();
    controller->motor[1]->stop();
}

void Neutral::servoAction()
{
    Serial.println("servo action neutral");
    Serial.println(millis());
    controller->servo[0]->close(30);
    controller->servo[1]->close(30);
    controller->servo[2]->close(30);
}

void Neutral::musicAction() {}

void Neutral::ledAction()
{
    controller->led->light(0, 0, 0);
}

void Neutral::sonarAction() {}

void Neutral::stop()
{
    delete this;
}
