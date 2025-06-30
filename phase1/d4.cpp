#include <iostream>
#include <string>
using namespace std;

class Character {
protected:
    string name, role;
    int health, level;

public:
    Character(string n, string r, int l, int h) {
        name = n;
        role = r;
        setLevel(l);
        setHealth(h);
    }

    void setLevel(int l) { level = (l >= 1) ? l : 1; }
    void setHealth(int h) { health = (h >= 0) ? h : 0; }

    void status() {
        cout << "[ " << name << " the " << role << " ]\n";
        cout << "Level : " << level << ", Health : " << health << "\n\n";
    }
};

// Class turunan Warrior
class Warrior : public Character {
public:
    Warrior(string n, int l, int h) : Character(n, "Warrior", l, h) {}

    void powerStrike() {
        cout << name << " menggunakan Power Strike! 💥\n";
    }
        void ragePower() {
        cout << name << " menggunakan Rage POWER!\n";
    }
};

// Class turunan Mage
class Mage : public Character {
public:
    Mage(string n, int l, int h) : Character(n, "Mage", l, h) {}

    void castSpell() {
        cout << name << " melemparkan Fireball! 🔥\n";
    }
    void castSpellpower() {
        cout << name << " cast Mana Power 🔥\n";
    }

};

// Class turunan Assasin
class Assasin : public Character {
public:
    Assasin(string n, int l, int h) : Character(n, "Assasin", l, h) {}

    void stealthAttack() {
        cout << name << " melakukan serangan diam-diam! 🗡️\n";
    }
    void shadowStrike() {
        cout << name << " menggunakan Shadow Strike! \n";
    }
};
int main() {
    Warrior hero("Arthur", 5, 100);
    Mage mage("Merlin", 7, 60);
    Assasin assasin("Shadow", 6, 80);

    hero.status();
    hero.powerStrike();
    hero.ragePower();

    mage.status();
    mage.castSpell();
    mage.castSpellpower();

    assasin.status();
    assasin.stealthAttack();
    assasin.shadowStrike();


    return 0;
}
