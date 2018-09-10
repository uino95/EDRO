#include "anger.h"

Anger::Anger(Controller* controller, unsigned long start){

	Serial.println("enter Anger state");

  this->controller = controller;

	this->emotion_duration = 10000;
	this->emotion_started = start;
  
  this->servo_interval = 200;
  this->motor_interval = 50;
  this->led_interval = 50;
  this->sonar_interval = 1500;
  this->music_interval = 0;

  this->motor_last_millis = 0;
  this->servo_last_millis = 0;
  this->music_last_millis = 0;
  this->led_last_millis = 0;
  this->sonar_last_millis = 0;

  this->isMotorSwapped = 1;
  this->isServoSwapped =1;
  
  this->initColor[0] = 50;
  this->initColor[1] = 0;
  this->initColor[2] = 0;
  this->endColor[0] = 150;
  this->endColor[1] = 0;
  this->endColor[2] = 0;
    
    for(int i = 0; i< 3; i++){
      this->steps[i] = round((float)abs((int)this->initColor[i] - (int)this->endColor[i]) * (int)this->led_interval / (this->servo_interval * 2));
      if(this->steps[i] < 1){
        this->steps[i] = 1;
      }
      Serial.println(this->steps[i]);
      this->currentColor[i] = initColor[i];
    }

  this->threshold = 40;
  this->obstacleFound = 1;
  controller->next_emotion = 6; //default the next emotion is setted to search.
}

Anger::~Anger(){
	Serial.println("exiting Anger state");
}

void Anger::motorAction(){
  //Serial.println("motor action ");
  //Serial.println(millis());
  if(millis() -  this->emotion_started <= 3500){
    this->motor_last_millis = millis();
    controller->motor[0]->forward(255);
    controller->motor[1]->reverse(255);
  } else {
    this->motor_interval = 400;
  	if(isMotorSwapped){
  		this->motor_last_millis = millis();
  		controller->motor[0]->forward(255);
  		controller->motor[1]->forward(255);
  		isMotorSwapped = 0;
  	} else {
  		this->motor_last_millis = millis();
  		controller->motor[0]->stop();
  		controller->motor[1]->stop();
  		isMotorSwapped = 1;	
  	}
  }
}

void Anger::servoAction(){
  //Serial.println("servo action ");
  //Serial.println(millis());
  if(millis() -  this->emotion_started <= 3500){
    this->servo_last_millis = millis();
    controller->servo[0]->move(30,30);
    controller->servo[1]->move(30,30);
    controller->servo[2]->move(30,30);
  } else {
    if(isServoSwapped){
      this->servo_last_millis = millis();
  	  controller->servo[1]->move(50,90);
  	  controller->servo[2]->move(50,90);
      isServoSwapped = 0;
    } else {
      this->servo_last_millis = millis();
      controller->servo[1]->close(250);
      controller->servo[2]->close(250);
      isServoSwapped = 1;
    }
  }
}
	
void Anger::musicAction(){
  this->music_last_millis = millis();
  this->music_interval = this->emotion_duration;
  controller->player->setVolume(30);
  controller->player->play(7);
}

void Anger::ledAction(){
    if(this->currentColor[0] >= this->endColor[0] && this->currentColor[1] >= this->endColor[1] && this->currentColor[2] >= this->endColor[2]){
      for(int i = 0; i < 3; i++){
        currentColor[i] = initColor[i];
      }
    } else {
      controller->led->light(this->currentColor[0], this->currentColor[1], this->currentColor[2]);
      for(int i = 0; i < 3; i++){
        currentColor[i] = currentColor[i] + this->steps[i];
      }
    }
    this->led_last_millis = millis(); 
}

void Anger::sonarAction(){
  this->sonar_interval = 25;
  this->sonar_last_millis = millis();
  this->distance = controller->sonar->computeDistance();
  if(this->distance < this->threshold && this->distance > 0){
    this->consecutive ++;
    if (this->consecutive = this->obstacleFound){
      //change to fear
      controller->next_emotion = 4;
      this->emotion_started = this->emotion_duration;
    }
  } else {
    this->consecutive = 0;
  }
}

void Anger::stop(){
	controller->motor[0]->stop();
	controller->motor[1]->stop();
  controller->led->light(0,0,0);
  controller->player->stop();
	delete this;
}
