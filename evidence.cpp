#include "Evidence.h"
#include <iostream>
using namespace std;

Evidence::Evidence(string i, string t, string d, string l)
{
    id = i;
    title = t;
    description = d;
    location = l;
}

string Evidence::getId() const
{
    return id;
}

string Evidence::getTitle() const
{
    return title;
}

string Evidence::getDescription() const
{
    return description;
}

string Evidence::getLocation() const
{
    return location;
}

void Evidence::display() const
{
    cout << "\n----------------------------------" << endl;
    cout << "Evidence ID   : " << id << endl;
    cout << "Clue          : " << title << endl;
    cout << "Description   : " << description << endl;
    cout << "Found at      : " << location << endl;
    cout << "----------------------------------" << endl;
}