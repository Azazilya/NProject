#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Interface dasar
class Unit {
public:
    virtual void attack(class Character& target) = 0;
    virtual void status() = 0;
    virtual ~Unit() {}
};

// Karakter individu
class Character : public Unit {
protected:
    string name;
    int health;

public:
    Character(string n, int h) : name(n), health(h) {}
    bool isAlive() const { return health > 0; }

    void takeDamage(int dmg) {
        health -= dmg;
        if (health < 0) health = 0;
        cout << name << " menerima " << dmg << " damage. Sisa HP: " << health << endl;
    }

    void status() {
        cout << name << " [HP: " << health << "]\n";
    }

    virtual void attack(Character& target) = 0;
    string getName() const { return name; }
    virtual ~Character() {}
};

class Warrior : public Character {
public:
    Warrior(string n, int h) : Character(n, h) {}
    void attack(Character& target) {
        cout << name << " menebas musuh dengan pedang! ⚔️\n";
        target.takeDamage(20);
    }
};
class Mage : public Character {
public:
    Mage(string n, int h) : Character(n, h) {}
    void attack(Character& target) {
        cout << name << " melempar bola api! 🔥\n";
        target.takeDamage(25);
    }
};
class Orc : public Character {
public:
    Orc(string n, int h) : Character(n, h) {}
    void attack(Character& target) {
        cout << name << " menghantam musuh dengan gada! 💥\n";
        target.takeDamage(15);
    }
};
class Goblin : public Character {
public:
    Goblin(string n, int h) : Character(n, h) {}
    void attack(Character& target) {
        cout << name << " menyerang dengan pisau curian! 🗡️\n";
        target.takeDamage(10);
    }
};

class Party : public Unit {
private:
    vector<Unit*> members;

public:
    void addMember(Unit* member) {
        members.push_back(member);
    }

    void attack(Character& target) {
        cout << "Party menyerang " << target.getName() << "!\n";
        for (int i = 0; i < members.size(); ++i) {
            members[i]->attack(target);
        }
    }

    void status() {
        cout << "=== Status Party ===\n";
        for (int i = 0; i < members.size(); ++i) {
            members[i]->status();
        }
        cout << "====================\n";
    }

    ~Party() {
        for (int i = 0; i < members.size(); ++i)
            delete members[i];
    }
};
// Tambahan untuk akses nama (biar bisa dibaca oleh Party)
int main() {
    // Buat karakter
    Warrior* warrior = new Warrior("Arthur", 100);
    Mage* mage = new Mage("Merlin", 80);
    Orc* orc = new Orc("Grug", 120);
    Goblin* goblin = new Goblin("Sneaky", 60);

    // Buat party
    Party* heroParty = new Party();
    heroParty->addMember(warrior);
    heroParty->addMember(mage);

    Party* enemyParty = new Party();
    enemyParty->addMember(orc);
    enemyParty->addMember(goblin);

    // Status awal
    cout << "--- Status Awal ---\n";
    heroParty->status();
    enemyParty->status();

    // Pertarungan
    cout << "\n=== Pertarungan Dimulai ===\n";
    heroParty->attack(*orc);
    enemyParty->attack(*warrior);

    // Status akhir
    cout << "\n--- Status Setelah Serangan ---\n";
    heroParty->status();
    enemyParty->status();

    delete heroParty;
    delete enemyParty;

    return 0;
}
