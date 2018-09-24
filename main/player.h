#ifndef PLAYER_H_
#define PLAYER_H_

#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include <Arduino.h>

using namespace std;

class Player
{

public:
    Player();
    DFRobotDFPlayerMini myDFPlayer;
    void setup(int TX, int RX);
    void play(int song);
    void setVolume(int volume);
    void stop();

private:
    void printDetail(uint8_t type, int value);
};

#endif // PLAYER_H_