#ifndef SEARCH_H_
#define SEARCH_H_

#include "emotion.h"
#include "controller.h"

using namespace std;

class Search: public Emotion
{

public:
    Search(Controller *controller, unsigned long start);
    ~Search();

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

    int distance;
    int consecutive;
    int threshold;
    int obstacleFound;
    unsigned long rotation;
};

#endif // SEARCH_H_
