

#include "Character.h"

Character::Character(string n, string d)
{
    name = n;
    dialogue = d;
}

void Character::introduce()
{
    cout << name << ": " << dialogue << endl;
}
