// Player.cpp - Mitul: notebook and suspicion level.

#include "Declarations.cpp"

Player::Player(const string& playerName)
    : Character(playerName, "The detective (you)") {
    suspicionOfAarav = 0;
}

// Mitul's interact() checks his own notebook.
void Player::interact(Player& player) {
    cout << "\nMitul checks his notebook.\n";
    player.showNotebook();
}

Notebook& Player::getNotebook() {
    return notebook;
}

// Const version, so ending logic can READ the notebook safely.
const Notebook& Player::getNotebook() const {
    return notebook;
}

int Player::getSuspicionOfAarav() const {
    return suspicionOfAarav;
}

void Player::increaseSuspicion(int amount) {
    suspicionOfAarav = suspicionOfAarav + amount;
    if (suspicionOfAarav < 0) {
        suspicionOfAarav = 0;
    }
    if (suspicionOfAarav > 10) {
        suspicionOfAarav = 10;
    }
}

void Player::showNotebook() const {
    cout << "\n";
    printDivider();
    cout << "MITUL'S NOTEBOOK\n";
    printDivider();
    notebook.display();
    cout << "Suspicion level (Aarav): " << suspicionOfAarav << "/10\n";
    cout << "(Suspicion is not proof. Only reliable evidence can prove guilt.)\n";
    printDivider();
}

void Player::resetInvestigation() {
    notebook.clear();
    suspicionOfAarav = 0;
}
