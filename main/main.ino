#include "controller.h"

MyServo* servo1 = new MyServo();
MyServo* servo2 = new MyServo();
MyServo* servo3 = new MyServo();
Motor* motor0 = new Motor();
Motor* motor1 = new Motor();
Led* led = new Led();
Player* player = new Player();
Sonar* sonar = new Sonar();

MyServo * servoPtrs[3] = {servo1, servo2, servo3};
Motor* motorPtrs[2] = {motor0, motor1};

Controller controller(servoPtrs, motorPtrs, led, player, sonar);

void setup(){
  Serial.begin(115200);
   //front servo
   servo1->setup(6);
   //left servo
   servo2->setup(7);
   //right servo
   servo3->setup(8);
   //left motor
   motor0->setup(22, 24, 11);
   //right motor
   motor1->setup(23, 25, 12);
   led->setup(2,3,5);
   player->setup(10,9);
   sonar->setup(33,31, 200);  
}
 
void loop(){
   controller.updateEmotion(millis());
}
