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
    Player(string n)
    {
        name = n;
    }
    void talkTo(NPC person)
    {
        person.talk();
    }
    void showName()
    {
        cout << "Detective " << name << endl;
    }
};

#endif
