# Midnight Paradox: Detective Time Loop

A console-based C++ OOP project (2nd-year college level).

**You are Mitul, a college student trapped in a time loop.**
Your friend Harshit Mehra is murdered at midnight -- and every morning at 8:00 AM,
the day resets. Your notebook is the only thing that survives the reset.
Find the real killer before the loop wins.

- Culprit: **Aarav** | Witness: Ramesh (uncertain) | Investigator: Inspector Rao
- 10 loops of scripted investigation, and exactly 4 possible endings.

---

## 1. How to build and run

You need a C++ compiler with C++17 support (g++ from MinGW on Windows, or g++/clang on Linux/macOS).

### Windows (Command Prompt, MinGW g++)

    cd MidnightParadox-PBL
    g++ -std=c++17 -Wall -Wextra -o MidnightParadox.exe src\main.cpp src\Game.cpp src\Player.cpp src\Character.cpp src\NPC.cpp src\Location.cpp src\Evidence.cpp src\Notebook.cpp src\TimeLoop.cpp src\StoryManager.cpp src\EndingManager.cpp
    ./MidnightParadox.exe

### Linux / macOS

    cd MidnightParadox-PBL
    g++ -std=c++17 -Wall -Wextra -o MidnightParadox src/main.cpp src/Game.cpp src/Player.cpp src/Character.cpp src/NPC.cpp src/Location.cpp src/Evidence.cpp src/Notebook.cpp src/TimeLoop.cpp src/StoryManager.cpp src/EndingManager.cpp
    ./MidnightParadox

That is the whole build. No makefile, no extra setup, no external libraries.

> Note: `src/Declarations.cpp` is intentionally left out of the compiler command.
> The other files `#include` it -- it holds the shared declarations (this project
> uses no `.h` header files; that is a documented design decision).

## 2. How to play

- Everything is menu-driven: type the number of your choice and press Enter.
- The **notebook** can be reviewed from the town map and morning menus (evidence collected so far).
- A typical loop: investigate the morning -> talk to people -> check the notebook
  and the **Case Status** in the evening -> midnight ends the loop -> the day resets.
- Your notebook and suspicion survive the reset -- story choices do not.
- On the final loop you will name a suspect and choose how the story ends.

## 3. Project structure

    MidnightParadox-PBL/
    |-- README.md                this file: build, run, overview
    |-- src/                     all source code (.cpp files only)
    |   |-- main.cpp             entry point
    |   |-- Declarations.cpp     shared declarations (included; never compiled alone)
    |   |-- Game.cpp             game loop + all 10 loop drivers
    |   |-- StoryManager.cpp     all story text and scenes
    |   |-- EndingManager.cpp    ending selection + 4 ending scenes
    |   |-- Player.cpp           player + notebook access
    |   |-- NPC.cpp              Ramesh / Inspector Rao / Harshit / Aarav dialogue
    |   |-- Character.cpp        base class
    |   |-- Location.cpp         rooms
    |   |-- Evidence.cpp         evidence items + reliability label
    |   |-- Notebook.cpp         persistent notebook
    |   `-- TimeLoop.cpp         clock, day reset, victim state
    `-- docs/
        |-- PROJECT_GUIDE.md     how the whole project works, explained simply
        |-- PBL_VIVA_QUESTIONS.md  viva preparation: questions + answers
        `-- Test_Report.md       how the project was tested

## 4. OOP concepts used

| Concept        | Where                                                  |
|----------------|--------------------------------------------------------|
| Classes/objects| every class; `Game` owns the objects                    |
| Encapsulation  | private members + getters/setters                       |
| Inheritance    | `NPC` and `Player` extend `Character`                   |
| Polymorphism   | `virtual introduction()` / `interact()` overridden      |
| Abstraction    | each class hides its own details                        |
| Composition    | `Player` has a `Notebook`, `Game` has `TimeLoop`        |

### Class guide (quick reference for the viva)

| Class | What it represents | Main functions |
|---|---|---|
| `Evidence` | one clue with a reliability label | `getId`, `display` |
| `Notebook` | Mitul's memory (survives the reset) | `addEvidence` (no duplicates), `hasEvidence`, `display` |
| `TimeLoop` | clock + loop counter | `setTime`, `getTimeString`, `resetDay` |
| `Location` | one place on the town map | `display` |
| `Character` | base class for people | `introduction()`, `interact()` (virtual) |
| `Player` | Mitul (the detective) | `showNotebook`, `increaseSuspicion`, `resetInvestigation` |
| `NPC` | Harshit, Aarav, Ramesh, Rao, the clerk | one function per conversation |
| `StoryManager` | the scripted story scenes | `loop1Intro`, `murderSceneLoopN`, `loop10Plan` |
| `EndingManager` | progress screen + the four endings | `showCaseStatus`, `decideEnding`, `showEnding` |
| `Game` | menu and flow; owns every object | `run`, `playLoop1`..`playLoop10`, `startLoopDay`, `finishLoop` |

**Program flow:** `main()` -> `Game::run()` -> main menu -> `startNewGame()`
-> `playLoop1()` .. `playLoop10()` -> `decideEnding()` -> `showEnding()` ->
back to the menu. Each `playLoopN` is a scene list: `startLoopDay()` sets
8:00 AM, scene functions advance the clock and talk, `finishLoop()` plays
the midnight reset and asks whether to continue.

## 5. The four endings (deterministic -- no randomness)

| Ending          | How you reach it                                                            |
|-----------------|-----------------------------------------------------------------------------|
| False Accusation| accuse the wrong person                                                     |
| Sacrifice       | rescue Harshit without support; Ramesh dies                                 |
| True Detective  | protect Harshit, inform the inspector, secure records, confront Aarav, with strong proof |
| Endless Loop    | none of the above -- the loop continues                                     |

## 6. How to test quickly (manual)

1. Build and start the game -> the title screen and main menu appear.
2. Choose `1` (New Game) -> Loop 1 starts at 8:00 AM.
3. In the Loop 1 town map choose `4` -> the notebook opens (empty at first).
4. Enter an invalid choice (`9`, `abc`, `0` where not allowed) -> the game re-prompts; it never crashes.
5. Play with mostly `1`s to see the day reset at midnight.

For the full test history (ending-selection unit tests, the scripted all-10-loops run,
invalid-input handling, and the four ending variants), see `docs/Test_Report.md`.
For a complete walkthrough of every class and system, see `docs/PROJECT_GUIDE.md`.
For viva preparation (60+ questions with answers), see `docs/PBL_VIVA_QUESTIONS.md`.
