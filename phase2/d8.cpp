#include <iostream>
#include <string>
using namespace std;

class Character {
protected:
    string name;
    int health;

public:
    Character(string n, int h) : name(n) {
        setHealth (h);
    }

    void setHealth(int h) {
        health = (h >= 0) ? h : 0;
    }
    virtual ~Character() {
        cout << name << "destroyed.\n";
    }

    string getName() const { return name; }
    int getHealth() const { return health; }

    virtual bool isAlive() const {
        return health > 0;
    }

    virtual void status() {
        cout << name << " has " << health << " HP.\n";
    }
    virtual void attack(Character& target) = 0;

    virtual void takeDamage(int dmg) {
        health -= dmg;
        if (health < 0) health = 0;
        cout << name << " now has " << health << " HP.\n";
    }
    virtual void taketurn () {
        cout << name << " takes a turn.\n";
    }
};

class Warrior : public Character {
public:
    Warrior(string n, int h) : Character(n,h) {}
    void status() {
    cout << name << " " << health << " HP.\n";
    }

    void taketurn() {
        cout << name << " turn.\n";
    }
    void attack(Character& target) { 
    int damage = 20;
    cout << name << " slashes!\n"; 
    cout << name << " attacks " << target.getName() << " with " << damage << "!\n";
    target.takeDamage(damage);
    }
};

class Mage : public Character {
public:
    Mage(string n, int h) : Character(n,h) {}
    void status() {
    cout << name << " " << health << " HP.\n";
    }

    void taketurn() {
        cout << name << " turn.\n";
    }
    void attack(Character& target) { 
    int damage = 30;
    cout << name << " casts fireball!\n"; 
    cout << name << " attacks " << target.getName() << " with " << damage << "!\n";
    target.takeDamage(damage);
    }
};

class Assasin : public Character {
public:
    Assasin(string n, int h) : Character(n,h) {}
    void status() {
    cout << name << " " << health << " HP.\n";
    }

    void taketurn() {
        cout << name << " turn.\n";
    }
    void attack(Character& target) { 
    int damage = 30;
    cout << name << " strikes from the shadows!\n";
    cout << name << " attacks " << target.getName() << " with " << damage << "!\n";
    target.takeDamage(damage);
    }
};

int main() {
    Character* c1 = new Warrior("Arthur", 100);
    Character* c2 = new Mage("Merlin", 80);
    Character* c3 = new Assasin("Shadow", 70);
    c1->status();
    c2->status();
    c3->status();
    cout << "Attacks:\n";

    c1->taketurn();
    c1->attack(*c2);
    c2->taketurn();
    c2->attack(*c1);
    c3->taketurn();
    c3->attack(*c2);

    cout << "End Turn\n";
    delete c1;
    delete c2;
    delete c3;
    return 0;
}