#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>

class Character;
class ICharacterState;

class IObserver {
public:
    virtual ~IObserver() {}
    virtual void onNotify(const Character& character, const std::string& eventMessage) = 0;
};

class ISubject {
public:
    virtual ~ISubject() {}
    virtual void attach(IObserver* observer) = 0;
    virtual void detach(IObserver* observer) = 0;
    virtual void notify(const std::string& eventMessage) = 0;
};

class BattleLogger : public IObserver {
public:
    void onNotify(const Character& character, const std::string& eventMessage);
};

class IAttackStrategy {
public:
    virtual ~IAttackStrategy() {}
    virtual void attack(const std::string& attackerName, const std::string& target) const = 0;
};

class SwordAttack : public IAttackStrategy {
public:
    void attack(const std::string& attackerName, const std::string& target) const {
        std::cout << "-> " << attackerName << " swings their sword at " << target << "! Deals 15 damage." << std::endl;
    }
};

class FireballCast : public IAttackStrategy {
public:
    void attack(const std::string& attackerName, const std::string& target) const {
        std::cout << "-> " << attackerName << " casts Fireball at " << target << "! Deals 25 damage." << std::endl;
    }
};

class FuriousAttack : public IAttackStrategy {
public:
    void attack(const std::string& attackerName, const std::string& target) const {
        std::cout << "-> " << attackerName << " attacks furiously at " << target << "! Deals 30 damage!" << std::endl;
    }
};

class ICharacterState {
public:
    virtual ~ICharacterState() {}
    virtual void enterState(Character* character) = 0;
    virtual void attack(Character* character, const std::string& target) = 0;
};


class ICombatant {
public:
    virtual ~ICombatant() {}
    virtual std::string getName() const = 0;
    virtual void attack(const std::string& target) = 0;
};

class Character : public ICombatant, public ISubject {
private:
    std::string name;
    int hp;
    int maxHp;
    IAttackStrategy* currentStrategy;
    ICharacterState* currentState;
    std::vector<IObserver*> observers;

public:
    Character(std::string name, int hp, IAttackStrategy* strategy)
        : name(name), hp(hp), maxHp(hp), currentStrategy(strategy), currentState(0) {}

    ~Character() {
        if (currentStrategy) delete currentStrategy;
        if (currentState) delete currentState;
    }

    void attach(IObserver* observer) {
        observers.push_back(observer);
    }

    void detach(IObserver* observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

    void notify(const std::string& eventMessage) {
        for (size_t i = 0; i < observers.size(); ++i) {
            observers[i]->onNotify(*this, eventMessage);
        }
    }

    void setAttackStrategy(IAttackStrategy* newStrategy) {
        if (currentStrategy) delete currentStrategy;
        currentStrategy = newStrategy;
    }
    
    void performAttack(const std::string& target) {
        if (currentStrategy) {
            currentStrategy->attack(this->name, target);
            notify("Dealt damage to " + target);
        }
    }

    void setState(ICharacterState* newState);

    std::string getName() const { return name; }
    
    void attack(const std::string& target);

    void takeDamage(int damage) {
        this->hp -= damage;
        if (this->hp <= 0) {
            this->hp = 0;
            notify("has died.");
        } else {
            notify("HP is now " + std::to_string(this->hp));
        }
    }
};

// --- State classes ---
class NormalState : public ICharacterState {
public:
    void enterState(Character* /*character*/) override {
        // No-op
    }
    void attack(Character* character, const std::string& target) override {
        character->performAttack(target);
    }
};

class BerserkState : public ICharacterState {
public:
    void enterState(Character* character) override {
        std::cout << character->getName() << " is now in BERSERK mode!" << std::endl;
        character->notify("is now in Berserk mode.");
    }
    void attack(Character* character, const std::string& target) override {
        FuriousAttack furiousAttack;
        furiousAttack.attack(character->getName(), target);
        character->notify("Dealt furious damage to " + target);
    }
};

class DefendState : public ICharacterState {
public:
    void enterState(Character* character) override {
        std::cout << character->getName() << " is now in DEFEND mode!" << std::endl;
        character->notify("is now in Defend mode.");
    }
    void attack(Character* character, const std::string& target) override {
        (void)target;
        std::cout << "-> " << character->getName() << " holds a defensive stance and cannot attack." << std::endl;
    }
};

// --- Character method definitions ---
void Character::setState(ICharacterState* newState) {
    if (currentState) delete currentState;
    currentState = newState;
    if (currentState) currentState->enterState(this);
}

void Character::attack(const std::string& target) {
    if (this->hp > 0 && currentState) {
        currentState->attack(this, target);
    }
}

// --- Party class ---
class Party : public ICombatant {
private:
    std::string name;
    std::vector<ICombatant*> members;

public:
    Party(const std::string& name) : name(name) {}

    void addMember(ICombatant* member) {
        members.push_back(member);
    }

    std::string getName() const { return name; }

    void attack(const std::string& target) override {
        std::cout << "\n" << this->name << " attacks " << target << "!" << std::endl;
        for (size_t i = 0; i < members.size(); ++i) {
            members[i]->attack(target);
        }
    }
};

// --- BattleLogger implementation ---
void BattleLogger::onNotify(const Character& character, const std::string& eventMessage) {
    std::cout << "[LOG] " << character.getName() << " " << eventMessage << std::endl;
}

// --- main function ---
int main() {
    BattleLogger logger;

    Character* arthur = new Character("Arthur", 100, new SwordAttack());
    Character* merlin = new Character("Merlin", 80, new FireballCast());

    arthur->attach(&logger);
    merlin->attach(&logger);

    Party partyA("Party A");
    partyA.addMember(arthur);
    partyA.addMember(merlin);

    std::cout << "[GOBLIN muncul!]\n";

    partyA.attack("Goblin");

    std::cout << "\n--- Arthur's turn ---" << std::endl;
    arthur->setState(new BerserkState());
    arthur->attack("Goblin");

    std::cout << "\n--- Merlin's turn ---" << std::endl;
    std::cout << "Merlin prepares a different spell!" << std::endl;
    merlin->setAttackStrategy(new FuriousAttack());
    merlin->attack("Goblin");
    
    std::cout << "\n--- Goblin attacks back! ---" << std::endl;
    arthur->takeDamage(40);
    
    std::cout << "\n--- Arthur's next turn ---" << std::endl;
    arthur->setState(new DefendState());
    arthur->attack("Goblin");

    std::cout << "\n--- Another strong attack from Goblin! ---" << std::endl;
    merlin->takeDamage(95);

    delete arthur;
    delete merlin;
    return 0;
};