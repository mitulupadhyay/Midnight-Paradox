#pragma once
#include "TimeLoop.h"

class Game {
private:
    TimeLoop timeLoop;
    bool running;

    // ---- Dusre members ke objects yahan add karna ----
    // Notebook notebook;           // Evidence/Notebook person
    // Player player;               // Character person
    // StoryManager story;          // Tu (story person)
    // EndingManager endings;       // Tu (story person)
    // NOTE: Notebook ko TimeLoop reset me touch mat karna, taaki clues bache rahe.

    void showMenu();
    void startGame();
    void playDay();
    void showStatus();
    void handleMidnight();
public:
    Game();
    void run();
};
