#ifndef FEAR_H_
#define FEAR_H_

#include "emotion.h"
#include "controller.h"

using namespace std;

class Fear: public Emotion
{

public:
    Fear(Controller *controller, unsigned long start);
    ~Fear();

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
    bool isLedSwapped;
};

#endif // FEAR_H_
