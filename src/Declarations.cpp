#pragma once

// Declarations.cpp - shared class declarations (this project uses no .h files).
// Every .cpp includes this file, and it is NEVER compiled on its own
// (keep it out of the g++ command). It holds only declarations, so including
// it in many files creates no duplicate symbols.

#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <cstdlib>
using namespace std;

// Console input helpers (defined once in Game.cpp).
void printDivider();
void waitForContinue();
int askChoice(const string& prompt, int minChoice, int maxChoice);

// Evidence: one clue. The reliability label keeps the investigation honest:
// "Suspicion", "Lead", "Uncertain", "Evidence", "Verified". Suspicion or an
// uncertain sighting is never treated as proof.
//
class Evidence {
private:
    string id;
    string name;
    string description;
    string reliability;

public:
    Evidence(const string& id, const string& name,
             const string& description, const string& reliability);
    string getId() const;
    string getName() const;
    string getDescription() const;
    string getReliability() const;
    void display() const;
};

// Notebook: Mitul's notes; they survive the time loop.
class Notebook {
private:
    vector<Evidence> entries;

public:
    bool hasEvidence(const string& id) const;
    bool addEvidence(const Evidence& evidence);
    void display() const;
    int size() const;
    int countReliability(const string& reliability) const;
    void clear();
};

// TimeLoop: clock, loop counter and daily reset.
class TimeLoop {
private:
    int currentLoop;
    int minutesSinceMidnight;   // 8:00 AM is 480
    bool victimAlive;           // temporary world state, reset every day

public:
    TimeLoop();
    int getCurrentLoop() const;
    void setTime(int hour, int minute);
    void advanceMinutes(int minutes);
    string getTimeString() const;
    bool hasReached(int hour, int minute) const;
    bool isVictimAlive() const;
    void setVictimAlive(bool alive);
    void resetDay();            // new loop, clock back to 8:00 AM
};

// Location: one place on the town.
class Location {
private:
    string name;
    string description;

public:
    Location(const string& name, const string& description);
    string getName() const;
    string getDescription() const;
    void display() const;
};

// Player is used inside Character, so we announce it first.
class Player;

// Character: base class for every person.
class Character {
protected:
    string name;
    string role;

public:
    Character(const string& name, const string& role);
    virtual ~Character();
    string getName() const;
    string getRole() const;
    virtual void introduction() const;
    virtual void interact(Player& player);
};

// Player: Mitul.
class Player : public Character {
private:
    Notebook notebook;
    int suspicionOfAarav;       // 0 to 10, suspicion is NOT proof

public:
    Player(const string& playerName);
    void interact(Player& player) override;
    Notebook& getNotebook();
    const Notebook& getNotebook() const;
    int getSuspicionOfAarav() const;
    void increaseSuspicion(int amount);
    void showNotebook() const;
    void resetInvestigation();
};

// NPC: Harshit, Aarav, Ramesh, Inspector Rao, records clerk.
class NPC : public Character {
private:
    string greeting;

public:
    NPC(const string& name, const string& role, const string& greeting);
    void interact(Player& player) override;

    void harshitLoop1Morning(Player& player, TimeLoop& timeLoop);
    void harshitLoop1Afternoon(Player& player, TimeLoop& timeLoop);
    void aaravLoop1Street(Player& player, TimeLoop& timeLoop);
    void aaravLoop1Evening(Player& player, TimeLoop& timeLoop);
    void rameshLoop1Shop(Player& player, TimeLoop& timeLoop);

    bool harshitLoop2Morning(Player& player, TimeLoop& timeLoop);
    void aaravLoop2Street(Player& player, TimeLoop& timeLoop);
    void rameshLoop2Shop(Player& player, TimeLoop& timeLoop);
    void harshitLoop2Evening(Player& player, TimeLoop& timeLoop);

    void harshitLoop3Morning(Player& player, TimeLoop& timeLoop);
    void rameshLoop3Shop(Player& player, TimeLoop& timeLoop);
    void aaravLoop3Street(Player& player, TimeLoop& timeLoop);
    void harshitLoop3Evening(Player& player, TimeLoop& timeLoop);

    void harshitLoop4Morning(Player& player, TimeLoop& timeLoop);
    void aaravLoop4Confront(Player& player, TimeLoop& timeLoop);
    void rameshLoop4Shop(Player& player, TimeLoop& timeLoop);
    void raoLoop4Visit(Player& player, TimeLoop& timeLoop);
    void harshitLoop4Evening(Player& player, TimeLoop& timeLoop);

    void harshitLoop5Morning(Player& player, TimeLoop& timeLoop);
    void clerkLoop5Morning(Player& player, TimeLoop& timeLoop);
    void rameshLoop5Shop(Player& player, TimeLoop& timeLoop);
    void clerkLoop5Afternoon(Player& player, TimeLoop& timeLoop);
    void aaravLoop5Street(Player& player, TimeLoop& timeLoop);
    void harshitLoop5Evening(Player& player, TimeLoop& timeLoop);

    void harshitLoop6Morning(Player& player, TimeLoop& timeLoop);
    void rameshLoop6Shop(Player& player, TimeLoop& timeLoop);
    void aaravLoop6Alibi(Player& player, TimeLoop& timeLoop);
    void raoLoop6Visit(Player& player, TimeLoop& timeLoop);
    void harshitLoop6Evening(Player& player, TimeLoop& timeLoop);

    void harshitLoop7Morning(Player& player, TimeLoop& timeLoop);
    void clerkLoop7Archive(Player& player, TimeLoop& timeLoop);
    void clerkLoop7Movement(Player& player, TimeLoop& timeLoop);
    void harshitLoop7Beneficiary(Player& player, TimeLoop& timeLoop);
    void aaravLoop7Street(Player& player, TimeLoop& timeLoop);
    void harshitLoop7Evening(Player& player, TimeLoop& timeLoop);

    void raoLoop8Review(Player& player, TimeLoop& timeLoop);
    void raoLoop8Priority(Player& player, TimeLoop& timeLoop);
    void aaravLoop8Square(Player& player, TimeLoop& timeLoop);
    void raoLoop8Assessment(Player& player, TimeLoop& timeLoop);
    void harshitLoop8Evening(Player& player, TimeLoop& timeLoop);

    void harshitLoop9Morning(Player& player, TimeLoop& timeLoop);
    void clerkLoop9Transfer(Player& player, TimeLoop& timeLoop);
    void rameshLoop9Argument(Player& player, TimeLoop& timeLoop);
    void aaravLoop9Confront(Player& player, TimeLoop& timeLoop);
    void raoLoop9Reassess(Player& player, TimeLoop& timeLoop);
    void harshitLoop9Evening(Player& player, TimeLoop& timeLoop);
};

// StoryManager: scripted story events and narration.
class StoryManager {
private:
    void printMurderDiscovery(TimeLoop& timeLoop);

public:
    void loop1Intro(Player& player, TimeLoop& timeLoop);
    void harshitMessage(Player& player, TimeLoop& timeLoop);
    void murderSceneLoop1(Player& player, TimeLoop& timeLoop);
    void murderSceneLoop2(Player& player, TimeLoop& timeLoop);
    void midnightResetScene(Player& player, TimeLoop& timeLoop);
    void impossibleMorning(Player& player, TimeLoop& timeLoop, int finishedLoop);
    void loop2Morning(Player& player, TimeLoop& timeLoop);
    void loop2SearchRoom(Player& player, TimeLoop& timeLoop, bool knowsAboutBackupPhone);
    void loop2NotebookConclusion(Player& player, TimeLoop& timeLoop);
    void showLoopComplete(int finishedLoop, const string& title, const string& nextLine);

    void loop3MorningIntro(Player& player, TimeLoop& timeLoop);
    void loop3Timeline(Player& player, TimeLoop& timeLoop);
    void murderSceneLoop3(Player& player, TimeLoop& timeLoop);
    void loop4MorningIntro(Player& player, TimeLoop& timeLoop);
    void loop4AlibiTest(Player& player, TimeLoop& timeLoop);
    void murderSceneLoop4(Player& player, TimeLoop& timeLoop);
    void loop5MorningIntro(Player& player, TimeLoop& timeLoop);
    void murderSceneLoop5(Player& player, TimeLoop& timeLoop);

    void loop6MorningIntro(Player& player, TimeLoop& timeLoop);
    void loop6TimelineBoard(Player& player, TimeLoop& timeLoop);
    void murderSceneLoop6(Player& player, TimeLoop& timeLoop);
    void loop7MorningIntro(Player& player, TimeLoop& timeLoop);
    void loop7MissingPages(Player& player, TimeLoop& timeLoop);
    void murderSceneLoop7(Player& player, TimeLoop& timeLoop);
    void loop8MorningIntro(Player& player, TimeLoop& timeLoop);
    void loop8RecordRequest(Player& player, TimeLoop& timeLoop);
    void murderSceneLoop8(Player& player, TimeLoop& timeLoop);

    void loop9MorningIntro(Player& player, TimeLoop& timeLoop);
    void murderSceneLoop9(Player& player, TimeLoop& timeLoop);

    // Loop 10 scenes report the player's decisions back through reference parameters.
    void loop10MorningIntro(Player& player, TimeLoop& timeLoop);
    void loop10CaseBoard(Player& player, TimeLoop& timeLoop);
    void loop10HarshitTruth(Player& player, TimeLoop& timeLoop);
    void loop10Plan(Player& player, TimeLoop& timeLoop,
                    bool& speakAarav, bool& protectHarshit,
                    bool& secureRecords, string& accusedSuspect);
    void loop10Questioning(Player& player, TimeLoop& timeLoop);
    void loop10MissingPiece(Player& player, TimeLoop& timeLoop);
    void loop10SafeNight(Player& player, TimeLoop& timeLoop);
    void loop10Message(Player& player, TimeLoop& timeLoop,
                       bool& rescueWithoutSupport);
    void loop10Confrontation(Player& player, TimeLoop& timeLoop);
};

// EndingManager: case status + the four endings. decideEnding is deterministic
// (never random): wrong accusation -> False Accusation, rescue without support
// -> Sacrifice, proof + all actions -> True Detective, else -> Endless Loop.
//
class EndingManager {
public:
    enum EndingType {
        ENDING_FALSE_ACCUSATION = 1,
        ENDING_SACRIFICE = 2,
        ENDING_ENDLESS_LOOP = 3,
        ENDING_TRUE_DETECTIVE = 4
    };

    // Investigation progress (used by the in-game Case Status screen).
    void showCaseStatus(const Player& player) const;
    bool hasSufficientProof(const Player& player) const;

    int decideEnding(const Player& player,
                     bool harshitSafe,
                     bool inspectorInformed,
                     bool evidencePreserved,
                     bool aaravConfronted,
                     bool rescueWithoutSupport,
                     const string& accusedSuspect) const;

    string endingName(int endingId) const;
    void showEndingPreview() const;
    void showEnding(int endingId) const;
};

// Game: menu, flow and connections.
class Game {
private:
    Player player;
    TimeLoop timeLoop;
    StoryManager storyManager;
    EndingManager endingManager;
    NPC harshit;
    NPC aarav;
    NPC ramesh;
    NPC rao;
    NPC clerk;
    vector<Character*> characters;
    vector<Location> locations;
    Location recordsOffice;
    bool gameRunning;
    bool metAaravToday;
    bool metRameshToday;

    void showMainMenu();
    void showHowToPlay();
    void startNewGame();
    bool playLoop1();
    bool playLoop2();
    bool playLoop3();
    bool playLoop4();
    bool playLoop5();
    bool playLoop6();
    bool playLoop7();
    bool playLoop8();
    bool playLoop9();
    void playLoop10();
    void loop3MorningMenu();
    void exploreTownLoop1();
    void visitLocationLoop1(int choice);
    void showTownMap();
    void resetDayFlags();
    void startLoopDay();
    bool finishLoop(int finishedLoop, const string& title,
                    const string& nextLine);

public:
    Game();
    void run();
};
