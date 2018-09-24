#ifndef SADNESS_H_
#define SADNESS_H_

#include "emotion.h"
#include "controller.h"

using namespace std;

class Sadness: public Emotion
{

public:
    Sadness(Controller *controller, unsigned long start);
    ~Sadness();

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
    int steps[3];
    int initColor[3];
    int endColor[3];
    int currentColor[3];
};

#endif // SADNESS_H_
