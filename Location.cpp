
#include "Location.h"

Location::Location(string n, string d)
{
    name = n;
    description = d;
}

void Location::showLocation()
{
    cout << "\nLocation: " << name << endl;
    cout << description << endl;
}