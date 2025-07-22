#include <iostream>
#include <string>

using namespace std;

class Character {
protected:
    string name;
public:
    Character(const string& n) : name(n) {}
    virtual void move() {
        cout << name << " melangkah maju!\n";
    }
    virtual void attack() {
        cout << name << " menyerang dengan pedang!\n";
    }
    virtual void defend() {
        cout << name << " bertahan dengan perisai!\n";
    }
    virtual string getName() const { return name; }
    virtual ~Character() {}
};

class Command {
public:
    virtual void execute(Character* target) = 0;
    virtual string getName() const = 0;
    virtual ~Command() {}
};

class MoveCommand : public Command {
public:
    void execute(Character* target) {
        if (target) target->move();
    }
    string getName() const { return "Move"; }
};

class AttackCommand : public Command {
public:
    void execute(Character* target) {
        if (target) target->attack();
    }
    string getName() const { return "Attack"; }
};

class DefendCommand : public Command {
public:
    void execute(Character* target) {
        if (target) target->defend();
    }
    string getName() const { return "Defend"; }
};

int main() {

    Character* warrior = new Character("Warrior");


    Command* move = new MoveCommand();
    Command* attack = new AttackCommand();
    Command* defend = new DefendCommand();

    // Eksekusi perintah satu per satu
    move->execute(warrior);
    attack->execute(warrior);
    defend->execute(warrior);

    // (Opsional) Simpan ke dalam history
    Command* history[3] = {move, attack, defend};
    cout << "\nHistory:\n";
    for (int i = 0; i < 3; ++i) {
        cout << "- " << history[i]->getName() << endl;
    }

    // Bersihkan memori
    delete move;
    delete attack;
    delete defend;
    delete warrior;

    return 0;
}
