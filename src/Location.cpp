// Location.cpp - one place on the town map.

#include "Declarations.cpp"

Location::Location(const string& name, const string& description) {
    this->name = name;
    this->description = description;
}

string Location::getName() const {
    return name;
}

string Location::getDescription() const {
    return description;
}

void Location::display() const {
    cout << name << " - " << description << "\n";
}
