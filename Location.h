#ifndef LOCATION_H
#define LOCATION_H

#include <iostream>
#include <string>
using namespace std;

class Location
{
private:
    string name;
    string description;

public:
    Location(string n, string d)
    {
        name = n;
        description = d;
    }

    void showLocation()
    {
        cout << "\nLocation: " << name << endl;
        cout << description << endl;
    }
};

#endif
