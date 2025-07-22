#include <iostream>
#include <string>

class Character;
class ICharacterState;

// =================== STRATEGY ====================
class IAttackStrategy {
public:
    virtual ~IAttackStrategy() {}
    virtual void execute(Character& attacker, Character& target) = 0;
    virtual std::string getName() const = 0;
};

class NormalAttack;
class FireAttack;
class PoisonAttack;

// =============== STATE INTERFACE =================
class ICharacterState {
protected:
    Character* character_;
public:
    virtual ~ICharacterState() {}
    void setCharacter(Character* character) { character_ = character; }
    virtual std::string getStateName() const = 0;
    virtual int onDamageDealt(int baseDamage) = 0;
    virtual int onDamageTaken(int baseDamage) = 0;
    virtual void onTurnEnd() = 0;
};

// =============== CHARACTER CLASS =================
class Character {
    std::string name_;
    int health_;
    int baseDamage_;
    IAttackStrategy* attackStrategy_;
    ICharacterState* state_;
public:
    Character(std::string name, int health, int baseDamage, IAttackStrategy* strategy, ICharacterState* state)
        : name_(name), health_(health), baseDamage_(baseDamage), attackStrategy_(strategy), state_(state) {
        this->state_->setCharacter(this);
        std::cout << name_ << " is now in " << state_->getStateName() << " mode.\n";
    }

    ~Character() {
        delete attackStrategy_;
        delete state_;
    }

    void setState(ICharacterState* newState) {
        delete state_;
        state_ = newState;
        state_->setCharacter(this);
        std::cout << name_ << " is now in " << state_->getStateName() << " mode.\n";
    }

    void setAttackStrategy(IAttackStrategy* newStrategy) {
        delete attackStrategy_;
        attackStrategy_ = newStrategy;
        std::cout << name_ << " is now using " << attackStrategy_->getName() << ".\n";
    }

    void attack(Character& target) {
        std::cout << "--------------------------------\n";
        attackStrategy_->execute(*this, target);
    }

    void takeDamage(int damage) {
        int finalDamage = state_->onDamageTaken(damage);
        health_ -= finalDamage;
        if (health_ < 0) health_ = 0;
        std::cout << name_ << " receives " << finalDamage << " damage! (" << health_ << " HP left)\n";
    }

    void updateOnTurnEnd() { state_->onTurnEnd(); }

    bool isAlive() const { return health_ > 0; }
    const std::string& getName() const { return name_; }
    int getBaseDamage() const { return baseDamage_; }
    int getHealth() const { return health_; }
    std::string getStatusName() const { return state_->getStateName(); }
    int modifyDealtDamage(int damage) { return state_->onDamageDealt(damage); }

    void reduceHealthDirectly(int damage) {
        health_ -= damage;
        if (health_ < 0) health_ = 0;
    }
};

// ============ STATE IMPLEMENTATIONS =============
class NormalState : public ICharacterState {
public:
    std::string getStateName() const { return "NORMAL"; }
    int onDamageDealt(int damage) { return damage; }
    int onDamageTaken(int damage) { return damage; }
    void onTurnEnd() {}
};

class BerserkState : public ICharacterState {
public:
    std::string getStateName() const { return "BERSERK"; }
    int onDamageDealt(int damage) {
        std::cout << "Berserk rage multiplies damage!\n";
        return damage * 2;
    }
    int onDamageTaken(int damage) {
        std::cout << "Berserk rage lowers defense!\n";
        return static_cast<int>(damage * 1.5);
    }
    void onTurnEnd() {}
};

class DefendState : public ICharacterState {
public:
    std::string getStateName() const { return "DEFEND"; }
    int onDamageDealt(int damage) { return damage; }
    int onDamageTaken(int damage) {
        std::cout << "Defensive stance reduces damage!\n";
        return static_cast<int>(damage * 0.5);
    }
    void onTurnEnd() {}
};

class PoisonedState : public ICharacterState {
    int poisonDamage_;
public:
    PoisonedState() : poisonDamage_(5) {}
    std::string getStateName() const { return "POISONED"; }
    int onDamageDealt(int damage) { return damage; }
    int onDamageTaken(int damage) { return damage; }
    void onTurnEnd() {
        std::cout << character_->getName() << " receives " << poisonDamage_ << " poison damage!\n";
        character_->reduceHealthDirectly(poisonDamage_);
    }
};

// ============ STRATEGY IMPLEMENTATIONS ============
class NormalAttack : public IAttackStrategy {
public:
    void execute(Character& attacker, Character& target) {
        int finalDamage = attacker.modifyDealtDamage(attacker.getBaseDamage());
        std::cout << attacker.getName() << " attacks " << target.getName()
                  << " with " << getName() << "! Deals " << finalDamage << " damage!\n";
        target.takeDamage(finalDamage);
    }
    std::string getName() const { return "Normal Attack"; }
};

class FireAttack : public IAttackStrategy {
public:
    void execute(Character& attacker, Character& target) {
        int finalDamage = attacker.modifyDealtDamage(attacker.getBaseDamage() * 1.5);
        std::cout << attacker.getName() << " attacks " << target.getName()
                  << " with " << getName() << "! Huge fireball! Deals " << finalDamage << " damage!\n";
        target.takeDamage(finalDamage);
    }
    std::string getName() const { return "Fire Attack"; }
};

class PoisonAttack : public IAttackStrategy {
public:
    void execute(Character& attacker, Character& target) {
        int finalDamage = attacker.modifyDealtDamage(attacker.getBaseDamage() * 0.8);
        std::cout << attacker.getName() << " attacks " << target.getName()
                  << " with " << getName() << "! Venomous strike! Deals " << finalDamage << " damage!\n";
        target.takeDamage(finalDamage);
        std::cout << target.getName() << " is poisoned!\n";
        target.setState(new PoisonedState());
    }
    std::string getName() const { return "Poison Attack"; }
};

// ===================== MAIN ==========================
void printStatus(const Character& player, const Character& enemy) {
    std::cout << "\n=========== STATUS ===========\n";
    std::cout << player.getName() << " [HP: " << player.getHealth()
              << ", State: " << player.getStatusName() << "]\n";
    std::cout << enemy.getName() << " [HP: " << enemy.getHealth()
              << ", State: " << enemy.getStatusName() << "]\n";
    std::cout << "==============================\n";
}

int main() {
    Character* player = new Character("Knight", 100, 20, new NormalAttack(), new NormalState());
    Character* enemy  = new Character("Goblin", 80, 15, new NormalAttack(), new NormalState());

    int turn = 1;
    while (player->isAlive() && enemy->isAlive()) {
        std::cout << "\n<<<<<<<<<< TURN " << turn << " >>>>>>>>>>\n";
        printStatus(*player, *enemy);

        int choice = 0;
        std::cout << "\nPlayer's action:\n1. Attack\n2. Change Attack\n3. Change State\n> ";
        std::cin >> choice;

        if (choice == 1) {
            player->attack(*enemy);
        } else if (choice == 2) {
            int s;
            std::cout << "Choose: 1.Normal 2.Fire 3.Poison\n> ";
            std::cin >> s;
            if (s == 1) player->setAttackStrategy(new NormalAttack());
            else if (s == 2) player->setAttackStrategy(new FireAttack());
            else if (s == 3) player->setAttackStrategy(new PoisonAttack());
        } else if (choice == 3) {
            int s;
            std::cout << "Choose: 1.Normal 2.Berserk 3.Defend\n> ";
            std::cin >> s;
            if (s == 1) player->setState(new NormalState());
            else if (s == 2) player->setState(new BerserkState());
            else if (s == 3) player->setState(new DefendState());
        }

        player->updateOnTurnEnd();
        if (!enemy->isAlive()) break;

        std::cout << "\n--- Enemy's Turn ---\n";
        enemy->attack(*player);
        enemy->updateOnTurnEnd();

        turn++;
    }

    std::cout << "\n========== BATTLE ENDED ==========\n";
    if (player->isAlive()) std::cout << player->getName() << " is victorious!\n";
    else std::cout << enemy->getName() << " has won the battle!\n";

    delete player;
    delete enemy;
    return 0;
}
