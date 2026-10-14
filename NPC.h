
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
        int choice;

        cout << "\nTalking to " << name << endl;
        cout << "1. Ask about old land records" << endl;
        cout << "2. Ask if they suspect someone" << endl;
        cout << "3. End conversation" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            cout << name << ": Something is wrong with the old land records." << endl;
        }
        else if (choice == 2)
        {
            cout << name << ": I have some doubts, but suspicion is not proof." << endl;
        }
        else if (choice == 3)
        {
            cout << "You ended the conversation." << endl;
        }
        else
        {
            cout << "Invalid choice!" << endl;
        }
    }
};

#endif
