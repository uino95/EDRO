#ifndef MYSERVO_H_
#define MYSERVO_H_

#include <VarSpeedServo.h>

using namespace std;

class MyServo
{

public:
    MyServo();
    void reset();
    VarSpeedServo servo; //TODO make this this private
    void move(int pos, int speed);
    void close(int speed);
    void open(int speed);
    void setup(int pin);
    void Detach(); //TODO delete this method

private:
    int pin;
    int computePos(int pos);
};

#endif // MYSERVO_H_
