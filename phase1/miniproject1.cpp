#include <iostream>
#include <string>
using namespace std;

class Character {
protected:
    string name;
    int health, level;

public:
    Character(string n, int h, int l = 1) {
        name = n;
        setHealth(h);
        setLevel(l);
    }

    virtual ~Character() {}

    bool isAlive() const {
        return health > 0;
    }

    void setHealth(int h) {
        health = (h >= 0) ? h : 0;
    }

    void setLevel(int l) {
        level = (l >= 1) ? l : 1;
    }

    string getName() const {
        return name;
    }

    int getHealth() const {
        return health;
    }

    virtual void status() = 0;
    virtual void attack(Character& target) = 0;
    virtual void takeDamage(int dmg) {
        health -= dmg;
        if (health < 0) health = 0;
        cout << name << " tersisa " << health << " HP.\n";
    }
};

// === Class Turunan ===

class Warrior : public Character {
public:
    Warrior(string n, int h, int l = 1) : Character(n, h, l) {}

    void status() override {
        cout << "[Warrior] " << name << " [HP: " << health << "]\n";
    }

    void attack(Character& target) override {
        int damage = 15 * level;
        if (!isAlive()) {
            cout << name << " telah dikalahkan, tidak bisa menyerang!\n";
            return;
        }
        if (!target.isAlive()) {
            cout << target.getName() << " sudah kalah, tidak bisa diserang!\n";
            return;
        }
        cout << name << " menyerang " << target.getName() << " dengan Power Strike! 💥\n";
        target.takeDamage(damage);
    }
};

class Mage : public Character {
public:
    Mage(string n, int h, int l = 1) : Character(n, h, l) {}

    void status() override {
        cout << "[Mage] " << name << " [HP: " << health << "]\n";
    }

    void attack(Character& target) override {
        int damage = 12 * level;
        if (!isAlive()) {
            cout << name << " telah dikalahkan, tidak bisa menyerang!\n";
            return;
        }
        if (!target.isAlive()) {
            cout << target.getName() << " sudah kalah, tidak bisa diserang!\n";
            return;
        }
        cout << name << " melemparkan Fireball! 🔥\n";
        target.takeDamage(damage);
    }
};

class Archer : public Character {
public:
    Archer(string n, int h, int l = 1) : Character(n, h, l) {}

    void status() override {
        cout << "[Archer] " << name << " [HP: " << health << "]\n";
    }

    void attack(Character& target) override {
        int damage = 10 * level;
        if (!isAlive()) {
            cout << name << " telah dikalahkan, tidak bisa menyerang!\n";
            return;
        }
        if (!target.isAlive()) {
            cout << target.getName() << " sudah kalah, tidak bisa diserang!\n";
            return;
        }
        cout << name << " menembakkan panah! 🏹\n";
        target.takeDamage(damage);
    }
};

class Assasin : public Character {
public:
    Assasin(string n, int h, int l = 1) : Character(n, h, l) {}

    void status() override {
        cout << "[Assasin] " << name << " [HP: " << health << "]\n";
    }

    void attack(Character& target) override {
        int damage = 18 * level;
        if (!isAlive()) {
            cout << name << " telah dikalahkan, tidak bisa menyerang!\n";
            return;
        }
        if (!target.isAlive()) {
            cout << target.getName() << " sudah kalah, tidak bisa diserang!\n";
            return;
        }
        cout << name << " menyerang diam-diam! 🗡️\n";
        target.takeDamage(damage);
    }
};

int main() {
    Warrior hero("Arthur", 100, 2);
    Mage mage("Merlin", 90, 2);
    Archer archer("Esa", 80, 2);
    Assasin assasin("Shadow", 70, 2);

    while (hero.isAlive() && mage.isAlive() && archer.isAlive() && assasin.isAlive()) {
        cout << "\n--- Status ---\n";
        hero.status();
        mage.status();
        archer.status();
        assasin.status();

        cout << "\n--- Aksi ---\n";
        hero.attack(mage);
        mage.attack(archer);
        archer.attack(hero);
        assasin.attack(mage);
    }

    cout << "\n--- Pertarungan Selesai! ---\n";
    if (!hero.isAlive()) cout << "Arthur telah dikalahkan!\n";
    if (!mage.isAlive()) cout << "Merlin telah dikalahkan!\n";
    if (!archer.isAlive()) cout << "Esa telah dikalahkan!\n";
    if (!assasin.isAlive()) cout << "Shadow telah dikalahkan!\n";

    int aliveCount = 0;
    string winner;
    if (hero.isAlive()) { aliveCount++; winner = hero.getName(); }
    if (mage.isAlive()) { aliveCount++; winner = mage.getName(); }
    if (archer.isAlive()) { aliveCount++; winner = archer.getName(); }
    if (assasin.isAlive()) { aliveCount++; winner = assasin.getName(); }

    if (aliveCount == 1) {
        cout << "Pemenangnya adalah: " << winner << "!\n";
    } else if (aliveCount > 1) {
        cout << "Pertarungan berakhir seri!\n";
    } else {
        cout << "Tidak ada pemenang!\n";
    }

    return 0;
}
