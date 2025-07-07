#include <iostream>
#include <string>
using namespace std;

class Character;

// === Interface State ===
class State {
public:
    virtual void attack(Character& self, Character& target) = 0;
    virtual void takeDamage(Character& self, int dmg) = 0;
    virtual string getName() const = 0;
    virtual ~State() {}
};

// === Character Interface ===
class Character {
public:
    virtual void attack(Character& target) = 0;
    virtual void takeDamage(int dmg) = 0;
    virtual void status() const = 0;
    virtual string getName() const = 0;
    virtual int getHealth() const = 0;
    virtual void setHealth(int h) = 0;
    virtual string getCurrentStateName() const = 0;
    virtual void setState(State* s) = 0;
    virtual void checkAutoBerserk() = 0;
    virtual ~Character() {}
};

// === State Implementations ===
class NormalState : public State {
public:
    void attack(Character& self, Character& target) override {
        cout << self.getName() << " attacks normally. Deals 10 damage!\n";
        target.takeDamage(10);
    }

    void takeDamage(Character& self, int dmg) override {
        cout << self.getName() << " receives " << dmg << " damage.\n";
        self.setHealth(self.getHealth() - dmg);
    }

    string getName() const override {
        return "Normal";
    }
};

class BerserkState : public State {
public:
    void attack(Character& self, Character& target) override {
        cout << self.getName() << " attacks furiously! Deals 35 damage!\n";
        target.takeDamage(35);
    }

    void takeDamage(Character& self, int dmg) override {
        cout << self.getName() << " receives " << dmg << " damage in return!\n";
        self.setHealth(self.getHealth() - dmg);
    }

    string getName() const override {
        return "Berserk";
    }
};

class DefendState : public State {
public:
    void attack(Character& self, Character&) override {
        cout << self.getName() << " does not attack while defending.\n";
    }

    void takeDamage(Character& self, int dmg) override {
        int reduced = dmg / 2;
        cout << self.getName() << " defends! Receives only " << reduced << " damage.\n";
        self.setHealth(self.getHealth() - reduced);
    }

    string getName() const override {
        return "Defend";
    }
};

// === BasicCharacter ===
class BasicCharacter : public Character {
protected:
    string name;
    int health;
    State* currentState;
public:
    BasicCharacter(string n, int h) : name(n), health(h), currentState(new NormalState()) {}

    void attack(Character& target) override {
        checkAutoBerserk();
        currentState->attack(*this, target);
    }

    void takeDamage(int dmg) override {
        currentState->takeDamage(*this, dmg);
        checkAutoBerserk();
    }

    void status() const override {
        cout << name << " (HP: " << health << ") - Mode: " << getCurrentStateName() << endl;
    }

    string getName() const override { return name; }
    int getHealth() const override { return health; }
    void setHealth(int h) override { health = h; }

    string getCurrentStateName() const override {
        return currentState->getName();
    }

    void setState(State* newState) override {
        if (currentState) delete currentState;
        currentState = newState;
        cout << name << " is now in " << currentState->getName() << " mode!\n";
    }

    void checkAutoBerserk() override {
        if (health <= 50 && getCurrentStateName() != "Berserk") {
            setState(new BerserkState());
        }
    }

    ~BasicCharacter() {
        delete currentState;
    }
};

// === Decorator ===
class CharacterDecorator : public Character {
protected:
    Character* wrapped;
public:
    CharacterDecorator(Character* c) : wrapped(c) {}

    void attack(Character& target) override {
        wrapped->attack(target);
    }

    void takeDamage(int dmg) override {
        wrapped->takeDamage(dmg);
    }

    void status() const override {
        wrapped->status();
    }

    string getName() const override {
        return wrapped->getName();
    }

    int getHealth() const override {
        return wrapped->getHealth();
    }

    void setHealth(int h) override {
        wrapped->setHealth(h);
    }

    string getCurrentStateName() const override {
        return wrapped->getCurrentStateName();
    }

    void setState(State* s) override {
        wrapped->setState(s);
    }

    void checkAutoBerserk() override {
        wrapped->checkAutoBerserk();
    }

    virtual ~CharacterDecorator() {
        delete wrapped;
    }
};

// === Poisoned Decorator ===
class PoisonedCharacter : public CharacterDecorator {
public:
    PoisonedCharacter(Character* c) : CharacterDecorator(c) {}

    void takeDamage(int dmg) override {
        wrapped->takeDamage(dmg);
        int poison = 5;
        cout << getName() << " suffers " << poison << " poison damage!\n";
        wrapped->setHealth(wrapped->getHealth() - poison);
        checkAutoBerserk();
    }

    string getCurrentStateName() const override {
        return wrapped->getCurrentStateName() + " + Poisoned";
    }
};

// === MAIN ===
int main() {
    Character* arthur = new BasicCharacter("Arthur", 100);
    Character* merlin = new BasicCharacter("Merlin", 80);

    arthur->setState(new BerserkState());
    merlin->setState(new DefendState());

    cout << "\n--- Battle Start ---\n";
    arthur->attack(*merlin);
    merlin->attack(*arthur);

    cout << "\n--- After Initial Turn ---\n";
    arthur->status();
    merlin->status();

    // Tambahkan efek Poison ke Merlin
    merlin = new PoisonedCharacter(merlin);
    cout << "\nMerlin is poisoned!\n";

    arthur->attack(*merlin);
    merlin->attack(*arthur);

    cout << "\n--- Final Status ---\n";
    arthur->status();
    merlin->status();

    delete arthur;
    delete merlin;
    return 0;
}