
#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include "NPC.h"
using namespace std;

class Player
{
private:
    string name;

public:
    Player(string n);
    void showName();
    void talkTo(NPC person);
};

#endif
