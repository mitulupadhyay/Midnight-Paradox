#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
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

    void showName()
    {
        cout << "Detective " << name << endl;
    }
};

#endif
