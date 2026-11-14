// NPC.cpp - conversations for Harshit, Aarav, Ramesh, Rao and the clerk.

#include "Declarations.cpp"

NPC::NPC(const string& name, const string& role, const string& greeting)
    : Character(name, role) {
    this->greeting = greeting;
}

// Short repeat talk when revisiting a character the same day.
void NPC::interact(Player& player) {
    cout << "\n";
    if (name == "Harshit Mehra") {
        cout << "Harshit: \"" << player.getName()
             << ", later. I need to check something first.\"\n";
    } else if (name == "Aarav") {
        cout << "Aarav: \"Still asking questions? Be careful who you trust.\"\n";
    } else if (name == "Ramesh") {
        cout << "Ramesh: \"Quiet day. Come back if you think of another question.\"\n";
    } else if (name == "Inspector Rao") {
        cout << "Inspector Rao: \"" << player.getName()
             << ", bring me evidence, not rumours.\"\n";
    } else {
        cout << name << ": \"If you find real evidence, bring it to the station.\"\n";
    }
}

// ============================= LOOP 1 =============================

void NPC::harshitLoop1Morning(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "HARSHIT'S HOUSE - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nHarshit looks over his shoulder before letting you in.\n";
    cout << "Harshit: \"Someone altered the old property records. "
         << "The original register proves it.\"\n";

    bool askedWho = false;
    bool askedWhere = false;
    bool askedAccess = false;
    while (true) {
        // The menu shows only questions that are still unanswered.
        int next = 1;
        int optWho = 0;
        int optWhere = 0;
        int optAccess = 0;
        if (!askedWho) {
            optWho = next++;
        }
        if (!askedWhere) {
            optWhere = next++;
        }
        if (askedWhere && !askedAccess) {
            optAccess = next++;
        }
        int optLeave = next++;

        cout << "\n";
        if (optWho)    cout << optWho << ". Who benefits from the change?\n";
        if (optWhere)  cout << optWhere << ". Where is the original register?\n";
        if (optAccess) cout << optAccess << ". Ask who can reach the archive.\n";
        cout << optLeave << ". Leave.\n";

        int choice = askChoice("\nEnter choice: ", 1, optLeave);
        if (choice == optLeave) {
            break;
        }
        if (choice == optWho) {
            askedWho = true;
            cout << "\nHarshit: \"I don't know yet. That's what scares me.\"\n";
        } else if (choice == optWhere) {
            askedWhere = true;
            cout << "\nHarshit: \"The records office archive. "
                 << "But someone has been watching it.\"\n";
            if (player.getNotebook().addEvidence(Evidence(
                    "LAND_RECORDS_LEAD",
                    "The original register is in the records office archive",
                    "Harshit says the property records were falsified and the "
                    "original register can prove it. It is kept in the records "
                    "office archive - and someone has been watching it.",
                    "Lead"))) {
                cout << "\n[Clue noted: LAND_RECORDS_LEAD]\n";
            }
        } else {
            askedAccess = true;
            cout << "\nHarshit: \"The clerks. And anyone the clerks "
                 << "are afraid of. That's what worries me.\"\n";
        }
    }

    if (player.getNotebook().hasEvidence("LAND_RECORDS_LEAD")) {
        cout << "\n(You leave. The records office archive is not on today's "
             << "town map - but the lead is in your notebook.)\n";
    } else {
        cout << "\n(You leave Harshit to his window.)\n";
    }
    waitForContinue();
}

void NPC::harshitLoop1Afternoon(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "HARSHIT'S HOUSE - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nHarshit keeps glancing at the window.\n";
    cout << "Harshit: \"" << player.getName() << ", sit down. Please.\"\n";
    cout << "Harshit: \"Aarav asked me to stop looking into the records. "
         << "Twice.\"\n";

    cout << "\n1. Tell him to go to the police.\n";
    cout << "2. Tell him to hide the register.\n";
    cout << "3. Leave.\n";
    int choice = askChoice("\nEnter choice: ", 1, 3);

    if (choice == 1) {
        cout << "\nHarshit: \"With what proof? Rao needs documents, not fear.\"\n";
    } else if (choice == 2) {
        cout << "\nHarshit: \"Maybe tonight. I'll think of somewhere.\"\n";
    }
    waitForContinue();
}

void NPC::rameshLoop1Shop(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "RAMESH'S SHOP - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nRamesh leans over the counter.\n";
    cout << "Ramesh: \"" << player.getName()
         << ", Harshit asked me about old land deals last week. "
         << "That boy looks over his shoulder now.\"\n";

    cout << "\n1. Who else asked about the land?\n";
    cout << "2. Leave.\n";
    int choice = askChoice("\nEnter choice: ", 1, 2);
    if (choice == 1) {
        cout << "\nRamesh: \"Aarav, maybe. Or nobody. "
             << "Talk is cheap here.\"\n";
        cout << "A rumour. Nothing more.\n";
        if (player.getNotebook().addEvidence(Evidence(
                "LAND_INQUIRY_RUMOR",
                "Someone else may have asked about the land",
                "Ramesh heard that Aarav - or maybe nobody - also asked "
                "about the old land deals. Uncertain gossip. NOT proof "
                "of anything.",
                "Uncertain"))) {
            cout << "\n[Clue noted: LAND_INQUIRY_RUMOR - uncertain]\n";
        }
    }
    cout << "\nRamesh turns back to his counter. (Conversation over.)\n";
}

void NPC::aaravLoop1Street(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "TOWN STREET - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nAarav is waiting outside Harshit's house.\n";
    cout << "Aarav: \"Harshit told you about the records?\"\n";
    cout << player.getName() << ": \"Why are you asking?\"\n";
    cout << "Aarav looks away.\n";
    cout << "Aarav: \"Forget I asked.\"\n";

    cout << "\n1. Question him.\n";
    cout << "2. Let him go.\n";
    int choice = askChoice("\nEnter choice: ", 1, 2);

    if (choice == 1) {
        cout << "\nAarav: \"I'm his friend. I just don't want him "
             << "in trouble.\"\n";
        cout << "He leaves before you can answer.\n";
    } else {
        cout << "\nYou let him go. He walks away slowly, "
             << "watching you over his shoulder.\n";
    }
}

void NPC::aaravLoop1Evening(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "TOWN STREET - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nAarav steps out of the shadows near Harshit's house.\n";
    cout << "Aarav: \"Stay out of Harshit's business. "
         << "This doesn't concern you.\"\n";

    cout << "\n1. What are you afraid of?\n";
    cout << "2. Were you at the archive last night?\n";
    cout << "3. Walk away.\n";
    int choice = askChoice("\nEnter choice: ", 1, 3);

    if (choice == 1) {
        cout << "\nAarav: \"Afraid? I'm trying to help.\"\n";
    } else if (choice == 2) {
        cout << "\nAarav freezes for half a second.\n";
        cout << "Aarav: \"You're imagining things.\"\n";
    }

    if (player.getNotebook().addEvidence(Evidence(
            "AARAV_WARNING",
            "Aarav warned Mitul to stop investigating",
            "Aarav told Mitul to stay out of Harshit's business.",
            "Suspicion"))) {
        cout << "\n[Clue noted: AARAV_WARNING]\n";
    }
}

// ============================= LOOP 2 =============================

bool NPC::harshitLoop2Morning(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "HARSHIT'S HOUSE - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nHarshit is alive. Same day. Same fear in his eyes.\n";
    cout << "Harshit: \"" << player.getName()
         << ", you look like you haven't slept.\"\n";

    bool knowsAboutBackupPhone = false;
    bool askedNight = false;
    bool askedPhone = false;
    while (true) {
        int next = 1;
        int optNight = 0;
        int optPhone = 0;
        if (!askedNight) {
            optNight = next++;
        }
        if (!askedPhone) {
            optPhone = next++;
        }
        int optLeave = next++;

        cout << "\n";
        if (optNight) cout << optNight << ". Ask about last night.\n";
        if (optPhone) cout << optPhone << ". Ask about his phone.\n";
        cout << optLeave << ". Leave.\n";

        int choice = askChoice("\nEnter choice: ", 1, optLeave);
        if (choice == optLeave) {
            break;
        }
        if (choice == optNight) {
            askedNight = true;
            cout << "\nHarshit: \"I kept the register hidden. "
                 << "But I left something for you, just in case.\"\n";
        } else {
            askedPhone = true;
            knowsAboutBackupPhone = true;
            cout << "\nHarshit: \"My backup phone. Old papers on my desk. "
                 << "If something happens - read the draft.\"\n";
        }
    }
    return knowsAboutBackupPhone;
}

void NPC::aaravLoop2Street(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "TOWN STREET - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nYou block Aarav's path.\n";

    cout << "\n1. Ask where he was last night.\n";
    cout << "2. Ask about the property records.\n";
    if (player.getNotebook().hasEvidence("PHONE_MESSAGE")) {
        cout << "3. Confront him about Harshit's draft message.\n";
    } else {
        cout << "3. Ask nothing more.\n";
    }

    int choice = askChoice("\nEnter choice: ", 1, 3);

    if (choice == 1) {
        cout << "\nAarav: \"Home. All night.\"\n";
    } else if (choice == 2) {
        cout << "\nAarav: \"What records? I don't know anything "
             << "about any original record.\"\n";
    } else if (player.getNotebook().hasEvidence("PHONE_MESSAGE")) {
        cout << "\nAarav: \"Draft message? Harshit was paranoid. "
             << "Ask him yourself.\"\n";
        cout << "He knows Harshit is dead. He said it too fast.\n";
    }

    if (player.getNotebook().addEvidence(Evidence(
            "AARAV_DENIAL",
            "Aarav denies knowing about the original record",
            "Aarav claims he knows nothing about any original record. "
            "He also claims he was home all night.",
            "Uncertain"))) {
        cout << "\n[Clue noted: AARAV_DENIAL]\n";
    }

    if (player.getNotebook().hasEvidence("PHONE_MESSAGE")) {
        player.increaseSuspicion(1);
    }
}

void NPC::rameshLoop2Shop(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "RAMESH'S SHOP - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nRamesh sweeps the same spot twice. Something is on his mind.\n";
    cout << "Ramesh: \"Last night... I saw someone near Harshit's house. "
         << "I think.\"\n";

    bool askedTime = false;
    bool askedWho = false;
    bool askedCertain = false;
    while (true) {
        int next = 1;
        int optTime = 0;
        int optWho = 0;
        int optCertain = 0;
        if (!askedTime) {
            optTime = next++;
        }
        if (!askedWho) {
            optWho = next++;
        }
        if (!askedCertain) {
            optCertain = next++;
        }
        int optDone = next++;

        cout << "\n";
        if (optTime)    cout << optTime << ". When did you see him?\n";
        if (optWho)     cout << optWho << ". Who did it look like?\n";
        if (optCertain) cout << optCertain << ". Are you certain?\n";
        cout << optDone << ". Done.\n";

        int choice = askChoice("\nEnter choice: ", 1, optDone);
        if (choice == optDone) {
            break;
        }
        if (choice == optTime) {
            askedTime = true;
            cout << "\nRamesh: \"Around 9:30 in the evening. "
                 << "Closing up the shop.\"\n";
        } else if (choice == optWho) {
            askedWho = true;
            cout << "\nRamesh: \"Built like Aarav. The walk, maybe. "
                 << "I didn't see the face.\"\n";
        } else {
            askedCertain = true;
            cout << "\nRamesh: \"That's the problem. I am not certain.\"\n";
        }

        // The sighting is recorded the moment the player hears it.
        if (askedTime || askedWho) {
            if (player.getNotebook().addEvidence(Evidence(
                    "RAMESH_SIGHTING",
                    "Ramesh may have seen someone near Harshit's house",
                    "Around 9:30 PM Ramesh saw a figure resembling Aarav "
                    "near Harshit's house - but he did not see the face "
                    "and is unsure.",
                    "Uncertain"))) {
                cout << "\n[Clue noted: RAMESH_SIGHTING - uncertain]\n";
            }
        }
    }
    cout << "\nRamesh goes back to sweeping. (Conversation over.)\n";
}

void NPC::harshitLoop2Evening(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "HARSHIT'S HOUSE - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nHarshit bars the door with a chair.\n";
    cout << "Harshit: \"" << player.getName() << ", listen to me carefully.\"\n";
    cout << "Harshit: \"Whatever you find - don't trust Aarav with it.\"\n";

    cout << "\n1. Ask why he says that.\n";
    cout << "2. Promise to return before midnight.\n";
    int choice = askChoice("\nEnter choice: ", 1, 2);

    if (choice == 1) {
        cout << "\nHarshit: \"He asked me to stop. And he never asks twice. "
             << "Unless it matters.\"\n";
    } else {
        cout << "\nHarshit nods. He does not look convinced.\n";
    }
}

// ============================= LOOP 3 =============================

void NPC::harshitLoop3Morning(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "HARSHIT'S HOUSE - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nHarshit: \"" << player.getName() << ", you keep looking at me like you've seen this before.\"\n";

    cout << "\n1. Ask about the night again.\n";
    cout << "2. Ask about Aarav's visits.\n";
    cout << "3. Leave.\n";
    int choice = askChoice("\nEnter choice: ", 1, 3);

    if (choice == 1) {
        cout << "\nHarshit: \"Same as yesterday. The register is hidden. "
             << "I'll show nobody.\"\n";
    } else if (choice == 2) {
        cout << "\nHarshit: \"He came by in the evening. Asked me to stop. "
             << "Then left angry.\"\n";
    }
}

void NPC::rameshLoop3Shop(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "RAMESH'S SHOP - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nRamesh agrees to tell you everything. Slowly.\n";

    bool askedTime = false;
    bool askedPlace = false;
    bool askedFace = false;
    while (true) {
        int next = 1;
        int optTime = 0;
        int optPlace = 0;
        int optFace = 0;
        if (!askedTime) {
            optTime = next++;
        }
        if (!askedPlace) {
            optPlace = next++;
        }
        if (!askedFace) {
            optFace = next++;
        }
        int optDone = next++;

        cout << "\n";
        if (optTime)  cout << optTime << ". What time exactly?\n";
        if (optPlace) cout << optPlace << ". Where exactly was he standing?\n";
        if (optFace)  cout << optFace << ". Did you see his face?\n";
        cout << optDone << ". Done.\n";

        int choice = askChoice("\nEnter choice: ", 1, optDone);
        if (choice == optDone) {
            break;
        }
        if (choice == optTime) {
            askedTime = true;
            cout << "\nRamesh: \"9:30. The clock in the shop had just "
                 << "chimed.\"\n";
        } else if (choice == optPlace) {
            askedPlace = true;
            cout << "\nRamesh: \"Between my shop and Harshit's gate. "
                 << "In the dark.\"\n";
        } else {
            askedFace = true;
            cout << "\nRamesh: \"No. Only the walk. I THINK it looked "
                 << "like Aarav. Think.\"\n";
        }

        if (askedTime && askedPlace && askedFace) {
            if (player.getNotebook().addEvidence(Evidence(
                    "WITNESS_STATEMENT",
                    "Ramesh's complete statement",
                    "At 9:30 PM a figure stood between the shop and "
                    "Harshit's gate. Ramesh recognised only the walk - he "
                    "cannot confirm the face.",
                    "Uncertain"))) {
                cout << "\n[Clue noted: WITNESS_STATEMENT - uncertain]\n";
            }
        }
    }

    if (player.getNotebook().hasEvidence("RAMESH_SIGHTING")) {
        player.increaseSuspicion(1);
    }
    cout << "\nRamesh says no more. (Conversation over.)\n";
}

void NPC::aaravLoop3Street(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "TOWN STREET - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nAarav: \"I already told you. I was home all night.\"\n";

    cout << "\n1. Ramesh saw someone at 9:30 near the house.\n";
    cout << "2. Ask about the records again.\n";
    cout << "3. Walk away.\n";
    int choice = askChoice("\nEnter choice: ", 1, 3);

    if (choice == 1) {
        cout << "\nAarav: \"Ramesh needs glasses. Ask him how sure he was.\"\n";
    } else if (choice == 2) {
        cout << "\nAarav: \"Records, records. You sound like Harshit.\"\n";
    }

    if (player.getNotebook().addEvidence(Evidence(
            "AARAV_DENIAL",
            "Aarav denies knowing about the original record",
            "Aarav claims he knows nothing about any original record. "
            "He also claims he was home all night.",
            "Uncertain"))) {
        cout << "\n[Clue noted: AARAV_DENIAL]\n";
    }
    if (player.getNotebook().hasEvidence("WITNESS_STATEMENT")) {
        player.increaseSuspicion(1);
    }
}

void NPC::harshitLoop3Evening(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "HARSHIT'S HOUSE - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nHarshit: \"" << player.getName() << ", one day I'll tell you the whole story. "
         << "If we get a quiet night.\"\n";
    cout << "The house creaks. Neither of you laughs.\n";
}

// ============================= LOOP 4 =============================

void NPC::harshitLoop4Morning(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "HARSHIT'S HOUSE - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nHarshit: \"" << player.getName() << ", you look tired. Bad dreams?\"\n";
    cout << player.getName() << ": \"You have no idea.\"\n";
}

void NPC::aaravLoop4Confront(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "TOWN STREET - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nYou confront Aarav with what you know.\n";

    bool askedAlibi = false;
    bool askedWhy = false;
    while (true) {
        int next = 1;
        int optAlibi = 0;
        int optWhy = 0;
        if (!askedAlibi) {
            optAlibi = next++;
        }
        if (!askedWhy) {
            optWhy = next++;
        }
        int optDone = next++;

        cout << "\n";
        if (optAlibi) cout << optAlibi << ". Where were you at 9:30 that night?\n";
        if (optWhy)   cout << optWhy << ". Why did you tell Harshit to stop?\n";
        cout << optDone << ". Done.\n";

        int choice = askChoice("\nEnter choice: ", 1, optDone);
        if (choice == optDone) {
            break;
        }
        if (choice == optAlibi) {
            askedAlibi = true;
            cout << "\nAarav: \"Home. I was reading. "
                 << "I think I slept early.\"\n";
            cout << "\"I think\" is not an alibi.\n";
            if (player.getNotebook().addEvidence(Evidence(
                    "AARAV_ALIBI_DETAILS",
                    "Aarav's alibi is vague",
                    "Aarav claims he was home reading and 'thinks' he slept "
                    "early. He cannot confirm where he was at 9:30 PM.",
                    "Uncertain"))) {
                cout << "\n[Clue noted: AARAV_ALIBI_DETAILS]\n";
            }
        } else {
            askedWhy = true;
            cout << "\nAarav: \"For his own good. That land dispute "
                 << "has gone on for years.\"\n";
        }
    }
    cout << "\nAarav walks away. (Conversation over.)\n";
}

void NPC::rameshLoop4Shop(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "RAMESH'S SHOP - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nYou push Ramesh on the details he avoided.\n";

    bool askedSomeone = false;
    bool askedRao = false;
    while (true) {
        int next = 1;
        int optSomeone = 0;
        int optRao = 0;
        if (!askedSomeone) {
            optSomeone = next++;
        }
        if (!askedRao) {
            optRao = next++;
        }
        int optDone = next++;

        cout << "\n";
        if (optSomeone) cout << optSomeone << ". Could it have been someone else?\n";
        if (optRao)     cout << optRao << ". Would you say this in front of Inspector Rao?\n";
        cout << optDone << ". Done.\n";

        int choice = askChoice("\nEnter choice: ", 1, optDone);
        if (choice == optDone) {
            break;
        }
        if (choice == optSomeone) {
            askedSomeone = true;
            cout << "\nRamesh: \"Of course it could. It was dark. "
                 << "I sell sugar and tea - I am not a detective.\"\n";
        } else {
            askedRao = true;
            cout << "\nRamesh: \"I would say what I saw. But I would "
                 << "also say I am not sure. Both are true.\"\n";
        }

        if (player.getNotebook().addEvidence(Evidence(
                "WITNESS_LIMITATIONS",
                "Ramesh cannot confirm the identity",
                "Ramesh admits it was dark, it could have been anyone, and "
                "he would testify only that he is unsure.",
                "Uncertain"))) {
            cout << "\n[Clue noted: WITNESS_LIMITATIONS]\n";
        }
    }
    cout << "\nRamesh says no more. (Conversation over.)\n";
}

void NPC::raoLoop4Visit(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "HARSHIT'S HOUSE - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nInspector Rao has come to take a statement.\n";
    cout << "Inspector Rao: \"A witness who is unsure is not a witness. "
         << "It is a rumour with a mouth.\"\n";

    cout << "\n1. Show him what you have.\n";
    cout << "2. Ask what would be enough.\n";
    int choice = askChoice("\nEnter choice: ", 1, 2);

    if (choice == 1) {
        cout << "\nRao flips through your notes slowly.\n";
        cout << "Inspector Rao: \"Useful. Not enough. Keep going.\"\n";
    } else {
        cout << "\nInspector Rao: \"Documents. Place. Motive linked to "
             << "action. Connect those three - then we talk.\"\n";
    }

    if (player.getNotebook().addEvidence(Evidence(
            "RAO_REPORT",
            "Inspector Rao's standard: documents, place, motive",
            "Rao will act on documents that place a suspect at the scene "
            "and connect them to the property transfer - not on rumours.",
            "Lead"))) {
        cout << "\n[Clue noted: RAO_REPORT]\n";
    }
}

void NPC::harshitLoop4Evening(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "HARSHIT'S HOUSE - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nHarshit: \"" << player.getName() << ", if Ramesh is right, Aarav was watching my house. "
         << "Why?\"\n";
    cout << "He answers his own question by looking at the locked drawer.\n";
}

// ============================= LOOP 5 =============================

void NPC::harshitLoop5Morning(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "HARSHIT'S HOUSE - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nHarshit slides an old key across the table.\n";
    cout << "Harshit: \"" << player.getName() << ", take this.\"\n";
    cout << "Harshit: \"The archive room. Ask for the transfer files. "
         << "Don't say I sent you.\"\n";
}

void NPC::clerkLoop5Morning(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "RECORDS OFFICE - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nThe clerk keeps one hand on the register shelf.\n";
    if (player.getNotebook().hasEvidence("LAND_RECORDS_LEAD")) {
        cout << "You know exactly why you are here: the original register.\n";
    }
    cout << "Clerk: \"Transfer files? Those are old. Why do you ask?\"\n";

    cout << "\n1. \"Research for a friend.\"\n";
    cout << "2. \"Someone falsified property records.\"\n";
    cout << "3. Leave.\n";
    int choice = askChoice("\nEnter choice: ", 1, 3);

    if (choice == 1) {
        cout << "\nClerk: \"Then read them here. Nothing leaves this room.\"\n";
    } else if (choice == 2) {
        cout << "\nThe clerk goes pale.\n";
        cout << "Clerk: \"Say that quietly. And say it to the inspector.\"\n";
    }

    if (choice != 3) {
        if (player.getNotebook().addEvidence(Evidence(
                "ARCHIVE_REFERENCE",
                "The archive holds the old transfer files",
                "The old property transfer files are kept in the records "
                "office archive. The clerk is nervous about them.",
                "Lead"))) {
            cout << "\n[Clue noted: ARCHIVE_REFERENCE]\n";
        }
    }
}

void NPC::rameshLoop5Shop(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "RAMESH'S SHOP - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nRamesh: \"" << player.getName() << ", that land - it changed hands on paper. "
         << "The old family never sold it. Not really.\"\n";
    cout << "Ramesh: \"Ask who signed. That's the part nobody mentions.\"\n";
}

void NPC::clerkLoop5Afternoon(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "RECORDS OFFICE - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nYou find the transfer file. Two columns do not match.\n";

    cout << "\n1. Compare the dates.\n";
    cout << "2. Compare the signatures.\n";
    cout << "3. Leave.\n";
    int choice = askChoice("\nEnter choice: ", 1, 3);

    if (choice == 1) {
        cout << "\nThe approval date is AFTER the transfer date. "
             << "Impossible. That is the discrepancy.\n";
    } else if (choice == 2) {
        cout << "\nOne signature was traced. Slowly. Sloppily.\n";
    }

    if (choice != 3) {
        if (player.getNotebook().addEvidence(Evidence(
                "RECORD_DISCREPANCY",
                "The property transfer file is falsified",
                "In the transfer file the approval date falls after the "
                "transfer date, and one signature appears traced. The "
                "records were altered.",
                "Evidence"))) {
            cout << "\n[Clue noted: RECORD_DISCREPANCY]\n";
        }
        cout << "\nBut who signed? A falsified record proves fraud - "
             << "not murder.\n";
    }
}

void NPC::aaravLoop5Street(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "TOWN STREET - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nAarav falls into step beside you. Too casually.\n";
    cout << "Aarav: \"The clerk talks too much. Whatever he showed you - "
         << "it isn't what you think.\"\n";

    cout << "\n1. How do you know what he showed me?\n";
    cout << "2. Walk away.\n";
    int choice = askChoice("\nEnter choice: ", 1, 2);

    if (choice == 1) {
        cout << "\nAarav: \"Small town. Small windows.\"\n";
        cout << "He was watching the records office.\n";
    }

    if (player.getNotebook().addEvidence(Evidence(
            "AARAV_KNOWS_INVESTIGATION",
            "Aarav knows about Mitul's investigation",
            "Aarav knew Mitul was at the records office. He has been "
            "watching the investigation.",
            "Lead"))) {
        cout << "\n[Clue noted: AARAV_KNOWS_INVESTIGATION]\n";
    }
}

void NPC::harshitLoop5Evening(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "HARSHIT'S HOUSE - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nHarshit: \"" << player.getName() << ", if the file is forged, the land is worth killing "
         << "for.\"\n";
    cout << "Harshit: \"Find the signature. Then find who gains.\"\n";
}

// ============================= LOOP 6 =============================

void NPC::harshitLoop6Morning(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "HARSHIT'S HOUSE - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nHarshit pins paper scraps to the wall. Times. Names.\n";
    cout << "Harshit: \"" << player.getName() << ", help me build the night.\"\n";
    cout << "Harshit: \"Build the night. Hour by hour. "
         << "Someone's story won't survive it.\"\n";
}

void NPC::rameshLoop6Shop(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "RAMESH'S SHOP - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nRamesh: \"One thing I never told anyone.\"\n";
    cout << "Ramesh: \"The figure came BACK at 10:15. Walking fast. "
         << "Away from the house.\"\n";

    if (player.getNotebook().addEvidence(Evidence(
            "TIMELINE_GAP",
            "The figure returned at 10:15 PM",
            "Ramesh saw the same figure leave the direction of Harshit's "
            "house at 10:15 PM - there is a gap between 9:30 and 10:15.",
            "Lead"))) {
        cout << "\n[Clue noted: TIMELINE_GAP]\n";
    }
}

void NPC::aaravLoop6Alibi(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "TOWN STREET - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nAarav: \"I told you. Home all night. In bed by ten.\"\n";

    cout << "\n1. Ramesh saw the figure at 10:15.\n";
    cout << "2. Let it go for now.\n";
    int choice = askChoice("\nEnter choice: ", 1, 2);

    if (choice == 1) {
        cout << "\nAarav: \"Then Ramesh saw a ghost. "
             << "I was in bed. Ask anyone.\"\n";
        cout << "\"Anyone\" is nobody.\n";
    }

    if (player.getNotebook().addEvidence(Evidence(
            "ALIBI_CONFLICT",
            "Aarav's alibi conflicts with the timeline",
            "Aarav claims he was in bed before 10:00 PM, but a figure "
            "matching his build moved near the house at 10:15 PM.",
            "Suspicion"))) {
        cout << "\n[Clue noted: ALIBI_CONFLICT]\n";
    }
    player.increaseSuspicion(1);
}

void NPC::raoLoop6Visit(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "POLICE STATION - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nInspector Rao studies your timeline.\n";
    cout << "Inspector Rao: \"" << player.getName() << ", gaps are not accusations. "
         << "Fill the 9:30 to 10:15 window. Then we talk again.\"\n";
}

void NPC::harshitLoop6Evening(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "HARSHIT'S HOUSE - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nHarshit: \"" << player.getName() << ", tonight I stay awake. Whatever happens, "
         << "at midnight - write down what you saw.\"\n";
    cout << "You already do.\n";
}

// ============================= LOOP 7 =============================

void NPC::harshitLoop7Morning(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "HARSHIT'S HOUSE - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nHarshit: \"The register was moved. The log will say when "
         << "and by whom.\"\n";

    if (player.getNotebook().addEvidence(Evidence(
            "ARCHIVE_REFERENCE",
            "The archive holds the old transfer files",
            "The old property transfer files are kept in the records "
            "office archive. The clerk is nervous about them.",
            "Lead"))) {
        cout << "\n[Clue noted: ARCHIVE_REFERENCE]\n";
    }
}

void NPC::clerkLoop7Archive(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "RECORDS OFFICE ARCHIVE - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nDust. Shelves. One gap where a register should be.\n";
    cout << "Clerk: \"" << player.getName() << ", mind the dust.\"\n";

    cout << "\n1. Search the shelf.\n";
    cout << "2. Check the index card for that shelf.\n";
    cout << "3. Leave.\n";
    int choice = askChoice("\nEnter choice: ", 1, 3);

    if (choice == 1) {
        cout << "\nNothing. Someone cleaned this shelf recently. "
             << "The dust ends in a clean rectangle.\n";
    } else if (choice == 2) {
        cout << "\n\"Register B-7 - see movement log.\" "
             << "Someone signed it out.\n";
    }
}

void NPC::clerkLoop7Movement(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "RECORDS OFFICE - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nThe clerk produces the movement log reluctantly.\n";
    cout << "One line is signed out and never signed back in.\n";

    cout << "\n1. Who signed it out?\n";
    cout << "2. When?\n";
    cout << "3. Leave.\n";
    int choice = askChoice("\nEnter choice: ", 1, 3);

    if (choice == 1) {
        cout << "\nClerk: \"The signature is a smudge. "
             << "I told Rao the same thing.\"\n";
    } else if (choice == 2) {
        cout << "\nThree days before the murder. "
             << "Someone planned ahead.\n";
    }

    if (player.getNotebook().addEvidence(Evidence(
            "REGISTER_MOVEMENT_LOG",
            "The original register was signed out and never returned",
            "Register B-7 was signed out three days before the murder "
            "under a smudged signature and never returned.",
            "Lead"))) {
        cout << "\n[Clue noted: REGISTER_MOVEMENT_LOG]\n";
    }
}

void NPC::harshitLoop7Beneficiary(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "HARSHIT'S HOUSE - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nHarshit: \"" << player.getName() << ", I found the beneficiary name on the transfer. "
         << "I won't say it out loud.\"\n";
    cout << "He writes it on a scrap, shows it, and burns it.\n";
    cout << "You already know the letters. You wish you didn't.\n";
}

void NPC::aaravLoop7Street(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "TOWN STREET - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nAarav steps too close.\n";
    cout << "Aarav: \"" << player.getName() << ", you've been at the records office again. "
         << "Stop this. For everyone's sake.\"\n";

    cout << "\n1. Is that a threat?\n";
    cout << "2. Say nothing.\n";
    int choice = askChoice("\nEnter choice: ", 1, 2);

    if (choice == 1) {
        cout << "\nAarav: \"It's advice. Threats are for people "
             << "with something to hide.\"\n";
        cout << "He walks away first.\n";
    } else {
        cout << "\nYou say nothing. After a long moment, "
             << "he walks away first.\n";
    }
}

void NPC::harshitLoop7Evening(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "HARSHIT'S HOUSE - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nHarshit: \"" << player.getName() << ", one more night. Tomorrow I hand everything "
         << "to Rao.\"\n";
    cout << "You have heard tomorrow before.\n";
}

// ============================= LOOP 8 =============================

void NPC::raoLoop8Review(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "POLICE STATION - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nInspector Rao spreads your notebook across his desk.\n";
    cout << "Inspector Rao: \"" << player.getName() << ", sort it. What is proven? What is guesswork?\"\n";

    cout << "\n1. Review the physical evidence.\n";
    cout << "2. Review the witness statements.\n";
    cout << "3. What is still missing?\n";
    cout << "4. Done.\n";

    bool reviewedEvidence = false;
    bool reviewedWitnesses = false;
    bool reviewedMissing = false;
    while (true) {
        int choice = askChoice("\nEnter choice: ", 1, 4);
        if (choice == 4) {
            break;
        }
        bool repeat = (choice == 1 && reviewedEvidence) ||
                      (choice == 2 && reviewedWitnesses) ||
                      (choice == 3 && reviewedMissing);
        if (repeat) {
            cout << "\nRao: \"We already covered that. Something else?\"\n";
            continue;
        }
        if (choice == 1) {
            reviewedEvidence = true;
            cout << "\nRao points at your notes.\n";
            cout << "Inspector Rao: \"Fraud documents. Fine. "
                 << "That proves a crime - not THE crime.\"\n";
        } else if (choice == 2) {
            reviewedWitnesses = true;
            cout << "\nInspector Rao: \"One shopkeeper who didn't see "
                 << "a face. Two versions from one suspect. Guesswork.\"\n";
        } else {
            reviewedMissing = true;
            cout << "\nInspector Rao: \"Place and link. Put the man at "
                 << "the house AND at the transfer. Then we move.\"\n";
        }
    }
}

void NPC::raoLoop8Priority(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "POLICE STATION - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nInspector Rao: \"We act tonight. One priority. You choose.\"\n";

    cout << "\n1. Watch the archive - catch whoever comes for the register.\n";
    cout << "2. Watch Harshit's house.\n";
    cout << "3. Bring in the suspect for questioning.\n";
    int choice = askChoice("\nEnter choice: ", 1, 3);

    if (choice == 1) {
        cout << "\nInspector Rao: \"The patient option. I like it.\"\n";
    } else if (choice == 2) {
        cout << "\nInspector Rao: \"Protection first. Good.\"\n";
    } else {
        cout << "\nInspector Rao: \"Bold. If he lawyers up, we get one "
             << "shot. Make it count.\"\n";
    }

    if (player.getNotebook().addEvidence(Evidence(
            "INVESTIGATION_PRIORITY",
            "Rao and Mitul set tonight's priority",
            "Inspector Rao agreed to focus resources on the plan Mitul "
            "chose for tonight.",
            "Lead"))) {
        cout << "\n[Clue noted: INVESTIGATION_PRIORITY]\n";
    }
}

void NPC::aaravLoop8Square(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "TOWN SQUARE - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nAarav waits by the fountain. He looks like he hasn't slept.\n";
    cout << "Aarav: \"" << player.getName() << ", everyone knows you've been building a case. "
         << "Even me.\"\n";

    cout << "\n1. Then you know how this ends.\n";
    cout << "2. Confess now. It will go easier.\n";
    cout << "3. Walk away.\n";
    int choice = askChoice("\nEnter choice: ", 1, 3);

    if (choice == 1) {
        cout << "\nAarav: \"No. I know how it STARTS. "
             << "Endings are rarer than you think.\"\n";
    } else if (choice == 2) {
        cout << "\nAarav: \"Confess to what? Being a good friend?\"\n";
        cout << "His hands shake. His voice does not.\n";
    }
}

void NPC::raoLoop8Assessment(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "POLICE STATION - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nInspector Rao closes your notebook.\n";
    cout << "Inspector Rao: \"" << player.getName() << ", three things make a case. "
         << "The documents. The suspect at the scene. The transfer link.\"\n";
    cout << "Inspector Rao: \"You have pieces of two. "
         << "Keep the pieces safe tonight.\"\n";
}

void NPC::harshitLoop8Evening(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "HARSHIT'S HOUSE - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nHarshit: \"Rao believes you?\"\n";
    cout << player.getName() << ": \"He believes the evidence.\"\n";
    cout << "Harshit: \"Then keep him close tonight.\"\n";
}

// ============================= LOOP 9 =============================

void NPC::harshitLoop9Morning(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "HARSHIT'S HOUSE - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nHarshit: \"The transfer reference - it links to the "
         << "discrepancy in the file. Look at the numbers.\"\n";

    if (player.getNotebook().addEvidence(Evidence(
            "TRANSFER_REFERENCE_LINK",
            "The transfer reference links to the falsified file",
            "The transfer reference number matches the falsified "
            "discrepancy in the property file - the fraud is connected "
            "to the transfer.",
            "Lead"))) {
        cout << "\n[Clue noted: TRANSFER_REFERENCE_LINK]\n";
    }
}

void NPC::clerkLoop9Transfer(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "RECORDS OFFICE - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nYou lay the numbers in front of the clerk.\n";
    cout << "Clerk: \"These match. That... should not match.\"\n";

    cout << "\n1. Who gains if the transfer is valid?\n";
    cout << "2. Ask him to sign a statement.\n";
    cout << "3. Leave.\n";
    int choice = askChoice("\nEnter choice: ", 1, 3);

    if (choice == 1) {
        cout << "\nClerk: \"The beneficiary. There is always a "
             << "beneficiary.\"\n";
    } else if (choice == 2) {
        cout << "\nClerk: \"For Rao? ...Fine. But I want protection.\"\n";
    }

    if (player.getNotebook().addEvidence(Evidence(
            "TRANSFER_REFERENCE_LINK",
            "The transfer reference links to the falsified file",
            "The transfer reference number matches the falsified "
            "discrepancy in the property file - the fraud is connected "
            "to the transfer.",
            "Lead"))) {
        cout << "\n[Clue noted: TRANSFER_REFERENCE_LINK]\n";
    }
}

void NPC::rameshLoop9Argument(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "RAMESH'S SHOP - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nRamesh: \"The night before the murder - I heard them. "
         << "Harshit and Aarav. At the gate.\"\n";
    cout << "Ramesh: \"Harshit shouted: 'I won't sign it away.' "
         << "Aarav said nothing. That was worse.\"\n";

    if (player.getNotebook().addEvidence(Evidence(
            "ARGUMENT_CONTEXT",
            "Harshit and Aarav argued about signing",
            "The night before the murder Ramesh heard Harshit refuse "
            "to 'sign it away' to Aarav, who said nothing.",
            "Uncertain"))) {
        cout << "\n[Clue noted: ARGUMENT_CONTEXT]\n";
    }
}

void NPC::aaravLoop9Confront(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "TOWN STREET - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nYou show Aarav the timeline. Then the transfer numbers.\n";
    cout << "His story breaks like thin ice.\n";
    cout << "Aarav: \"...Fine. I went to his house that night. "
         << "Once. To talk.\"\n";

    cout << "\n1. Talk about what?\n";
    cout << "2. You argued about the transfer.\n";
    cout << "3. Stay silent.\n";
    int choice = askChoice("\nEnter choice: ", 1, 3);

    if (choice == 1) {
        cout << "\nAarav: \"The land. He was going to ruin everything.\"\n";
    } else if (choice == 2) {
        cout << "\nAarav says nothing. That is an answer.\n";
    } else {
        cout << "\nYou hold his gaze and say nothing. "
             << "The silence does the asking.\n";
    }

    if (player.getNotebook().addEvidence(Evidence(
            "AARAV_VISIT_ADMISSION",
            "Aarav admits visiting Harshit the night of the murder",
            "After being shown the timeline, Aarav admitted he went to "
            "Harshit's house that night. An admission of a visit is not "
            "a confession of murder.",
            "Evidence"))) {
        cout << "\n[Clue noted: AARAV_VISIT_ADMISSION]\n";
    }
    player.increaseSuspicion(1);
}

void NPC::raoLoop9Reassess(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "POLICE STATION - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nInspector Rao: \"" << player.getName() << ", a changed story. An admission of a visit. "
         << "Strong.\"\n";
    cout << "Inspector Rao: \"But strong is not proven. "
         << "One more night. One more piece.\"\n";
}

void NPC::harshitLoop9Evening(Player& player, TimeLoop& timeLoop) {
    printDivider();
    cout << "HARSHIT'S HOUSE - " << timeLoop.getTimeString() << "\n";
    printDivider();
    cout << "\nHarshit: \"Tonight feels different.\"\n";
    cout << player.getName() << ": \"It is.\"\n";
    cout << "Harshit: \"Then don't let it end the same way.\"\n";
}
