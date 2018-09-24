#ifndef JOY_H_
#define JOY_H_

#include "emotion.h"
#include "controller.h"

using namespace std;

class Joy: public Emotion
{

public:
    Joy(Controller *controller, unsigned long start);
    ~Joy();

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

#endif // JOY_H_
