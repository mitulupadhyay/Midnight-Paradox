
#include "Player.h"

Player::Player(string n)
{
    name = n;
}

void Player::showName()
{
    cout << "Detective " << name << endl;
}

void Player::talkTo(NPC person)
{
    person.talk();
}

