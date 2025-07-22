#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Character {
    string name;
public:
    Character(const string& n) : name(n) {}
    void move() { cout << name << " moves forward.\n"; }
    void attack() { cout << name << " attacks!\n"; }
    void defend() { cout << name << " defends!\n"; }
};

class Command {
public:
    virtual void execute(Character* c) = 0;
    virtual ~Command() {}
};

class MoveCommand : public Command {
public:
    void execute(Character* c) { if (c) c->move(); }
};
class AttackCommand : public Command {
public:
    void execute(Character* c) { if (c) c->attack(); }
};
class DefendCommand : public Command {
public:
    void execute(Character* c) { if (c) c->defend(); }
};

int main() {
    Character hero("Knight");

    vector<Command*> queue;
    queue.push_back(new MoveCommand());
    queue.push_back(new AttackCommand());
    queue.push_back(new DefendCommand());

    for (int i = 0; i < queue.size(); ++i) {
        queue[i]->execute(&hero);
        delete queue[i];
    }
}
