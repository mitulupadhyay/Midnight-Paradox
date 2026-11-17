
#include "Player.h"
#include "NPC.h"
#include "Location.h"

int main()
{
    Player mitul("Mitul");

    NPC harshit("Harshit", "I found something strange in the old land records.");
    NPC aarav("Aarav", "Harshit has been acting strange lately.");
    NPC ramesh("Ramesh", "Harshit has been asking many questions.");
    NPC inspector("Inspector Rao", "I will investigate this matter in the morning.");

    Location room("Mitul's Room", "You wake up in your room at 8 AM.");
    Location house("Harshit's House", "A quiet house near the town street.");
    Location shop("Ramesh's Shop", "A small shop in the town.");

    int choice;

    cout << "=== MIDNIGHT PARADOX ===" << endl;
    mitul.showName();

    do
    {
        cout << "\nChoose a location:" << endl;
        cout << "1. Mitul's Room" << endl;
        cout << "2. Harshit's House" << endl;
        cout << "3. Ramesh's Shop" << endl;
        cout << "4. Talk to Aarav" << endl;
        cout << "5. Talk to Inspector Rao" << endl;
        cout << "0. Exit game" << endl;

        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            room.showLocation();
        }
        else if (choice == 2)
        {
            house.showLocation();
            mitul.talkTo(harshit);
        }
        else if (choice == 3)
        {
            shop.showLocation();
            mitul.talkTo(ramesh);
        }
        else if (choice == 4)
        {
            mitul.talkTo(aarav);
        }
        else if (choice == 5)
        {
            mitul.talkTo(inspector);
        }
        else if (choice == 0)
        {
            cout << "Thanks for playing!" << endl;
        }
        else
        {
            cout << "Invalid choice!" << endl;
        }

    } while (choice != 0);

    return 0;
}
