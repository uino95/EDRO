#ifndef NEUTRAL_H_
#define NEUTRAL_H_

#include "controller.h"
#include "emotion.h"

using namespace std;

class Neutral: public Emotion
{

public:
    Neutral(Controller *controller);
    ~Neutral();

    void motorAction();
    void servoAction();
    void musicAction();
    void ledAction();
    void sonarAction();
    void stop();

private:
    Controller *controller;
};

#endif // NEUTRAL_H_
