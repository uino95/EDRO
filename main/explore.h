#ifndef EXPLORE_H_
#define EXPLORE_H_

#include "emotion.h"
#include "controller.h"

using namespace std;

class Explore: public Emotion
{

public:
    Explore(Controller *controller, unsigned long start);
    ~Explore();

    void motorAction();
    void servoAction();
    void musicAction();
    void ledAction();
    void sonarAction();
    void stop();

private:
    Controller *controller;
    bool isMotorStopped;
    bool isMotorSwapped;
    bool isSonarSwapped;

    int distance;
    int consecutive;
    int threshold;
    int obstacleFound;
    unsigned long rotation;
};

#endif // EXPLORE_H_
