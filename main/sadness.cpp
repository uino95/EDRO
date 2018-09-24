#include "sadness.h"

Sadness::Sadness(Controller *controller, unsigned long start)
{

    Serial.println("enter Sadness state");

    this->controller = controller;

    this->emotion_duration = 7000;
    this->emotion_started = start;

    this->led_interval = 100;
    this->servo_interval = 0;
    this->motor_interval = 0;
    this->sonar_interval = 0;
    this->music_interval = 0;

    this->motor_last_millis = start;
    this->servo_last_millis = start;
    this->music_last_millis = 0;
    this->led_last_millis = start;
    this->sonar_last_millis = 0;

    this->initColor[0] = 0;
    this->initColor[1] = 150;
    this->initColor[2] = 150;
    this->endColor[0] = 0;
    this->endColor[1] = 10;
    this->endColor[2] = 10;

    for(int i = 0; i < 3; i++)
    {
        this->steps[i] = round((float)abs((int)this->initColor[i] - (int)this->endColor[i]) * (int)this->led_interval / this->emotion_duration);
        if(this->steps[i] < 1)
        {
            this->steps[i] = 1;
        }
        //Serial.println(this->steps[i]);
        this->currentColor[i] = initColor[i];
    }

    controller->next_emotion = 6; //default the next emotion/state will be search
}

Sadness::~Sadness()
{
    Serial.println("exiting Sadness state");
}

void Sadness::motorAction()
{
    Serial.println("motor action ");
    Serial.println(millis());
    if(millis() - this->emotion_started < (this->emotion_duration / 5))
    {
        //Serial.println("motor action < 1/3 ");
        //Serial.println(millis() -  this->emotion_started);
        controller->motor[0]->stop();
        controller->motor[1]->stop();
        this->motor_last_millis = millis();
        this->motor_interval = (this->emotion_duration * 2 / 5);
    }
    if (millis() - this->emotion_started >= this->emotion_duration * 2 / 5)
    {
        this->motor_interval = 1000;
        //Serial.println("motor action > 2/3 ");
        //Serial.println(millis() -  this->emotion_started);
        if(isMotorSwapped)
        {
            controller->motor[0]->reverse(180);
            controller->motor[1]->forward(255);
            this->motor_last_millis = millis();
            isMotorSwapped = 0;
        }
        else
        {
            controller->motor[0]->forward(255);
            controller->motor[1]->reverse(180);
            this->motor_last_millis = millis();
            isMotorSwapped = 1;
        }

    }
}

void Sadness::servoAction()
{
    //Serial.println("servo action ");
    //Serial.println(millis());
    if(millis() - this->emotion_started < this->emotion_duration / 5)
    {
        //Serial.println("servo action first");
        //Serial.println(millis() -  this->emotion_started);
        controller->servo[0]->close(25);
        controller->servo[1]->close(25);
        controller->servo[2]->close(25);
        this->servo_last_millis = millis();
        this->servo_interval = this->emotion_duration / 5;
    }
    else
    {
        //Serial.println("servo action second");
        Serial.println(millis() -  this->emotion_started);
        controller->servo[0]->open(25);
        controller->servo[1]->open(25);
        controller->servo[2]->open(25);
        this->servo_interval = this->emotion_duration;
        this->servo_last_millis = millis();
    }
}


void Sadness::musicAction()
{
    this->music_last_millis = millis();
    this->music_interval = this->emotion_duration;
    controller->player->setVolume(30);
    controller->player->play(5);
}

void Sadness::ledAction()
{
    this->led_last_millis = millis();
    //Serial.println("led");
    controller->led->light(this->currentColor[0], this->currentColor[1], this->currentColor[2]);
    for(int i = 0; i < 3; i++)
    {
        currentColor[i] = currentColor[i] - this->steps[i];
    }
}

void Sadness::sonarAction() {}

void Sadness::stop()
{
    controller->motor[0]->stop();
    controller->motor[1]->stop();
    controller->led->light(0, 0, 0);
    controller->player->stop();
    delete this;
}
