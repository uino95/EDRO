#ifndef LED_H_
#define LED_H_

using namespace std;

class Led
{

public:
    Led();
    void setup(int pinRed, int pinGreen, int pinBlue);
    void light(int red, int green, int blue);
private:
    int pinRed;
    int pinGreen;
    int pinBlue;
};

#endif // LED_H_
