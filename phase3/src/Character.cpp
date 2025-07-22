#include "Character.h"

Character::Character(const string& n) : name(n) {}
void Character::move() { cout << name << " bergerak ke depan!\n"; }
void Character::attack() { cout << name << " menyerang musuh!\n"; }
void Character::defend() { cout << name << " bertahan dengan perisai!\n"; }
