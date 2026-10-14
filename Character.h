#ifndef CHARACTER_H
#define CHARACTER_H
#include <iostream>
#include <string>
using namespace std;
class Character
{
protected:
  string name;
  string dialogue;
public:
  Character(string n,string d)
  {
    name = n;
    dialogue =d;
  }
  void introduce()
  {
    cout<<name<<":"<<dialogue<<endl;
  }
};
#endif

