// Notebook.cpp - stores Mitul's clues; survives the time loop, prevents duplicates.

#include "Declarations.cpp"

bool Notebook::hasEvidence(const string& id) const {
    for (int i = 0; i < static_cast<int>(entries.size()); i++) {
        if (entries[i].getId() == id) {
            return true;
        }
    }
    return false;
}

// Returns true only if the evidence was new.
bool Notebook::addEvidence(const Evidence& evidence) {
    if (hasEvidence(evidence.getId())) {
        return false;
    }
    entries.push_back(evidence);
    return true;
}

void Notebook::display() const {
    if (entries.empty()) {
        cout << "(The notebook is empty.)\n";
        return;
    }
    for (int i = 0; i < static_cast<int>(entries.size()); i++) {
        cout << (i + 1) << ". ";
        entries[i].display();
        cout << "\n";
    }
}

int Notebook::size() const {
    return static_cast<int>(entries.size());
}

// How many entries carry a given reliability label.
int Notebook::countReliability(const string& reliability) const {
    int count = 0;
    for (int i = 0; i < static_cast<int>(entries.size()); i++) {
        if (entries[i].getReliability() == reliability) {
            count = count + 1;
        }
    }
    return count;
}

void Notebook::clear() {
    entries.clear();
}
