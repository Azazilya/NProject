#include <iostream>
#include <string>
using namespace std;

class Character {
public:
    virtual void status() = 0;
    virtual void attack(Character& target) = 0;
    virtual void takeDamage(int dmg) = 0;
    virtual void takeTurn() = 0;
    virtual string getName() const = 0;
    virtual int getHealth() const = 0;
    virtual void setHealth(int h) = 0;
    virtual Character* removeEffect() { return this; } // default tidak ada efek
    virtual ~Character() {}
};

class BaseCharacter : public Character {
protected:
    string name;
    int health;
public:
    BaseCharacter(string n, int h) : name(n), health(h) {}
    virtual void status() {
        cout << name << " (HP: " << health << ")\n";
    }
    virtual void attack(Character& target) {}
    virtual void takeDamage(int dmg) {
        health -= dmg;
        if (health < 0) health = 0;
    }
    virtual void takeTurn() {}
    virtual string getName() const { return name; }
    virtual int getHealth() const { return health; }
    virtual void setHealth(int h) { health = h; }
    virtual ~BaseCharacter() {}
};

class CharacterDecorator : public Character {
protected:
    Character* wrapped;
public:
    CharacterDecorator(Character* c) : wrapped(c) {}
    virtual void status() { wrapped->status(); }
    virtual void attack(Character& target) { wrapped->attack(target); }
    virtual void takeDamage(int dmg) { wrapped->takeDamage(dmg); }
    virtual void takeTurn() { wrapped->takeTurn(); }
    virtual string getName() const { return wrapped->getName(); }
    virtual int getHealth() const { return wrapped->getHealth(); }
    virtual void setHealth(int h) { wrapped->setHealth(h); }
    virtual Character* removeEffect() { return wrapped; }
    virtual ~CharacterDecorator() { delete wrapped; }
};

// ========== Poisoned Effect ==========
class Poisoned : public CharacterDecorator {
    int duration;
public:
    Poisoned(Character* c, int d) : CharacterDecorator(c), duration(d) {}
    virtual void status() {
        CharacterDecorator::status();
        cout << getName() << " is poisoned! (" << duration << " turns left)\n";
    }
    virtual void takeTurn() {
        CharacterDecorator::takeTurn();
        if (duration > 0) {
            cout << getName() << " takes poison damage!\n";
            setHealth(getHealth() - 5);
            duration--;
        }
        if (duration == 0) {
            cout << getName() << "'s poison wears off.\n";
        }
    }
    virtual Character* removeEffect() {
        if (duration <= 0)
            return wrapped;
        return this;
    }
};

// ========== Shielded Effect ==========
class Shielded : public CharacterDecorator {
    int duration;
public:
    Shielded(Character* c, int d) : CharacterDecorator(c), duration(d) {}
    virtual void status() {
        CharacterDecorator::status();
        cout << getName() << " is shielded! (" << duration << " turns left)\n";
    }
    virtual void takeTurn() {
        CharacterDecorator::takeTurn();
        if (duration > 0) {
            cout << getName() << " is protected by shield!\n";
            duration--;
        }
        if (duration == 0) {
            cout << getName() << "'s shield fades.\n";
        }
    }
    virtual void takeDamage(int dmg) override {
        if (duration > 0) {
            cout << getName() << " shield absorbs part of the damage!\n";
            wrapped->takeDamage(dmg / 2);
        } else {
            wrapped->takeDamage(dmg);
        }
    }
    virtual Character* removeEffect() {
        if (duration <= 0)
            return wrapped;
        return this;
    }
};

// ========== Warrior & Mage ==========
class Warrior : public BaseCharacter {
public:
    Warrior(string n, int h) : BaseCharacter(n, h) {}
    void attack(Character& target) {
        cout << name << " menebas musuh dengan pedang! ⚔️\n";
        target.takeDamage(20);
    }
};

class Mage : public BaseCharacter {
public:
    Mage(string n, int h) : BaseCharacter(n, h) {}
    void attack(Character& target) {
        cout << name << " melempar bola api! 🔥\n";
        target.takeDamage(25);
    }
};

// ========== Main ==========
int main() {
    Character* warrior = new Warrior("Arthur", 100);
    Character* mage = new Mage("Merlin", 80);

    warrior = new Poisoned(warrior, 2); // 2 turn racun
    mage = new Shielded(mage, 3);       // 3 turn perisai

    cout << "\n=== Status Awal ===\n";
    warrior->status();
    mage->status();

    for (int turn = 1; turn <= 4; ++turn) {
        cout << "\n=== Giliran Ke-" << turn << " ===\n";
        warrior->takeTurn();
        mage->takeTurn();

        // Perbarui efek jika durasi habis
        Character* newWarrior = warrior->removeEffect();
        if (newWarrior != warrior) {
            delete warrior;
            warrior = newWarrior;
        }

        Character* newMage = mage->removeEffect();
        if (newMage != mage) {
            delete mage;
            mage = newMage;
        }

        cout << "\nStatus setelah giliran " << turn << ":\n";
        warrior->status();
        mage->status();
    }

    cout << "\n=== Serangan ===\n";
    warrior->attack(*mage);
    mage->attack(*warrior);

    cout << "\n=== Status Akhir ===\n";
    warrior->status();
    mage->status();

    delete warrior;
    delete mage;
    return 0;
}