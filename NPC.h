
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
        
        if (name == "Harshit")
        {
            if (choice == 1)
            {
                cout << "Harshit: Something is wrong with the old land records." << endl;
            }
            else if (choice == 2)
            {
                cout << "Harshit: I found a mismatch in the old documents." << endl;
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
        else if (name == "Aarav")
        {
            if (choice == 1)
            {
                cout << "Aarav: Harshit has been acting strange lately." << endl;
            }
            else if (choice == 2)
            {
                cout << "Aarav: Don't get dragged into the land records issue." << endl;
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
        else if (name == "Ramesh")
        {
            if (choice == 1)
            {
                cout << "Ramesh: Harshit has been asking many questions." << endl;
            }
            else if (choice == 2)
            {
                cout << "Ramesh: I think I saw Aarav near Harshit's house." << endl;
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
        else if (name == "Inspector Rao")
        {
            if (choice == 1)
            {
                cout << "Inspector Rao: I will investigate this matter in the morning." << endl;
            }
            else if (choice == 2)
            {
                cout << "You ended the conversation." << endl;
            }
            else
            {
                cout << "Invalid choice!" << endl;
            }
        }
        else
        {
            cout << "No dialogue available." << endl;
        }

        
    

    }

     
 
    
};

#endif
