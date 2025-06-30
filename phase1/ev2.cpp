#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Character {
protected:
    string name;
    int health,level;

public:
    Character(string n, int l, int h) {
        name = n;
        setLevel(l);
        setHealth(h);
    }

    void setLevel(int l) { level = (l >= 1) ? l : 1; }
    void setHealth(int h) { health = (h >= 0) ? h : 0; }

virtual void status() {
        cout << "[ " << name << " ]\n";
        cout << "Level : " << level << ", HP : " << health << "\n";
    }

    bool isAlive() {
        return health > 0;
    }

    void attack(Character& target) {
        if (!isAlive()) {
            cout << name << " sudah kalah dan tidak bisa menyerang!\n";
            return;
        }
        if (!target.isAlive()) {
            cout << target.getName() << " sudah kalah, tidak bisa diserang!\n";
            return;
        }

        int damage = 10 * level;
        cout << name << " menyerang " << target.getName() << " dengan " << damage << " damage!\n";
        target.takeDamage(damage);
    }

    void takeDamage(int dmg) {
        health -= dmg;
        if (health < 0) health = 0;
        cout << name << " tersisa " << health << " HP.\n";
    }

    string getName() const { return name; }

    virtual void skill() = 0;
    virtual ~Character() {}
};

class Warrior : public Character {
public:
    Warrior(string n, int l, int h) : Character(n, l, h) {}
    void skill() override {
        cout << name << " menggunakan skill Warrior: Slash!\n";
    }
};

class Mage : public Character {
public:
    Mage(string n, int l, int h) : Character(n, l, h) {}
    void skill() override {
        cout << name << " menggunakan skill Mage: Fireball!\n";
    }
};

class Assasin : public Character {
public:
    Assasin(string n, int l, int h) : Character(n, l, h) {}
    void skill() override {
        cout << name << " menggunakan skill Assasin: Stealth Attack!\n";
    }
};

int main() {
    vector<Character*> characters;

    Warrior* w = new Warrior("Arthur", 5, 100);
    Mage* m = new Mage("Merlin", 4, 80);
    Assasin* a = new Assasin("Shadow", 3, 60);
    characters.push_back(w);
    characters.push_back(m);
    characters.push_back(a);

    // Tampilkan status awal
    for (Character* c : characters) {
        c->status();
    }

    // Contoh aksi: Warrior menyerang Mage
    w->attack(*m);
    // Mage menggunakan skill
    m->skill();
    // Assasin menyerang Warrior
    a->attack(*w);

    // Tampilkan status akhir
    for (size_t i = 0; i < characters.size(); ++i) {
        characters[i]->status();
        if (!characters[i]->isAlive()) {
            cout << characters[i]->getName() << " telah kalah!\n";
        }
    }
    while (w->isAlive() && m->isAlive() && a->isAlive()) {
        w->attack(*m);
        m->attack(*a);
        a->attack(*w);
    }
    cout << "Pertarungan selesai!\n";
    if (!w->isAlive() && !m->isAlive() && !a->isAlive()) {
        cout << "Semua karakter telah kalah!\n";
    } else {
        if (w->isAlive()) cout << w->getName() << " masih hidup!\n";
        if (m->isAlive()) cout << m->getName() << " masih hidup!\n";
        if (a->isAlive()) cout << a->getName() << " masih hidup!\n";
    }

    // Bersihkan memori
    for (size_t i = 0; i < characters.size(); ++i) {
        delete characters[i];
    }

    return 0;
};