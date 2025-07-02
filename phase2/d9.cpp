#include <iostream>
#include <string>
using namespace std;

class IAttackBehavior {
public:
    virtual void attack(const string& attackerName, const string& targetName) = 0;
    virtual ~IAttackBehavior() {}
};

// Implementasi Attack Behavior
class SlashAttack : public IAttackBehavior {
public:
    void attack(const string& attackerName, const string& targetName) override {
        cout << attackerName << " menebas " << targetName << " dengan pedang! ⚔️\n";
    }
};

class FireballAttack : public IAttackBehavior {
public:
    void attack(const string& attackerName, const string& targetName) override {
        cout << attackerName << " melempar bola api ke " << targetName << "! 🔥\n";
    }
};

class StealthAttack : public IAttackBehavior {
public:
    void attack(const string& attackerName, const string& targetName) override {
        cout << attackerName << " menyerang diam-diam " << targetName << "! 🗡️\n";
    }
};

class BlastAttack : public IAttackBehavior {
public:
    void attack(const string& attackerName, const string& targetName) override {
        cout << attackerName << " meledakkan " << targetName << " dengan ledakan dahsyat! 💥\n";
    }
};

// Class Character
class Character {
protected:
    string name;
    int health;
    IAttackBehavior* attackStyle;

public:
    Character(string n, int h, IAttackBehavior* atk) : name(n), health(h), attackStyle(atk) {}
    virtual ~Character() {
        delete attackStyle;
        cout << name << " telah dihancurkan.\n";
    }

    virtual void status() {
        cout << name << " [HP: " << health << "]\n";
    }

    virtual void attack(Character& target) {
        if (attackStyle && isAlive()) {
            attackStyle->attack(name, target.name);
            target.takeDamage(20); // Default damage, bisa diubah per role
        }
    }

    void takeDamage(int dmg) {
        health -= dmg;
        if (health < 0) health = 0;
        cout << name << " tersisa " << health << " HP.\n";
    }

    bool isAlive() {
        return health > 0;
    }
};

class Warrior : public Character {
public:
    Warrior(string n, int h) : Character(n, h, new SlashAttack()) {}
};

class Mage : public Character {
public:
    Mage(string n, int h) : Character(n, h, new FireballAttack()) {}
};

class Assasin : public Character {
public:
    Assasin(string n, int h) : Character(n, h, new StealthAttack()) {}
};

class Necromancer : public Character {
public:
    Necromancer(string n, int h) : Character(n, h, new BlastAttack()) {}
};

int main() {
    Warrior* arthur = new Warrior("Arthur", 100);
    Mage* merlin = new Mage("Merlin", 80);
    Assasin* shadow = new Assasin("Shadow", 70);
    Necromancer* necro = new Necromancer("Necro", 90);

    arthur->status();
    merlin->status();
    shadow->status();
    necro->status();

    cout << "\n--- Pertarungan Dimulai ---\n";
    arthur->attack(*merlin);
    merlin->attack(*shadow);
    shadow->attack(*arthur);
    necro->attack(*merlin);

    delete arthur;
    delete merlin;
    delete shadow;
    delete necro;
    cout << "\n--- Pertarungan Selesai! ---\n";

    return 0;
};