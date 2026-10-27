#include "Game.h"
#include <iostream>
#include <limits>
using namespace std;

static int readInt() {
    int x;
    while (!(cin >> x)) {
        if (cin.eof()) return -1;  // input band ho gaya (Ctrl+Z / Ctrl+D)
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Please enter a number: ";
    }
    return x;
}

Game::Game() : running(true) {}

void Game::run() {
    while (running) showMenu();
}

void Game::showMenu() {
    cout << "\n=============================\n";
    cout << "        TIME LOOP GAME       \n";
    cout << "=============================\n";
    cout << "1. Start Game\n";
    cout << "2. Exit\n";
    cout << "Choice: ";
    int c = readInt();
    if (c == -1) { running = false; return; }
    if (c == 1) startGame();
    else if (c == 2) { cout << "Goodbye!\n"; running = false; }
    else cout << "Invalid choice.\n";
}

void Game::startGame() {
    timeLoop = TimeLoop();   // naya game: 8:00 AM, Loop 1
    // story.startLoop1();   // <- story person ka function yahan call hoga
    bool inGame = true;
    while (inGame && running) {
        playDay();
        inGame = false;      // playDay se quit hone par menu par wapas
    }
}

void Game::showStatus() {
    cout << "\n[Loop " << timeLoop.getLoop() << "]  Time: "
         << timeLoop.getTimeString() << "\n";
}

void Game::playDay() {
    while (true) {
        showStatus();
        cout << "1. Explore places   (30 min)\n";
        cout << "2. Talk to someone  (30 min)\n";
        cout << "3. Open notebook    (free)\n";
        cout << "4. Wait             (1 hour)\n";
        cout << "5. Quit to main menu\n";
        cout << "Choice: ";
        int c = readInt();
        if (c == -1) { running = false; return; }

        switch (c) {
            case 1:
                // player.explore();      // Character person
                cout << "You look around...\n";
                timeLoop.advance(30);
                break;
            case 2:
                // npc.talk();            // Character person
                cout << "You talk to someone...\n";
                timeLoop.advance(30);
                break;
            case 3:
                // notebook.display();    // Notebook person
                cout << "(Notebook will show here)\n";
                break;
            case 4:
                cout << "You wait...\n";
                timeLoop.advance(60);
                break;
            case 5:
                return;
            default:
                cout << "Invalid choice.\n";
        }

        if (timeLoop.isMidnight()) handleMidnight();
    }
}

void Game::handleMidnight() {
    cout << "\n*** The clock strikes midnight. Everything goes dark... ***\n";
    timeLoop.resetDay();     // sirf time reset hota hai, clues nahi
    // story.onLoopChanged(timeLoop.getLoop());   // Loop 2 ka start
    cout << "You wake up again. It is 8:00 AM... Loop "
         << timeLoop.getLoop() << " begins.\n";
}
