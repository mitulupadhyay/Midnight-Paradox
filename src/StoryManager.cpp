// StoryManager.cpp - scripted story scenes (conversations live in NPC.cpp).

#include "Declarations.cpp"

void StoryManager::loop1Intro(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "DAY 1 - " << timeLoop.getTimeString() << "\n";
    printDivider();

    cout << "\n" << player.getName() << "'s phone vibrates.\n\n";
    cout << "HARSHIT: \"Come alone tonight. I found something.\"\n\n";
    cout << "Last week he said the old property records were wrong.\n";
    cout << "Today he stopped answering questions.\n";

    waitForContinue();
}

void StoryManager::harshitMessage(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "HARSHIT'S HOUSE - " << timeLoop.getTimeString() << "\n";
    printDivider();

    cout << "\nHarshit's phone buzzes on the table. A draft, never sent.\n\n";
    cout << "HARSHIT: \"" << player.getName() << ", if something happens tonight, the answer is "
         << "in the register. Don't trust Aarav with it.\"\n";

    cout << "\n1. Read it twice.\n";
    cout << "2. Look out the window.\n";
    int choice = askChoice("\nEnter choice: ", 1, 2);

    if (choice == 1) {
        cout << "\nYou read it again. The fear is in the wording.\n";
    } else {
        cout << "\nA shape moves at the end of the road. Gone when "
             << "you focus.\n";
    }
    waitForContinue();
}

// Shared murder discovery, reused by every loop.
void StoryManager::printMurderDiscovery(TimeLoop& timeLoop) {
    printDivider();
    cout << timeLoop.getTimeString() << " - HARSHIT'S HOUSE\n";
    printDivider();

    cout << "\nThe front door is open an inch.\n";
    cout << "\"Harshit?\" No answer.\n";
    cout << "You find him on the floor. Motionless.\n";
    timeLoop.setVictimAlive(false);
}

// The murder nights: short suspense beats, always the same ending.
// Each scene records FIRST_MURDER once (duplicate prevention).

void StoryManager::murderSceneLoop1(Player& player, TimeLoop& timeLoop) {
    cout << "\n11:47 PM - Harshit is not answering.\n";
    cout << "11:51 PM - Someone knocks on the door.\n";
    cout << "11:53 PM - Your phone loses signal.\n";
    cout << "11:55 PM - A crash comes from inside the house.\n";

    cout << "\n1. Enter the house.\n";
    cout << "2. Call Inspector Rao.\n";
    cout << "3. Look for another entrance.\n";
    int choice = askChoice("\nEnter choice: ", 1, 3);

    if (choice == 1) {
        cout << "\nYou shoulder the door open.\n";
    } else if (choice == 2) {
        cout << "\nThe call does not connect. You run for the door.\n";
    } else {
        cout << "\nThe side window is shattered from the inside. "
             << "Too late.\n";
    }

    printMurderDiscovery(timeLoop);
    if (player.getNotebook().addEvidence(Evidence(
            "FIRST_MURDER",
            "Harshit was murdered shortly before midnight",
            "Mitul found Harshit dead in his house just before midnight. "
            "Aarav appeared at the doorway moments later.",
            "Evidence"))) {
        cout << "\n[Clue recorded: FIRST_MURDER]\n";
    }
    waitForContinue();
}

void StoryManager::murderSceneLoop2(Player& player, TimeLoop& timeLoop) {
    cout << "\n11:46 PM - The streetlights outside flicker off.\n";
    cout << "11:52 PM - Harshit's window goes dark.\n";
    cout << "11:55 PM - Silence. Then a single sound you will "
         << "never forget.\n";

    cout << "\n1. Run inside.\n";
    cout << "2. Circle the house first.\n";
    int choice = askChoice("\nEnter choice: ", 1, 2);

    if (choice == 1) {
        cout << "\nYou take the steps three at a time.\n";
    } else {
        cout << "\nYou circle too slowly. Everyone does.\n";
    }

    printMurderDiscovery(timeLoop);
    if (!player.getNotebook().addEvidence(Evidence(
            "FIRST_MURDER",
            "Harshit was murdered shortly before midnight",
            "Mitul found Harshit dead in his house just before midnight.",
            "Evidence"))) {
        cout << "\n[Already recorded: FIRST_MURDER]\n";
    }
    waitForContinue();
}

void StoryManager::murderSceneLoop3(Player& player, TimeLoop& timeLoop) {
    cout << "\n11:40 PM - Ramesh's shutter slams shut early.\n";
    cout << "11:49 PM - A shadow crosses Harshit's gate.\n";
    cout << "11:55 PM - The same sound. The same silence.\n";

    printMurderDiscovery(timeLoop);
    if (!player.getNotebook().addEvidence(Evidence(
            "FIRST_MURDER",
            "Harshit was murdered shortly before midnight",
            "Mitul found Harshit dead in his house just before midnight.",
            "Evidence"))) {
        cout << "\n[Already recorded: FIRST_MURDER]\n";
    }
    waitForContinue();
}

void StoryManager::murderSceneLoop4(Player& player, TimeLoop& timeLoop) {
    cout << "\n11:44 PM - A car with no lights stops at the corner.\n";
    cout << "11:51 PM - Harshit whispers: \"Someone's in the garden.\"\n";
    cout << "11:55 PM - Then the sound.\n";

    cout << "\n1. Check the garden.\n";
    cout << "2. Stay at Harshit's side.\n";
    int choice = askChoice("\nEnter choice: ", 1, 2);

    if (choice == 1) {
        cout << "\nEmpty garden. Open gate. You chose wrong again.\n";
    } else {
        cout << "\nThe crash comes from the hallway. "
             << "You still chose wrong.\n";
    }

    printMurderDiscovery(timeLoop);
    if (!player.getNotebook().addEvidence(Evidence(
            "FIRST_MURDER",
            "Harshit was murdered shortly before midnight",
            "Mitul found Harshit dead in his house just before midnight.",
            "Evidence"))) {
        cout << "\n[Already recorded: FIRST_MURDER]\n";
    }
    waitForContinue();
}

void StoryManager::murderSceneLoop5(Player& player, TimeLoop& timeLoop) {
    cout << "\n11:48 PM - Harshit stacks the forged file by the door. "
         << "\"Take it if I can't.\"\n";
    cout << "11:53 PM - Knocking. Soft. Patient.\n";
    cout << "11:55 PM - The sound.\n";

    printMurderDiscovery(timeLoop);
    if (!player.getNotebook().addEvidence(Evidence(
            "FIRST_MURDER",
            "Harshit was murdered shortly before midnight",
            "Mitul found Harshit dead in his house just before midnight.",
            "Evidence"))) {
        cout << "\n[Already recorded: FIRST_MURDER]\n";
    }
    waitForContinue();
}

void StoryManager::murderSceneLoop6(Player& player, TimeLoop& timeLoop) {
    cout << "\n11:30 PM - The board on the wall tells you everything "
         << "except how to stop this.\n";
    cout << "11:50 PM - The house creaks in the wrong places.\n";
    cout << "11:55 PM - The sound. On time. Every time.\n";

    printMurderDiscovery(timeLoop);
    if (!player.getNotebook().addEvidence(Evidence(
            "FIRST_MURDER",
            "Harshit was murdered shortly before midnight",
            "Mitul found Harshit dead in his house just before midnight.",
            "Evidence"))) {
        cout << "\n[Already recorded: FIRST_MURDER]\n";
    }
    waitForContinue();
}

void StoryManager::murderSceneLoop7(Player& player, TimeLoop& timeLoop) {
    cout << "\n11:45 PM - The movement log you copied feels heavy "
         << "in your pocket.\n";
    cout << "11:52 PM - Footsteps stop outside the door. They do "
         << "not knock.\n";
    cout << "11:55 PM - The sound.\n";

    printMurderDiscovery(timeLoop);
    if (!player.getNotebook().addEvidence(Evidence(
            "FIRST_MURDER",
            "Harshit was murdered shortly before midnight",
            "Mitul found Harshit dead in his house just before midnight.",
            "Evidence"))) {
        cout << "\n[Already recorded: FIRST_MURDER]\n";
    }
    waitForContinue();
}

void StoryManager::murderSceneLoop8(Player& player, TimeLoop& timeLoop) {
    cout << "\n11:42 PM - Rao's patrol passes the house. It will not "
         << "pass again before midnight.\n";
    cout << "11:54 PM - A tap at the window. Then the door gives.\n";
    cout << "11:55 PM - The sound.\n";

    printMurderDiscovery(timeLoop);
    if (!player.getNotebook().addEvidence(Evidence(
            "FIRST_MURDER",
            "Harshit was murdered shortly before midnight",
            "Mitul found Harshit dead in his house just before midnight.",
            "Evidence"))) {
        cout << "\n[Already recorded: FIRST_MURDER]\n";
    }
    waitForContinue();
}

void StoryManager::murderSceneLoop9(Player& player, TimeLoop& timeLoop) {
    cout << "\n11:38 PM - The pieces finally connect on the page.\n";
    cout << "11:52 PM - Harshit: \"Whatever happens - you almost "
         << "solved it.\"\n";
    cout << "11:55 PM - The sound. Last time, if you let it.\n";

    printMurderDiscovery(timeLoop);
    if (!player.getNotebook().addEvidence(Evidence(
            "FIRST_MURDER",
            "Harshit was murdered shortly before midnight",
            "Mitul found Harshit dead in his house just before midnight.",
            "Evidence"))) {
        cout << "\n[Already recorded: FIRST_MURDER]\n";
    }
    waitForContinue();
}

void StoryManager::midnightResetScene(Player& player, TimeLoop& timeLoop) {
    timeLoop.setTime(0, 0);

    printDivider();
    cout << timeLoop.getTimeString() << "\n";
    printDivider();

    cout << "\nThe clock stops.\n";
    cout << "The room goes silent.\n";
    cout << "You feel the floor tilt under you.\n\n";
    cout << "THE DAY HAS ENDED.\n\n";
    cout << "(Your notebook still holds " << player.getNotebook().size()
         << " entries. The notebook survives.)\n";

    waitForContinue();
}

void StoryManager::impossibleMorning(Player& player, TimeLoop& timeLoop, int finishedLoop) {
    timeLoop.setTime(8, 0);

    printDivider();
    cout << "DAY " << (finishedLoop + 1) << " - " << timeLoop.getTimeString() << "\n";
    printDivider();

    cout << "\nYour phone vibrates.\n";
    cout << "HARSHIT: \"Come alone tonight. I found something.\"\n";
    cout << "The same message. The same day. Again.\n";

    if (player.getNotebook().size() > 0) {
        cout << "\nBut your notebook still holds "
             << player.getNotebook().size() << " clues.\n";
    }

    if (finishedLoop == 1) {
        cout << "\nYesterday Harshit died at midnight. Today he is alive.\n";
        cout << "The message on his phone - you can find it faster now.\n";
    } else if (finishedLoop == 2) {
        cout << "\nThe draft message mentioned the original register.\n";
        cout << "Someone hid it. Someone moved it. Find out who.\n";
    } else if (finishedLoop == 3) {
        cout << "\nRamesh's story and Aarav's story do not match.\n";
        cout << "Today, press both of them harder.\n";
    } else if (finishedLoop == 4) {
        cout << "\nRamesh is sure of the time, unsure of the face.\n";
        cout << "The records office is where certainty lives.\n";
    } else if (finishedLoop == 5) {
        cout << "\nThe file was forged. Now reconstruct the night itself.\n";
    } else if (finishedLoop == 6) {
        cout << "\nThe figure left at 10:15. The register was moved.\n";
        cout << "Follow the register.\n";
    } else if (finishedLoop == 7) {
        cout << "\nYou have the altered copy and the movement log.\n";
        cout << "Rao needs to see the whole picture.\n";
    } else if (finishedLoop == 8) {
        cout << "\nDocuments. Place. Transfer link. You have pieces of each.\n";
        cout << "One more day to connect them.\n";
    } else if (finishedLoop == 9) {
        cout << "\nAarav's story has cracks. The transfer link matches.\n";
        cout << "Tonight, act before the clock reaches midnight.\n";
    }

    waitForContinue();
}

void StoryManager::loop2Morning(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "DAY 2 - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\n" << player.getName() << " knows this day. Use it.\n";
    cout << "Harshit mentioned a backup phone yesterday. "
         << "Old papers. A draft message.\n";
}

// Searching Harshit's room. knowsAboutBackupPhone = Harshit mentioned
// the backup phone, so the player knows where to look first.
void StoryManager::loop2SearchRoom(Player& player, TimeLoop& timeLoop,
                                   bool knowsAboutBackupPhone) {
    printDivider();
    cout << "HARSHIT'S ROOM - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nHarshit is downstairs. You have a few minutes.\n";

    bool searchedPapers = false;
    bool searchedDesk = false;
    bool checkedDrawer = false;
    while (true) {
        cout << "\n1. Inspect the desk.\n";
        cout << "2. Look under the papers.\n";
        cout << "3. Check the drawer.\n";
        cout << "4. Leave the room.\n";

        int choice = askChoice("\nEnter choice: ", 1, 4);
        if (choice == 4) {
            break;
        }
        if (choice == 1) {
            if (searchedDesk) {
                cout << "\nYou already searched the desk.\n";
            } else {
                cout << "\nScrap notes. Numbers. "
                     << "A traced signature in pencil.\n";
                searchedDesk = true;
            }
        } else if (choice == 2) {
            if (searchedPapers) {
                cout << "\nThe phone is already in your bag.\n";
                continue;
            }
            if (knowsAboutBackupPhone) {
                cout << "\nA backup phone. Harshit told you exactly "
                     << "where to look.\n";
            } else {
                cout << "\nOld papers... and the corner of a phone "
                     << "underneath them.\n";
            }
            cout << "\nA draft message is open on the screen:\n\n";
            cout << "   \"The original register proves everything. "
                 << "Aarav must not find it.\"\n";

            if (player.getNotebook().addEvidence(Evidence(
                    "PHONE_MESSAGE",
                    "Harshit's draft warns about Aarav and the register",
                    "Draft on Harshit's backup phone: 'The original "
                    "register proves everything. Aarav must not find it.' "
                    "This does NOT prove that Aarav is the killer.",
                    "Evidence"))) {
                cout << "\n[Clue discovered: PHONE_MESSAGE]\n";
            }
            searchedPapers = true;
        } else {
            if (checkedDrawer) {
                cout << "\nStill locked.\n";
            } else {
                cout << "\nLocked. And it was locked from the outside. "
                     << "Odd.\n";
                checkedDrawer = true;
            }
        }
    }

    if (!searchedPapers) {
        cout << "\nYou leave the room. Something under those papers "
             << "will have to wait for tomorrow.\n";
    }
}

void StoryManager::loop2NotebookConclusion(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "HARSHIT'S HOUSE - " << timeLoop.getTimeString() << "\n";
    printDivider();

    cout << "\nYou open your notebook and lay the day side by side.\n";
    cout << "Aarav says he knows nothing about any original record.\n";

    if (player.getNotebook().hasEvidence("PHONE_MESSAGE")) {
        cout << "Harshit's draft says the opposite.\n";
        cout << "One of them is lying. The notebook noticed.\n";
    } else {
        cout << "Without Harshit's draft, it is his word against "
             << "suspicion. Find that phone.\n";
    }
    waitForContinue();
}

void StoryManager::showLoopComplete(int finishedLoop, const string& title,
                                    const string& nextLine) {
    cout << "\n";
    printDivider();
    cout << "LOOP " << finishedLoop << " COMPLETE - " << title << "\n";
    cout << nextLine << "\n";
    printDivider();
}

// ============================= LOOP 3 =============================

void StoryManager::loop3MorningIntro(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "DAY 3 - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\n" << player.getName() << " has two versions of one night. Ramesh's and Aarav's.\n";
    cout << "Today you put them side by side.\n";
}

void StoryManager::loop3Timeline(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "TIMELINE - " << timeLoop.getTimeString() << "\n";
    printDivider();

    cout << "\n1. Compare Ramesh's 9:30 sighting with Aarav's alibi.\n";
    cout << "2. Compare both with Harshit's warning.\n";
    cout << "3. Stop for now.\n";
    int choice = askChoice("\nEnter choice: ", 1, 3);

    if (choice == 1) {
        cout << "\nAarav: home all night. Ramesh: a figure at 9:30.\n";
        cout << "Both cannot be true.\n";
    } else if (choice == 2) {
        cout << "\nHarshit said don't trust Aarav. The night proved him "
             << "right - so far.\n";
    }

    if (choice != 3) {
        if (player.getNotebook().addEvidence(Evidence(
                "TIMELINE_NOTES",
                "Mitul's timeline of the murder night",
                "Sighting at 9:30, Aarav claims he was home, warning at "
                "11:30 PM, murder at 11:55 PM. The accounts conflict.",
                "Lead"))) {
            cout << "\n[Clue noted: TIMELINE_NOTES]\n";
        }
    }
}

// ============================= LOOP 4 =============================

void StoryManager::loop4MorningIntro(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "DAY 4 - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\n" << player.getName() << " faces a witness who is almost sure, a suspect who is never "
         << "sure enough.\n";
}

void StoryManager::loop4AlibiTest(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "TIMELINE - " << timeLoop.getTimeString() << "\n";
    printDivider();

    cout << "\n" << player.getName() << " writes the alibi and the sighting on opposite sides "
         << "of a page.\n";
    cout << "\n1. Test what Aarav said against what Ramesh saw.\n";
    cout << "2. Leave it on the page.\n";
    int choice = askChoice("\nEnter choice: ", 1, 2);

    if (choice == 1) {
        cout << "\n'Home reading' vs 'figure at 9:30, another at 10:15'.\n";
        cout << "An alibi you 'think' you kept is not an alibi.\n";
        cout << "But a figure is not a face. Both gaps remain.\n";
    }
    waitForContinue();
}

// ============================= LOOP 5 =============================

void StoryManager::loop5MorningIntro(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "DAY 5 - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nHarshit gave " << player.getName() << " a key. The records office holds the "
         << "paper truth.\n";
}

// ============================= LOOP 6 =============================

void StoryManager::loop6MorningIntro(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "DAY 6 - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nOne night. Four moments. " << player.getName() << " builds the truth from the gaps.\n";
}

void StoryManager::loop6TimelineBoard(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "THE BOARD - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\n" << player.getName() << " studies the board.\n";

    bool pinned1 = false;
    bool pinned2 = false;
    bool pinned3 = false;
    while (true) {
        cout << "\n1. Pin the 9:30 sighting.\n";
        cout << "2. Pin the 10:15 return.\n";
        cout << "3. Pin the 11:30 message.\n";
        cout << "4. Step back.\n";

        int choice = askChoice("\nEnter choice: ", 1, 4);
        if (choice == 4) {
            break;
        }
        if (choice == 1) {
            if (pinned1) {
                cout << "\nThat pin is already on the board.\n";
            } else {
                cout << "\n9:30 - figure near the gate. No face.\n";
                pinned1 = true;
            }
        } else if (choice == 2) {
            if (pinned2) {
                cout << "\nThat pin is already on the board.\n";
            } else {
                cout << "\n10:15 - same figure, walking fast, away from "
                     << "the house. Forty-five missing minutes.\n";
                pinned2 = true;
            }
        } else {
            if (pinned3) {
                cout << "\nThat pin is already on the board.\n";
            } else {
                cout << "\n11:30 - 'the answer is in the register'. "
                     << "Then 11:55. Then nothing.\n";
                pinned3 = true;
            }
        }
    }
    waitForContinue();
}

// ============================= LOOP 7 =============================

void StoryManager::loop7MorningIntro(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "DAY 7 - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nThe register vanished from the shelf. " << player.getName() << " knows paper does not "
         << "walk. People move paper.\n";
}

void StoryManager::loop7MissingPages(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "RECORDS OFFICE - " << timeLoop.getTimeString() << "\n";
    printDivider();

    cout << "\nBehind a cabinet you find pages someone burned - "
         << "incomplete copies.\n";
    cout << "One page survived. The altered entry. The original ink "
         << "underneath the forgery.\n";

    if (player.getNotebook().addEvidence(Evidence(
            "ALTERED_RECORD_COPY",
            "Surviving copy of the altered record",
            "A surviving page shows the falsified entry with the original "
            "ink still visible underneath. The records were deliberately "
            "altered.",
            "Evidence"))) {
        cout << "\n[Clue discovered: ALTERED_RECORD_COPY]\n";
    }
    cout << "\nFraud, proven. The name behind it - still a shadow.\n";
    waitForContinue();
}

// ============================= LOOP 8 =============================

void StoryManager::loop8MorningIntro(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "DAY 8 - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nRao is ready to listen. " << player.getName() << " must make him ready to act.\n";
}

void StoryManager::loop8RecordRequest(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "POLICE STATION - " << timeLoop.getTimeString() << "\n";
    printDivider();

    cout << "\nYou file an official request for the transfer records.\n";
    cout << "The clerk cannot hide a file the police have logged.\n";

    if (player.getNotebook().addEvidence(Evidence(
            "OFFICIAL_RECORD_REQUEST",
            "Official police request for the transfer records",
            "Inspector Rao logged an official request for the property "
            "transfer records - they are now under police protection.",
            "Lead"))) {
        cout << "\n[Clue noted: OFFICIAL_RECORD_REQUEST]\n";
    }
}

// ============================= LOOP 9 =============================

void StoryManager::loop9MorningIntro(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "DAY 9 - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nThe numbers connect. The story stops matching. "
         << "Today, " << player.getName() << " breaks the story.\n";
}

// ============================= LOOP 10 =============================

void StoryManager::loop10MorningIntro(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "DAY 10 - " << timeLoop.getTimeString() << "\n";
    printDivider();

    cout << "\n" << player.getName() << " has lived this day ten times. Tonight the ending is yours "
         << "to write.\n";
    cout << "Harshit will die at midnight - unless the day finally "
         << "moves forward.\n";

    cout << "\n1. Review what you know.\n";
    cout << "2. Go to Harshit.\n";
    cout << "3. Go to Inspector Rao.\n";
    int choice = askChoice("\nEnter choice: ", 1, 3);

    if (choice == 1) {
        cout << "\nYou open the notebook. Every page cost you a night.\n";
    } else if (choice == 2) {
        cout << "\nHarshit is alive. Not for long, unless you act.\n";
    } else {
        cout << "\nRao will listen today. He has heard enough rumours.\n";
    }
}

void StoryManager::loop10CaseBoard(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "FINAL EVIDENCE BOARD - " << timeLoop.getTimeString() << "\n";
    printDivider();

    cout << "\nWhat the notebook holds:\n\n";
    if (player.getNotebook().hasEvidence("LAND_RECORDS_LEAD"))
        cout << "  [x] The altered property records.\n";
    else
        cout << "  [ ] The altered property records.\n";
    if (player.getNotebook().hasEvidence("PHONE_MESSAGE"))
        cout << "  [x] Harshit's warning about the register.\n";
    else
        cout << "  [ ] Harshit's warning about the register.\n";
    if (player.getNotebook().hasEvidence("RECORD_DISCREPANCY") ||
        player.getNotebook().hasEvidence("ALTERED_RECORD_COPY"))
        cout << "  [x] Proof the records were falsified.\n";
    else
        cout << "  [ ] Proof the records were falsified.\n";
    if (player.getNotebook().hasEvidence("AARAV_VISIT_ADMISSION"))
        cout << "  [x] Aarav at Harshit's house that night.\n";
    else
        cout << "  [ ] Aarav at Harshit's house that night.\n";
    if (player.getNotebook().hasEvidence("TRANSFER_REFERENCE_LINK") ||
        player.getNotebook().hasEvidence("AARAV_FRAUD_ADMISSION"))
        cout << "  [x] The transfer link.\n";
    else
        cout << "  [ ] The transfer link.\n";

    waitForContinue();
}

void StoryManager::loop10HarshitTruth(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "HARSHIT'S HOUSE - " << timeLoop.getTimeString() << "\n";
    printDivider();

    cout << "\nHarshit: \"You've lived this day before. I can tell.\"\n";
    cout << player.getName() << ": \"Then listen. Tonight, trust "
         << "only Rao.\"\n";

    cout << "\n1. Tell him everything.\n";
    cout << "2. Tell him only what he must do.\n";
    int choice = askChoice("\nEnter choice: ", 1, 2);

    if (choice == 1) {
        cout << "\nHe believes you. He shouldn't. He does.\n";
    } else {
        cout << "\n\"Stay where Rao puts you. Don't open the door "
             << "to anyone else.\"\n";
        cout << "Harshit nods slowly.\n";
    }
    waitForContinue();
}

void StoryManager::loop10Plan(Player& player, TimeLoop& timeLoop,
                              bool& speakAarav, bool& protectHarshit,
                              bool& secureRecords, string& accusedSuspect) {
    printDivider();
    cout << "POLICE STATION - " << timeLoop.getTimeString() << "\n";
    printDivider();

    cout << "\nInspector Rao: \"Give me the case in one minute.\"\n";
    cout << player.getName() << ": \"Property fraud. A witness placing "
         << "Aarav at the house. A transfer link. And a murder tonight "
         << "that hasn't happened yet.\"\n";
    cout << "Rao does not understand the time loop. He understands "
         << "the risk.\n";

    bool namedAnyone = false;
    while (true) {
        cout << "\n1. Ask Rao to bring in Aarav for questioning.\n";
        cout << "2. Ask Rao to protect Harshit tonight.\n";
        cout << "3. Ask Rao to secure the property records.\n";
        cout << "4. State who you believe is responsible.\n";
        cout << "5. Done planning.\n";

        int choice = askChoice("\nEnter choice: ", 1, 5);

        if (choice == 5) {
            cout << "\nOBJECTIVES FOR TONIGHT\n";
            cout << "  [" << (protectHarshit ? "x" : " ")
                 << "] Harshit is not alone at his house.\n";
            cout << "  [" << (speakAarav ? "x" : " ")
                 << "] Aarav is formally questioned.\n";
            cout << "  [" << (secureRecords ? "x" : " ")
                 << "] The property documents are preserved.\n";
            break;
        }

        if (choice == 1) {
            if (speakAarav) {
                cout << "\nRao: \"That's already arranged.\"\n";
            } else {
                speakAarav = true;
                cout << "\nRao: \"He'll be at the station by afternoon.\"\n";
            }
        } else if (choice == 2) {
            if (protectHarshit) {
                cout << "\nRao: \"That's already arranged.\"\n";
            } else {
                protectHarshit = true;
                cout << "\nRao: \"Harshit stays at the safehouse. "
                     << "My people, not his neighbours.\"\n";
            }
        } else if (choice == 3) {
            if (secureRecords) {
                cout << "\nRao: \"That's already arranged.\"\n";
            } else {
                secureRecords = true;
                cout << "\nRao: \"Everything in that archive gets logged "
                     << "and locked tonight.\"\n";
            }
        } else {
            if (namedAnyone) {
                if (accusedSuspect == "") {
                    cout << "\n(You told Rao you are naming no one yet.)\n";
                } else {
                    cout << "\n(You already named " << accusedSuspect
                         << " to Rao.)\n";
                }
                cout << "You can change your answer.\n";
            }
            namedAnyone = true;
            cout << "\nWho do you believe is responsible?\n";
            cout << "  1. Aarav\n";
            cout << "  2. Ramesh\n";
            cout << "  3. The records employee\n";
            cout << "  4. Name no one yet\n";

            int suspect = askChoice("\nEnter choice: ", 1, 4);

            if (suspect == 1) {
                accusedSuspect = "Aarav";
                cout << "\nRao: \"Then let the evidence speak. "
                     << "An accusation must be proven.\"\n";
            } else if (suspect == 2) {
                accusedSuspect = "Ramesh";
                cout << "\nRao: \"Ramesh? I need far more than an "
                     << "uncertain sighting before I act on that.\"\n";
            } else if (suspect == 3) {
                accusedSuspect = "Records employee";
                cout << "\nRao: \"That is a serious claim. "
                     << "I hope you can prove it.\"\n";
            } else {
                accusedSuspect = "";
                cout << "\nRao: \"Then we act on evidence, not names.\"\n";
            }
        }
    }

    waitForContinue();
}

void StoryManager::loop10Questioning(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "POLICE STATION - " << timeLoop.getTimeString() << "\n";
    printDivider();

    cout << "\nAarav sits across the table. He smiles. The smile "
         << "does not reach.\n";
    cout << "Aarav: \"You built a whole case out of a shopkeeper's "
         << "bad eyesight.\"\n";
    cout << player.getName() << ": \"Out of your own two versions "
         << "of one night.\"\n";
    cout << "The smile stops.\n";
    waitForContinue();
}

void StoryManager::loop10MissingPiece(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "POLICE STATION - " << timeLoop.getTimeString() << "\n";
    printDivider();

    cout << "\nThe transfer numbers are on the table between them.\n";
    cout << "Rao: \"The reference matches the forged entry. "
         << "Explain the fraud, Aarav.\"\n";
    cout << "Aarav: \"...The transfer was my idea. The records clerk "
         << "did the rest. Harshit was never supposed to be part "
         << "of it.\"\n";

    if (player.getNotebook().addEvidence(Evidence(
            "AARAV_FRAUD_ADMISSION",
            "Aarav admits the property fraud (verified by Rao)",
            "In front of Inspector Rao, Aarav admitted the falsified "
            "transfer was his idea. Verified confession of fraud - "
            "still not, by itself, proof of murder.",
            "Verified"))) {
        cout << "\n[Verified evidence: AARAV_FRAUD_ADMISSION]\n";
    }
    waitForContinue();
}

void StoryManager::loop10SafeNight(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "EVENING - " << timeLoop.getTimeString() << "\n";
    printDivider();

    cout << "\nThe safehouse is quiet. Too quiet is better than "
         << "yesterday's silence.\n";

    cout << "\n1. Stay with Harshit.\n";
    cout << "2. Check the street outside.\n";
    cout << "3. Sit by the phone and wait.\n";
    int choice = askChoice("\nEnter choice: ", 1, 3);

    if (choice == 1) {
        cout << "\nHarshit: \"Ten nights. You never gave up.\"\n";
        cout << player.getName() << ": \"Someone had to remember.\"\n";
    } else if (choice == 2) {
        cout << "\nA car with no lights idles at the corner, "
             << "then leaves.\n";
    } else {
        cout << "\nThe phone does not ring. That is new.\n";
    }
    waitForContinue();
}

void StoryManager::loop10Message(Player& player, TimeLoop& timeLoop,
                                 bool& rescueWithoutSupport) {
    printDivider();
    cout << "11:30 PM - " << timeLoop.getTimeString() << "\n";
    printDivider();

    cout << "\nYour phone vibrates. Harshit's name.\n\n";
    cout << "HARSHIT: \"" << player.getName() << ", someone's outside the safehouse. "
         << "I think he followed me here.\"\n";

    cout << "\n1. Call Inspector Rao. Move together.\n";
    cout << "2. Rush there alone. Now.\n";
    int choice = askChoice("\nEnter choice: ", 1, 2);

    if (choice == 1) {
        cout << "\nRao answers on the first ring. He never does that.\n";
        cout << "Inspector Rao: \"We go together. Stay on the line.\"\n";
    } else {
        rescueWithoutSupport = true;
        cout << "\nYou run. The streets are empty. "
             << "Nobody knows where you went.\n";
    }
    waitForContinue();
}

// Only reached in the True Detective path.
void StoryManager::loop10Confrontation(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "11:55 PM - HARSHIT'S HOUSE\n";
    printDivider();

    cout << "\nAarav arrives at Harshit's house, expecting to find "
         << "him alone.\n";
    cout << "Rao and Mitul are already inside. Harshit is safe.\n\n";
    cout << "Aarav: \"Where is Harshit?\"\n";
    cout << player.getName() << ": \"Somewhere you can't reach him "
         << "tonight.\"\n";

    cout << "\nAarav: \"You don't understand what this could do to me.\"\n";
    cout << "Rao steps forward.\n\n";
    cout << "Aarav: \"I killed him.\"\n\n";
    cout << "The difference this time: Harshit is alive when Aarav "
         << "confesses.\n";

    waitForContinue();

    timeLoop.setTime(0, 1);

    printDivider();
    cout << timeLoop.getTimeString() << "\n";
    printDivider();

    cout << "\nThe clock reaches midnight.\n";
    cout << "You brace for the reset.\n\n";
    cout << "Nothing happens.\n";
    cout << "The clock changes to 12:01 AM.\n\n";
    cout << "Harshit is still alive. Rao is still here. "
         << "The notebook stays open - but the day does not restart.\n\n";
    cout << player.getName() << ": \"Twelve-oh-one...\"\n";
    cout << "It's over. The day finally moved forward.\n";
    cout << "Why the loop began remains a small mystery.\n";

    waitForContinue();
}
