#ifndef EVIDENCE_H
#define EVIDENCE_H

#include <string>
using namespace std;

class Evidence
{
private:
    string id;
    string title;
    string description;
    string location;

public:
    Evidence(string i, string t, string d, string l);

    string getId() const;
    string getTitle() const;
    string getDescription() const;
    string getLocation() const;

    void display() const;
};

#endif