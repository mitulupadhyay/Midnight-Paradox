// Evidence.cpp - one clue: id, name, description, reliability label.

#include "Declarations.cpp"

Evidence::Evidence(const string& id, const string& name,
                   const string& description, const string& reliability) {
    this->id = id;
    this->name = name;
    this->description = description;
    this->reliability = reliability;
}

string Evidence::getId() const {
    return id;
}

string Evidence::getName() const {
    return name;
}

string Evidence::getDescription() const {
    return description;
}

string Evidence::getReliability() const {
    return reliability;
}

void Evidence::display() const {
    cout << "[" << id << "] (" << reliability << ") " << name << "\n";
    cout << "   " << description << "\n";
}
