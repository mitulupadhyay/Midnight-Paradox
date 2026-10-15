
#ifndef NPC_H
#define NPC_H

#include "Character.h"

class NPC : public Character
{
public:
    NPC(string n, string d);
    void talk();
};

#endif
