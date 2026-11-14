// EndingManager.cpp - case status and the four endings.
// decideEnding is deterministic (never random). Suspicion, an uncertain
// sighting or a motive is never proof - proof is a chain: altered records
// + the suspect at the scene + the property-transfer link.

#include "Declarations.cpp"

// Does the notebook contain a chain that can actually be presented as a case?
bool EndingManager::hasSufficientProof(const Player& player) const {
    const Notebook& notebook = player.getNotebook();

    // 1) Documentary evidence that the property records were altered.
    bool recordsFraud =
        notebook.hasEvidence("RECORD_DISCREPANCY") ||
        notebook.hasEvidence("ALTERED_RECORD_COPY");

    // 2) Evidence placing Aarav at the scene (his admission - NOT the uncertain sighting).
    bool presenceAtScene =
        notebook.hasEvidence("AARAV_VISIT_ADMISSION");

    // 3) The link between Aarav and the property transfer (the motive).
    bool motiveLink =
        notebook.hasEvidence("TRANSFER_REFERENCE_LINK") ||
        notebook.hasEvidence("AARAV_FRAUD_ADMISSION");

    return recordsFraud && presenceAtScene && motiveLink;
}

// The ending decision, in priority order:
//   1) wrong accusation -> False Accusation    2) rescue without police -> Sacrifice
//   3) proof + all actions -> True Detective   4) anything else -> Endless Loop
int EndingManager::decideEnding(const Player& player,
                                bool harshitSafe,
                                bool inspectorInformed,
                                bool evidencePreserved,
                                bool aaravConfronted,
                                bool rescueWithoutSupport,
                                const string& accusedSuspect) const {

    // 1) The player formally accused somebody who is not Aarav.
    if (accusedSuspect != "" && accusedSuspect != "Aarav") {
        return ENDING_FALSE_ACCUSATION;
    }

    // 2) The player rushed to save Harshit without police support; Ramesh is exposed.
    if (rescueWithoutSupport) {
        return ENDING_SACRIFICE;
    }

    // 3) The good ending: Harshit safe, Rao involved, records preserved,
    //    the right suspect confronted - AND a real chain of proof.
    if (harshitSafe && inspectorInformed && evidencePreserved &&
        aaravConfronted && hasSufficientProof(player)) {
        return ENDING_TRUE_DETECTIVE;
    }

    // 4) Everything else: the case is not solved, so the day repeats.
    return ENDING_ENDLESS_LOOP;
}

string EndingManager::endingName(int endingId) const {
    if (endingId == ENDING_FALSE_ACCUSATION) {
        return "FALSE ACCUSATION";
    }
    if (endingId == ENDING_SACRIFICE) {
        return "SACRIFICE";
    }
    if (endingId == ENDING_ENDLESS_LOOP) {
        return "ENDLESS LOOP";
    }
    if (endingId == ENDING_TRUE_DETECTIVE) {
        return "TRUE DETECTIVE";
    }
    return "UNKNOWN";
}

// What the notebook proves - and what it does not.
void EndingManager::showCaseStatus(const Player& player) const {
    const Notebook& notebook = player.getNotebook();

    cout << "\n";
    printDivider();
    cout << "CASE STATUS\n";
    printDivider();

    cout << "\nEvidence collected: " << notebook.size() << "\n";
    cout << "  Verified evidence ........ " << notebook.countReliability("Verified") << "\n";
    cout << "  Evidence (clues/documents)  " << notebook.countReliability("Evidence") << "\n";
    cout << "  Uncertain claims .......... " << notebook.countReliability("Uncertain") << "\n";
    cout << "  Leads ..................... " << notebook.countReliability("Lead") << "\n";
    cout << "  Suspicion only ............ " << notebook.countReliability("Suspicion") << "\n";

    cout << "\nCase checklist:\n";
    cout << "  [" << (notebook.hasEvidence("LAND_RECORDS_LEAD") ? "x" : " ")
         << "] Harshit's land-record investigation found\n";
    cout << "  [" << (notebook.hasEvidence("FIRST_MURDER") ? "x" : " ")
         << "] The murder witnessed\n";
    cout << "  [" << (notebook.hasEvidence("PHONE_MESSAGE") ? "x" : " ")
         << "] Harshit's hidden message found\n";
    cout << "  [" << (notebook.hasEvidence("RAMESH_SIGHTING") ? "x" : " ")
         << "] An uncertain sighting documented\n";
    cout << "  [" << (notebook.hasEvidence("RECORD_DISCREPANCY") ||
                        notebook.hasEvidence("ALTERED_RECORD_COPY") ? "x" : " ")
         << "] The altered records documented\n";
    cout << "  [" << (notebook.hasEvidence("AARAV_VISIT_ADMISSION") ? "x" : " ")
         << "] A suspect's presence at the scene established\n";
    cout << "  [" << (notebook.hasEvidence("TRANSFER_REFERENCE_LINK") ||
                        notebook.hasEvidence("AARAV_FRAUD_ADMISSION") ? "x" : " ")
         << "] The property-transfer link established\n";

    cout << "\nSuspicion level (Aarav): " << player.getSuspicionOfAarav()
         << "/10 - suspicion is never proof.\n";

    if (hasSufficientProof(player)) {
        cout << "\nReliable proof of the killer: A PROVABLE CHAIN EXISTS.\n";
    } else {
        cout << "\nReliable proof of the killer: NOT YET.\n";
        cout << "(A witness who is unsure, or a person with a motive,\n";
        cout << " is never enough on its own.)\n";
    }

    cout << "\nEvidence alone is not the final step: the last night also\n";
    cout << "requires ACTION - protect Harshit, involve Inspector Rao,\n";
    cout << "and confront the right suspect in time.\n";

    // Show what the current run would resolve to with no final actions yet.
    int outcome = decideEnding(player, false, false, false, false, false, "");
    cout << "\nIf the case ended right now: -> " << endingName(outcome) << "\n";

    printDivider();
}

void EndingManager::showEndingPreview() const {
    cout << "\nTHE FOUR ENDINGS\n";
    cout << "1. False Accusation - accuse an innocent person without enough proof.\n";
    cout << "2. Sacrifice        - save Harshit but lose the witness, Ramesh.\n";
    cout << "3. Endless Loop     - fail to build a case; the day repeats forever.\n";
    cout << "4. True Detective   - prove the case and protect Harshit in time.\n";
    cout << "\nWhich ending you see depends on your choices and your evidence, "
         << "never on luck.\n";
    cout << "(The four ending scenes play out in Loop 10.)\n";
}

void EndingManager::showEnding(int endingId) const {
    cout << "\n";
    printDivider();
    cout << "ENDING: " << endingName(endingId) << "\n";
    printDivider();

    if (endingId == ENDING_FALSE_ACCUSATION) {
        cout << "\nMitul presents a misleading case to Inspector Rao. "
             << "An innocent person is arrested, while Aarav remains "
             << "free. Harshit is murdered that night, and the clock "
             << "resets to 8:00 AM.\n\n";
        cout << "Mitul: \"I was so certain I had solved it. "
             << "How could I have been so wrong?\"\n\n";
        cout << "Result: The loop continues because the real killer "
             << "has not been stopped.\n";
    } else if (endingId == ENDING_SACRIFICE) {
        cout << "\nMitul rushes to save Harshit without arranging "
             << "sufficient police support. He gets Harshit away from "
             << "immediate danger, but the intervention leaves the "
             << "witness exposed. Ramesh, the witness, is killed during "
             << "the confrontation. The available evidence is lost or "
             << "remains insufficient, and the clock resets.\n\n";
        cout << "Mitul: \"I saved him... but I couldn't save "
             << "everyone.\"\n\n";
        cout << "Result: Harshit may be saved temporarily, but the "
             << "witness dies and the loop resets. The investigation "
             << "must begin again.\n";
    } else if (endingId == ENDING_ENDLESS_LOOP) {
        cout << "\nMitul reaches midnight again without proving who "
             << "killed Harshit. The same message arrives, the same "
             << "night unfolds, and Harshit dies once more.\n\n";
        cout << "This time, the screen shows the notebook filling with "
             << "the same incomplete clues. The dates change, but "
             << "nothing else does.\n\n";
        cout << "Mitul: \"There must be something I'm missing. "
             << "There has to be...\"\n\n";
        cout << "Result: The cycle continues indefinitely. There is no "
             << "resolution until the player restarts and investigates "
             << "more effectively.\n";
    } else {
        cout << "\nENDING UNLOCKED\n";
        cout << "THE DAY AFTER MIDNIGHT\n\n";
        cout << "Harshit survived. Aarav's involvement was exposed. "
             << "Inspector Rao took charge of the investigation. "
             << "For the first time in ten loops, tomorrow is no longer "
             << "a repetition of today.\n\n";
        cout << "Mitul: \"I finally understand. I wasn't trapped "
             << "because I couldn't find the truth. I was trapped "
             << "because I kept reaching it too late.\"\n\n";
        cout << "Mitul closed his notebook. Nine times, he had watched "
             << "the same day end in tragedy. He had searched for "
             << "clues, questioned friends, followed false leads, and "
             << "slowly uncovered a truth nobody wanted to face.\n\n";
        cout << "He had not changed the past. He had used what he "
             << "remembered to change what happened next.\n\n";
        cout << "Outside, the first light of morning appeared.\n\n";
        cout << "For the first time, it was a new day.\n";
    }

    waitForContinue();
}
