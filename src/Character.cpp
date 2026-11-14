// Character.cpp - base class for people; shows inheritance and polymorphism.

#include "Declarations.cpp"

Character::Character(const string& name, const string& role) {
    this->name = name;
    this->role = role;
}

// Virtual destructor: safe deletion through a Character pointer.
Character::~Character() {
    // Strings clean themselves up.
}

string Character::getName() const {
    return name;
}

string Character::getRole() const {
    return role;
}

void Character::introduction() const {
    cout << "- " << name << " (" << role << ")\n";
}

void Character::interact(Player& player) {
    cout << name << ": \"Sorry, " << player.getName()
         << ", I have nothing new to say right now.\"\n";
}
