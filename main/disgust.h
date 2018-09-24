#ifndef DISGUST_H_
#define DISGUST_H_

#include "emotion.h"
#include "controller.h"

using namespace std;

class Disgust: public Emotion
{

public:
    Disgust(Controller *controller, unsigned long start);
    ~Disgust();

    void motorAction();
    void servoAction();
    void musicAction();
    void ledAction();
    void sonarAction();
    void stop();

private:
    Controller *controller;
    bool isServoSwapped;
    bool isMotorSwapped;
};

#endif // DISGUST_H_
