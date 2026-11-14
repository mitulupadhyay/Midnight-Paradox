// Game.cpp - main menu, input helpers, and the ten loop drivers.

#include "Declarations.cpp"

// Console input helpers (declared in Declarations.cpp, defined here).

void printDivider() {
    cout << "============================================================\n";
}

void waitForContinue() {
    askChoice("\nPress 1 to continue: ", 1, 1);
}

// Reads a number in range and retries on bad input, so the game never crashes.
int askChoice(const string& prompt, int minChoice, int maxChoice) {
    int choice;
    while (true) {
        cout << prompt;

        if (cin >> choice) {
            // Clear the rest of the line so later input is not skipped.
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (choice >= minChoice && choice <= maxChoice) {
                return choice;
            }

            cout << "Invalid choice. Enter a number between "
                 << minChoice << " and " << maxChoice << ".\n";
        } else {
            if (cin.eof()) {
                // Input stream closed (useful for automated tests).
                cout << "\nInput ended. Closing the game.\n";
                exit(0);
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
        }
    }
}

Game::Game()
    : player("Mitul"),
      harshit("Harshit Mehra", "Mitul's childhood friend",
              "He has been worried about some old land records."),
      aarav("Aarav", "Harshit's closest friend",
            "He wants Harshit to stop investigating."),
      ramesh("Ramesh", "Local shopkeeper",
             "He sees most of what happens on this street."),
      rao("Inspector Rao", "Police inspector",
          "He follows evidence, not rumours."),
      clerk("Records Clerk", "Town records office employee",
            "He manages the archived property files."),
      recordsOffice("Town records office",
                    "Older property files are kept in the storage room here."),
      gameRunning(true),
      metAaravToday(false),
      metRameshToday(false) {

    // Base-class pointers for polymorphic calls.
    characters.push_back(&harshit);
    characters.push_back(&aarav);
    characters.push_back(&ramesh);
    characters.push_back(&rao);

    locations.push_back(Location(
        "Harshit's house",
        "A small house at the end of the road. Harshit lives here."));
    locations.push_back(Location(
        "Ramesh's shop",
        "The local shop. Ramesh hears most of the town's gossip."));
    locations.push_back(Location(
        "Town street",
        "The main street of the quiet hill town."));
}

void Game::run() {
    while (gameRunning) {
        showMainMenu();

        int choice = askChoice("Enter your choice: ", 1, 3);

        if (choice == 1) {
            startNewGame();
        } else if (choice == 2) {
            showHowToPlay();
        } else {
            cout << "\nThank you for playing Midnight Paradox.\n";
            gameRunning = false;
        }
    }
}

void Game::showMainMenu() {
    cout << "\n";
    printDivider();
    cout << "MIDNIGHT PARADOX\n";
    cout << "Detective Time Loop\n";
    printDivider();
    cout << "\n1. Start New Game\n";
    cout << "2. How to Play\n";
    cout << "3. Exit\n\n";
}

void Game::showHowToPlay() {
    cout << "\n";
    printDivider();
    cout << "HOW TO PLAY\n";
    printDivider();
    cout << "\n- You are Mitul. Your friend Harshit Mehra has been murdered,\n";
    cout << "  and the day keeps repeating itself.\n";
    cout << "- Type a number and press Enter to choose an option.\n";
    cout << "- Visit locations, talk to people and collect evidence.\n";
    cout << "- Evidence is stored in your notebook.\n";
    cout << "- The day resets at midnight, but your notebook and your\n";
    cout << "  memories survive the reset.\n";
    cout << "- Suspicion is not proof. Gather reliable evidence before\n";
    cout << "  you accuse anyone.\n";

    cout << "\nWHAT RESETS AT MIDNIGHT        WHAT PERSISTS\n";
    cout << "- The clock (back to 8:00 AM)  - Mitul's memories\n";
    cout << "- Harshit is alive again       - The notebook (every clue)\n";
    cout << "- Conversations and daily      - The loop counter\n";
    cout << "  events of the day            - Suspicion and case progress\n";

    cout << "\nTHE MAIN CHARACTERS:\n";
    // Polymorphism: each Character shows its own introduction.
    for (int i = 0; i < static_cast<int>(characters.size()); i++) {
        characters[i]->introduction();
    }

    endingManager.showEndingPreview();

    waitForContinue();
}

void Game::resetDayFlags() {
    // Temporary world state that resets with every new loop.
    metAaravToday = false;
    metRameshToday = false;
}

// Every loop starts at 8:00 AM.
void Game::startLoopDay() {
    resetDayFlags();
    timeLoop.setTime(8, 0);
}

// Shared midnight ending for Loops 1-9: reset, next morning, continue question.
bool Game::finishLoop(int finishedLoop, const string& title,
                      const string& nextLine) {
    storyManager.midnightResetScene(player, timeLoop);
    timeLoop.resetDay();   // clock back to 8:00 AM, loop counter +1

    storyManager.impossibleMorning(player, timeLoop, finishedLoop);
    storyManager.showLoopComplete(finishedLoop, title, nextLine);

    cout << "\n1. Continue to Loop " << (finishedLoop + 1) << "\n";
    cout << "2. Return to Main Menu\n";
    int choice = askChoice("\nEnter choice: ", 1, 2);

    return (choice == 1);
}

void Game::startNewGame() {
    player.resetInvestigation();
    timeLoop = TimeLoop();
    resetDayFlags();

    if (!playLoop1())  { return; }
    if (!playLoop2())  { return; }
    if (!playLoop3())  { return; }
    if (!playLoop4())  { return; }
    if (!playLoop5())  { return; }
    if (!playLoop6())  { return; }
    if (!playLoop7())  { return; }
    if (!playLoop8())  { return; }
    if (!playLoop9())  { return; }
    playLoop10();
}

bool Game::playLoop1() {
    startLoopDay();

    storyManager.loop1Intro(player, timeLoop);

    timeLoop.setTime(9, 0);
    harshit.harshitLoop1Morning(player, timeLoop);

    timeLoop.setTime(10, 0);
    exploreTownLoop1();

    timeLoop.setTime(14, 0);
    harshit.harshitLoop1Afternoon(player, timeLoop);

    timeLoop.setTime(19, 0);
    aarav.aaravLoop1Evening(player, timeLoop);

    timeLoop.setTime(23, 30);
    storyManager.harshitMessage(player, timeLoop);

    timeLoop.setTime(23, 55);
    storyManager.murderSceneLoop1(player, timeLoop);

    return finishLoop(1, "THE FIRST MURDER",
                      "The same day has started again.");
}

bool Game::playLoop2() {
    startLoopDay();

    storyManager.loop2Morning(player, timeLoop);

    timeLoop.setTime(9, 0);
    bool knowsAboutBackupPhone = harshit.harshitLoop2Morning(player, timeLoop);

    timeLoop.setTime(10, 0);
    storyManager.loop2SearchRoom(player, timeLoop, knowsAboutBackupPhone);

    timeLoop.setTime(11, 0);
    aarav.aaravLoop2Street(player, timeLoop);

    timeLoop.setTime(13, 0);
    ramesh.rameshLoop2Shop(player, timeLoop);

    timeLoop.setTime(16, 0);
    storyManager.loop2NotebookConclusion(player, timeLoop);

    timeLoop.setTime(19, 0);
    harshit.harshitLoop2Evening(player, timeLoop);

    timeLoop.setTime(23, 30);
    storyManager.harshitMessage(player, timeLoop);

    timeLoop.setTime(23, 55);
    storyManager.murderSceneLoop2(player, timeLoop);

    return finishLoop(2, "THE HIDDEN MESSAGE",
                      "Next: Loop 3 - The Witness");
}

void Game::showTownMap() {
    cout << "\n";
    printDivider();
    cout << "TOWN MAP\n";
    cout << "TIME: " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nWhere would you like to go?\n";

    for (int i = 0; i < static_cast<int>(locations.size()); i++) {
        cout << (i + 1) << ". ";
        locations[i].display();
    }

    cout << (locations.size() + 1) << ". Check notebook and case status\n";
    cout << (locations.size() + 2) << ". End exploration and move to evening\n";
}

void Game::exploreTownLoop1() {
    while (true) {
        showTownMap();

        // Map menu: one entry per location + notebook + end option.
        int endChoice = static_cast<int>(locations.size()) + 2;
        int notebookChoice = endChoice - 1;
        int choice = askChoice("\nEnter choice: ", 1, endChoice);

        if (choice == endChoice) {
            cout << "\nMitul decides to head back to Harshit's house.\n";
            waitForContinue();
            break;
        }

        if (choice == notebookChoice) {
            player.showNotebook();
            endingManager.showCaseStatus(player);
            waitForContinue();
        } else {
            visitLocationLoop1(choice);

            // Visiting a place costs about one hour of in-game time.
            timeLoop.advanceMinutes(60);
            cout << "\n[Time passes: +1 hour. It is now "
                 << timeLoop.getTimeString() << ".]\n";

            // Safety: the evening scene begins at 7:00 PM in the story.
            if (timeLoop.getTimeString() == "6:00 PM") {
                cout << "\n(It is getting late. Mitul decides to stop exploring.)\n";
                waitForContinue();
                break;
            }
        }
    }
}

void Game::visitLocationLoop1(int choice) {
    if (choice == 1) {
        locations[0].display();
        harshit.interact(player);
    } else if (choice == 2) {
        locations[1].display();
        if (!metRameshToday) {
            ramesh.rameshLoop1Shop(player, timeLoop);
            metRameshToday = true;
        } else {
            ramesh.interact(player);
        }
    } else if (choice == 3) {
        locations[2].display();
        if (!metAaravToday) {
            aarav.aaravLoop1Street(player, timeLoop);
            metAaravToday = true;
        } else {
            aarav.interact(player);
        }
    }
}

// Visits can happen in either order: first at 9:00 AM, second at 11:00 AM.
void Game::loop3MorningMenu() {
    bool visitedHarshit = false;
    bool visitedRamesh = false;
    bool firstVisit = true;

    while (!visitedHarshit || !visitedRamesh) {
        cout << "\n";
        printDivider();
        cout << "MITUL'S ROOM - MORNING\n";
        printDivider();
        cout << "\n1. Review the notebook.\n";
        if (!visitedHarshit) {
            cout << "2. Go to Harshit's house.\n";
        } else {
            cout << "2. Harshit's house. [done]\n";
        }
        if (!visitedRamesh) {
            cout << "3. Go to Ramesh's shop.\n";
        } else {
            cout << "3. Ramesh's shop. [done]\n";
        }

        int choice = askChoice("\nEnter choice: ", 1, 3);

        if (choice == 1) {
            player.showNotebook();
            endingManager.showCaseStatus(player);
            waitForContinue();
        } else if (choice == 2 && !visitedHarshit) {
            timeLoop.setTime(firstVisit ? 9 : 11, 0);
            firstVisit = false;
            harshit.harshitLoop3Morning(player, timeLoop);
            visitedHarshit = true;
        } else if (choice == 3 && !visitedRamesh) {
            timeLoop.setTime(firstVisit ? 9 : 11, 0);
            firstVisit = false;
            ramesh.rameshLoop3Shop(player, timeLoop);
            visitedRamesh = true;
        } else {
            cout << "\nThat location is already done for this morning.\n";
        }
    }

    cout << "\nMitul now compares everything he has learned.\n";
}

bool Game::playLoop3() {
    startLoopDay();

    storyManager.loop3MorningIntro(player, timeLoop);
    loop3MorningMenu();

    timeLoop.setTime(13, 0);
    storyManager.loop3Timeline(player, timeLoop);

    timeLoop.setTime(16, 0);
    aarav.aaravLoop3Street(player, timeLoop);

    timeLoop.setTime(19, 0);
    harshit.harshitLoop3Evening(player, timeLoop);

    timeLoop.setTime(23, 30);
    storyManager.harshitMessage(player, timeLoop);

    timeLoop.setTime(23, 55);
    storyManager.murderSceneLoop3(player, timeLoop);

    return finishLoop(3, "THE WITNESS",
                      "Next: Loop 4 - The Contradiction");
}

bool Game::playLoop4() {
    startLoopDay();

    storyManager.loop4MorningIntro(player, timeLoop);

    timeLoop.setTime(9, 0);
    harshit.harshitLoop4Morning(player, timeLoop);

    timeLoop.setTime(10, 30);
    aarav.aaravLoop4Confront(player, timeLoop);

    timeLoop.setTime(12, 0);
    ramesh.rameshLoop4Shop(player, timeLoop);

    timeLoop.setTime(14, 0);
    storyManager.loop4AlibiTest(player, timeLoop);

    timeLoop.setTime(17, 0);
    rao.raoLoop4Visit(player, timeLoop);

    timeLoop.setTime(19, 0);
    harshit.harshitLoop4Evening(player, timeLoop);

    timeLoop.setTime(23, 30);
    storyManager.harshitMessage(player, timeLoop);

    timeLoop.setTime(23, 55);
    storyManager.murderSceneLoop4(player, timeLoop);

    return finishLoop(4, "THE CONTRADICTION",
                      "Next: Loop 5 - The Land Records");
}

bool Game::playLoop5() {
    startLoopDay();

    storyManager.loop5MorningIntro(player, timeLoop);

    timeLoop.setTime(9, 0);
    harshit.harshitLoop5Morning(player, timeLoop);

    timeLoop.setTime(10, 30);
    recordsOffice.display();
    clerk.clerkLoop5Morning(player, timeLoop);

    timeLoop.setTime(12, 0);
    ramesh.rameshLoop5Shop(player, timeLoop);

    timeLoop.setTime(14, 0);
    recordsOffice.display();
    clerk.clerkLoop5Afternoon(player, timeLoop);

    timeLoop.setTime(16, 0);
    aarav.aaravLoop5Street(player, timeLoop);

    timeLoop.setTime(19, 0);
    harshit.harshitLoop5Evening(player, timeLoop);

    timeLoop.setTime(23, 30);
    storyManager.harshitMessage(player, timeLoop);

    timeLoop.setTime(23, 55);
    storyManager.murderSceneLoop5(player, timeLoop);

    return finishLoop(5, "THE LAND RECORDS",
                      "Next: Loop 6 - The Timeline");
}

bool Game::playLoop6() {
    startLoopDay();

    storyManager.loop6MorningIntro(player, timeLoop);

    timeLoop.setTime(9, 0);
    harshit.harshitLoop6Morning(player, timeLoop);

    timeLoop.setTime(10, 0);
    storyManager.loop6TimelineBoard(player, timeLoop);

    timeLoop.setTime(12, 0);
    ramesh.rameshLoop6Shop(player, timeLoop);

    timeLoop.setTime(14, 0);
    aarav.aaravLoop6Alibi(player, timeLoop);

    timeLoop.setTime(16, 0);
    rao.raoLoop6Visit(player, timeLoop);

    timeLoop.setTime(19, 0);
    harshit.harshitLoop6Evening(player, timeLoop);

    timeLoop.setTime(23, 30);
    storyManager.harshitMessage(player, timeLoop);

    timeLoop.setTime(23, 55);
    storyManager.murderSceneLoop6(player, timeLoop);

    return finishLoop(6, "THE TIMELINE",
                      "Next: Loop 7 - The Missing Original");
}

bool Game::playLoop7() {
    startLoopDay();

    storyManager.loop7MorningIntro(player, timeLoop);

    timeLoop.setTime(9, 0);
    harshit.harshitLoop7Morning(player, timeLoop);

    timeLoop.setTime(10, 30);
    recordsOffice.display();
    clerk.clerkLoop7Archive(player, timeLoop);

    timeLoop.setTime(12, 30);
    storyManager.loop7MissingPages(player, timeLoop);

    timeLoop.setTime(13, 30);
    recordsOffice.display();
    clerk.clerkLoop7Movement(player, timeLoop);

    timeLoop.setTime(15, 0);
    harshit.harshitLoop7Beneficiary(player, timeLoop);

    timeLoop.setTime(17, 0);
    aarav.aaravLoop7Street(player, timeLoop);

    timeLoop.setTime(19, 0);
    harshit.harshitLoop7Evening(player, timeLoop);

    timeLoop.setTime(23, 30);
    storyManager.harshitMessage(player, timeLoop);

    timeLoop.setTime(23, 55);
    storyManager.murderSceneLoop7(player, timeLoop);

    return finishLoop(7, "THE MISSING ORIGINAL",
                      "Next: Loop 8 - Building the Case");
}

bool Game::playLoop8() {
    startLoopDay();

    storyManager.loop8MorningIntro(player, timeLoop);

    timeLoop.setTime(9, 0);
    rao.raoLoop8Review(player, timeLoop);

    timeLoop.setTime(11, 30);
    rao.raoLoop8Priority(player, timeLoop);

    timeLoop.setTime(13, 0);
    storyManager.loop8RecordRequest(player, timeLoop);

    timeLoop.setTime(15, 0);
    aarav.aaravLoop8Square(player, timeLoop);

    timeLoop.setTime(17, 0);
    rao.raoLoop8Assessment(player, timeLoop);

    timeLoop.setTime(19, 0);
    harshit.harshitLoop8Evening(player, timeLoop);

    timeLoop.setTime(23, 30);
    storyManager.harshitMessage(player, timeLoop);

    timeLoop.setTime(23, 55);
    storyManager.murderSceneLoop8(player, timeLoop);

    return finishLoop(8, "BUILDING THE CASE",
                      "Next: Loop 9 - The Truth Begins to Emerge");
}

bool Game::playLoop9() {
    startLoopDay();

    storyManager.loop9MorningIntro(player, timeLoop);

    timeLoop.setTime(9, 0);
    harshit.harshitLoop9Morning(player, timeLoop);

    timeLoop.setTime(10, 30);
    recordsOffice.display();
    clerk.clerkLoop9Transfer(player, timeLoop);

    timeLoop.setTime(12, 0);
    ramesh.rameshLoop9Argument(player, timeLoop);

    timeLoop.setTime(14, 0);
    aarav.aaravLoop9Confront(player, timeLoop);

    timeLoop.setTime(16, 0);
    rao.raoLoop9Reassess(player, timeLoop);

    timeLoop.setTime(19, 0);
    harshit.harshitLoop9Evening(player, timeLoop);

    timeLoop.setTime(23, 30);
    storyManager.harshitMessage(player, timeLoop);

    timeLoop.setTime(23, 55);
    storyManager.murderSceneLoop9(player, timeLoop);

    return finishLoop(9, "THE TRUTH BEGINS TO EMERGE",
                      "Next: Loop 10 - Breaking the Cycle");
}

// Final loop: the player acts before midnight; decideEnding() picks the ending.

void Game::playLoop10() {
    // The player's decisions in this loop, reported back by the scenes.
    bool speakAarav = false;
    bool protectHarshit = false;
    bool secureRecords = false;
    bool rescueWithoutSupport = false;
    string accusedSuspect = "";

    startLoopDay();

    storyManager.loop10MorningIntro(player, timeLoop);

    timeLoop.setTime(8, 30);
    storyManager.loop10CaseBoard(player, timeLoop);

    timeLoop.setTime(9, 0);
    storyManager.loop10HarshitTruth(player, timeLoop);

    timeLoop.setTime(10, 30);
    storyManager.loop10Plan(player, timeLoop, speakAarav, protectHarshit,
                            secureRecords, accusedSuspect);

    timeLoop.setTime(13, 0);
    storyManager.loop10Questioning(player, timeLoop);

    timeLoop.setTime(16, 0);
    storyManager.loop10MissingPiece(player, timeLoop);

    timeLoop.setTime(19, 0);
    storyManager.loop10SafeNight(player, timeLoop);

    timeLoop.setTime(23, 30);
    storyManager.loop10Message(player, timeLoop, rescueWithoutSupport);

    // Map the prevention objectives onto the ending flags.
    bool harshitSafe = protectHarshit;
    bool inspectorInformed = true;      // Scene 4: Rao is told everything
    bool evidencePreserved = secureRecords;
    bool aaravConfronted = speakAarav;

    int ending = endingManager.decideEnding(
        player, harshitSafe, inspectorInformed, evidencePreserved,
        aaravConfronted, rescueWithoutSupport, accusedSuspect);

    if (ending == EndingManager::ENDING_TRUE_DETECTIVE) {
        storyManager.loop10Confrontation(player, timeLoop);
    }

    endingManager.showEnding(ending);

    cout << "\nThe game returns to the main menu.\n";
}
