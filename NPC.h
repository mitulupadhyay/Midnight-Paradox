#ifndef NPC_H
#define NPC_H

#include "Character.h"

class NPC : public Character
{
public:
    NPC(string n, string d) : Character(n, d)
    {
    }

    void talk()
    {
        introduce();
    }
};

#endif
