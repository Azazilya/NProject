#include <iostream>
#include <vector>
using namespace std;

class Character {
public:
    virtual void status() = 0;
    virtual void skill() = 0;
    virtual void attack(Character& target) = 0;
    virtual void receiveDamage(int dmg) = 0;
    virtual bool isAlive() = 0;
    virtual ~Character() {}
};
class Warrior : public Character {
    string name;
    int health;

public:
    Warrior() : name("Arthur"), health(100) {}

    void status() {
        cout << name << " [HP: " << health << "]\n";
    }

    void skill() {
        cout << name << " Slash!\n";
    }

    void attack(Character& target) {
        cout << name << " menyerang dengan kekuatan besar!\n";
        target.receiveDamage(20);
    }

    void receiveDamage(int dmg) {
        health -= dmg;
        if (health < 0) health = 0;
    }

    bool isAlive() {
        return health > 0;
    }
 };

class Mage : public Character {
    string name;
    int health;
public:
    Mage() : name("Merlin"), health(80) {}

    void status() {
        cout << name << " [HP: " << health << "]\n";
    }
    void skill() {
        cout << name << " Cast!\n";
    }
    void attack(Character& target) {
        cout << name << " melemparkan bola api!\n";
        target.receiveDamage(25);
    }
    void receiveDamage(int dmg) {
        health -= dmg;
        if (health < 0) health = 0;
    }
    bool isAlive() {
        return health > 0;
    }
 };

class Archer : public Character {
    string name;
    int health;
public:
    Archer() : name("Esa"), health(90) {}
    void status() {
        cout << name << " [HP: " << health << "]\n";
    }
    void skill() {
        cout << name << " Shoot!\n";
    }
    void attack(Character& target) {
        cout << name << " menembakkan panah!\n";
        target.receiveDamage(15);
    }
    void receiveDamage(int dmg) {
        health -= dmg;
        if (health < 0) health = 0;
    }
    bool isAlive() {
        return health > 0;
    }
};

 int main() {
    Warrior w;
    Mage m;
    Archer a;


    m.status();
    a.status();

    w.skill();
    w.attack(m);
    m.status();

    m.skill();
    m.attack(w);
    w.status();

    a.skill();
    a.attack(w);
    w.status();

    return 0;
};