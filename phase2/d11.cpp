#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

class Character {
public:
    string name;
    int health = 100;
    bool isDefending = false;

    Character(string n) : name(n) {}

    void takeDamage(int dmg) {
        if (isDefending) {
            dmg /= 2;
            cout << name << " bertahan! Damage dikurangi setengah menjadi " << dmg << "!\n";
            isDefending = false; // Reset defend
        }
        health -= dmg;
        if (health < 0) health = 0;
        cout << name << " menerima " << dmg << " damage. HP: " << health << endl;
    }

    void heal(int amount) {
        health += amount;
        cout << name << " sembuh " << amount << " HP. HP sekarang: " << health << endl;
    }

    void defend() {
        isDefending = true;
        cout << name << " bersiap untuk bertahan! (Damage selanjutnya akan dikurangi)\n";
    }
};

// Interface Command
class Command {
public:
    virtual void execute(Character& target) = 0;
    virtual void undo(Character& target) {} // optional override
    virtual ~Command() {}
};

// Command Serangan
class AttackCommand : public Command {
    int lastDamage = 10;
public:
    void execute(Character& target) override {
        target.takeDamage(lastDamage);
    }
    void undo(Character& target) override {
        target.heal(lastDamage);
        cout << "[Undo] Serangan dibatalkan. " << target.name << " mendapatkan kembali " << lastDamage << " HP.\n";
    }
};

// Command Heal
class HealCommand : public Command {
    int amount = 15;
public:
    void execute(Character& target) override {
        target.heal(amount);
    }
    void undo(Character& target) override {
        target.takeDamage(amount);
        cout << "[Undo] Penyembuhan dibatalkan. " << target.name << " kehilangan kembali " << amount << " HP.\n";
    }
};

// Command Defend
class DefendCommand : public Command {
public:
    void execute(Character& target) override {
        target.defend();
    }
    void undo(Character& target) override {
        target.isDefending = false;
        cout << "[Undo] Status bertahan dibatalkan.\n";
    }
};

// Fungsi untuk memproses daftar perintah (queue)
void processCommandQueue(vector<Command*>& queue, Character& target, stack<Command*>& history) {
    for (Command* cmd : queue) {
        cmd->execute(target);
        history.push(cmd);
    }
    queue.clear();
}

// Fungsi undo
void undoLastCommand(stack<Command*>& history, Character& target) {
    if (!history.empty()) {
        Command* last = history.top();
        last->undo(target);
        history.pop();
    } else {
        cout << "Tidak ada aksi untuk dibatalkan.\n";
    }
}

int main() {
    Character hero("Hero");

    // Commands
    AttackCommand* attack = new AttackCommand();
    HealCommand* heal = new HealCommand();
    DefendCommand* defend = new DefendCommand();

    // Queue dan history
    vector<Command*> commandQueue;
    stack<Command*> history;

    // Isi queue aksi
    commandQueue.push_back(attack);
    commandQueue.push_back(heal);
    commandQueue.push_back(defend);
    commandQueue.push_back(attack);

    cout << "== MULAI PERTARUNGAN ==\n";
    cout << hero.name << " [HP: " << hero.health << "]\n\n";

    processCommandQueue(commandQueue, hero, history);

    cout << "\n== UNDO TERAKHIR ==\n";
    undoLastCommand(history, hero);

    cout << "\n== UNDO LAGI ==\n";
    undoLastCommand(history, hero);

    cout << "\n== STATUS AKHIR ==\n";
    cout << hero.name << " [HP: " << hero.health << "]\n";

    delete attack;
    delete heal;
    delete defend;

    return 0;
}
