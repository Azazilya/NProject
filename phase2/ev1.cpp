#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

// ===== Strategy Pattern =====
class IAttackBehavior {
public:
    virtual void attack(const string& attacker, const string& target) = 0;
    virtual ~IAttackBehavior() {}
};

class SlashAttack : public IAttackBehavior {
public:
    void attack(const string& attacker, const string& target) {
        cout << attacker << " menebas " << target << " dengan pedang! ⚔️\n";
    }
};

class FireballAttack : public IAttackBehavior {
public:
    void attack(const string& attacker, const string& target) {
        cout << attacker << " melempar bola api ke " << target << "! 🔥\n";
    }
};

class StealthAttack : public IAttackBehavior {
public:
    void attack(const string& attacker, const string& target) {
        cout << attacker << " menyerang diam-diam " << target << "! 🗡️\n";
    }
};

class BlastAttack : public IAttackBehavior {
public:
    void attack(const string& attacker, const string& target) {
        cout << attacker << " meledakkan " << target << " dengan ledakan! 💥\n";
    }
};

// ===== Forward declaration for Command
class Character;

// ===== Command Pattern =====
class Command {
public:
    virtual void execute(Character& actor, Character& target) = 0;
    virtual ~Command() {}
};

// ===== Character Base Class =====
class Character {
protected:
    string name;
    int health;
    bool isDefending;
    IAttackBehavior* attackStyle;

public:
    Character(string n, int h, IAttackBehavior* atk)
        : name(n), health(h), isDefending(false), attackStyle(atk) {}
    virtual ~Character() { delete attackStyle; }

    bool isAlive() const { return health > 0; }

    void takeDamage(int dmg) {
        if (isDefending) {
            dmg /= 2;
            cout << name << " bertahan! Damage dikurangi menjadi " << dmg << "\n";
            isDefending = false;
        }
        health -= dmg;
        if (health < 0) health = 0;
        cout << name << " menerima " << dmg << " damage. HP: " << health << endl;
    }

    void heal(int amount) {
        health += amount;
        cout << name << " memulihkan " << amount << " HP. Total HP: " << health << endl;
    }

    void defend() {
        isDefending = true;
        cout << name << " bersiap bertahan!\n";
    }

    virtual void attack(Character& target) {
        if (attackStyle && isAlive()) {
            attackStyle->attack(name, target.name);
            target.takeDamage(20);
        }
    }

    virtual void status() {
        cout << name << " [HP: " << health << "]\n";
    }

    string getName() const { return name; }
};

// ===== Command Implementations =====
class AttackCommand : public Command {
public:
    void execute(Character& actor, Character& target) {
        actor.attack(target);
    }
};

class DefendCommand : public Command {
public:
    void execute(Character& actor, Character&) {
        actor.defend();
    }
};

class HealCommand : public Command {
public:
    void execute(Character& actor, Character&) {
        actor.heal(15);
    }
};

// ===== Derived Characters =====
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

class Orc : public Character {
public:
    Orc(string n, int h) : Character(n, h, new BlastAttack()) {}
};

class Goblin : public Character {
public:
    Goblin(string n, int h) : Character(n, h, new StealthAttack()) {}
};

// ===== Party (Composite) =====
class Party {
private:
    vector<Character*> members;
public:
    void addMember(Character* member) {
        members.push_back(member);
    }

    vector<Character*>& getMembers() { return members; }

    void status() {
        for (size_t i = 0; i < members.size(); ++i) members[i]->status();
    }

    ~Party() {
        for (size_t i = 0; i < members.size(); ++i) delete members[i];
    }
};

// ===== BattleManager (Invoker) =====
class BattleManager {
private:
    queue<pair<Command*, pair<Character*, Character*> > > turnQueue;

public:
    void queueCommand(Command* cmd, Character* actor, Character* target) {
        turnQueue.push(make_pair(cmd, make_pair(actor, target)));
    }

    void processTurn() {
        while (!turnQueue.empty()) {
            pair<Command*, pair<Character*, Character*> > front = turnQueue.front();
            turnQueue.pop();
            Command* cmd = front.first;
            Character* actor = front.second.first;
            Character* target = front.second.second;
            cout << "[Action] " << actor->getName() << " => " << target->getName() << endl;
            cmd->execute(*actor, *target);
            delete cmd;
        }
    }
};

// ===== Main =====
int main() {
    Warrior* arthur = new Warrior("Arthur", 100);
    Mage* merlin = new Mage("Merlin", 90);
    Assasin* shadow = new Assasin("Shadow", 70);
    Orc* grom = new Orc("Grom", 120);
    Goblin* sneaky = new Goblin("Sneaky", 60);

    Party* heroParty = new Party();
    heroParty->addMember(arthur);
    heroParty->addMember(merlin);
    heroParty->addMember(shadow);

    Party* enemyParty = new Party();
    enemyParty->addMember(grom);
    enemyParty->addMember(sneaky);

    BattleManager bm;

    // Turn 1 - Hero menyerang
    bm.queueCommand(new AttackCommand(), arthur, grom);
    bm.queueCommand(new AttackCommand(), merlin, sneaky);
    bm.queueCommand(new AttackCommand(), shadow, grom);

    // Turn 2 - Musuh membalas
    bm.queueCommand(new AttackCommand(), grom, arthur);
    bm.queueCommand(new DefendCommand(), sneaky, sneaky);

    cout << "\n=== PERTARUNGAN DIMULAI ===\n";
    bm.processTurn();

    cout << "\n=== STATUS AKHIR ===\n";
    cout << "-- HERO PARTY --\n"; heroParty->status();
    cout << "-- ENEMY PARTY --\n"; enemyParty->status();

    delete heroParty;
    delete enemyParty;
    return 0;
}