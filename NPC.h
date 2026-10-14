
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
    
        if (name == "Harshit")
        {
            cout << "1. Ask about old land records" << endl;
            cout << "2. Ask why he is investigating" << endl;
            cout << "3. End conversation" << endl;
        }
        else if (name == "Aarav")
        {
            cout << "1. Ask why Harshit is acting strange" << endl;
            cout << "2. Ask about land records" << endl;
            cout << "3. End conversation" << endl;
        }
        else if (name == "Ramesh")
        {
            cout << "1. Ask when Harshit started asking questions" << endl;
            cout << "2. Ask about visitors" << endl;
            cout << "3. End conversation" << endl;
        }
        else
        {
            cout << "1. Ask about the investigation" << endl;
            cout << "2. End conversation" << endl;
        }
    
        cout << "Enter your choice: ";
        cin >> choice;
    
        if (choice == 1)
        {
            cout << name << ": I have something to tell you." << endl;
        }
        else if (choice == 2)
        {
            cout << name << ": I am not sure what happened." << endl;
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
