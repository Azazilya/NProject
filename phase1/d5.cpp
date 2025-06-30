#include <iostream>
#include <string>
#include <vector>
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

    virtual void status() {
        cout << "[ " << name << " the " << role << " ]\n";
        cout << "Level : " << level << ", Health : " << health << "\n\n";
    }

    virtual void skill() {
        cout << name << " is ready to fight!\n";
    }
};

// Class turunan Warrior
class Warrior : public Character {
public:
    Warrior(string n, int l, int h) : Character(n, "Warrior", l, h) {}

    void powerStrike() {
        cout << name << " use Power Strike! 💥\n";
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
        cout << name << " cast Fireball! 🔥\n";
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
        cout << name << " do Shadow Strike! \n";
    }
};
int main() {
    Warrior hero("Arthur", 5, 100);
    Mage mage("Merlin", 7, 60);
    Assasin assasin("Shadow", 6, 80);
    vector<Character*> party;
    party.push_back(new Warrior("Arthur", 5, 100));
    party.push_back(new Mage("Merlin", 7, 60));
    party.push_back(new Assasin("Shadow", 6, 80));


    for (size_t i = 0; i < party.size(); ++i) {
        party[i]->status(); // Panggil method status via pointer induk!
    }

    for (size_t i = 0; i < party.size(); ++i) {
        if (Warrior* w = dynamic_cast<Warrior*>(party[i])) {
            w->powerStrike();
            // w->ragePower();
        } else if (Mage* m = dynamic_cast<Mage*>(party[i])) {
            m->castSpell();
            // m->castSpellpower();
        } else if (Assasin* a = dynamic_cast<Assasin*>(party[i])) {
            // a->stealthAttack();
            a->shadowStrike();
        }
    }

    // Bersihkan memori
    for (Character* c : party) {
        delete c;
    }

    return 0;
}