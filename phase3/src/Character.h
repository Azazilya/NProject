#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <iostream>
using namespace std;

class Character {
    string name;
public:
    Character(const string& n);
    void move();
    void attack();
    void defend();
};

#endif
