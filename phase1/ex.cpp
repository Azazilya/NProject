#include <iostream>
using namespace std;

class Fighter {
private:
    string name;
    int health;

public:
    Fighter(string n, int h) : name(n) {
        health = (h > 0) ? h : 0;
    }

    void attack(Fighter& target) {
        int damage = 20;
        cout << name << " menyerang " << target.name << " dengan " << damage << " damage!\n";
        target.takeDamage(damage);
    }

    void takeDamage(int dmg) {
        health -= dmg;
        if (health < 0) health = 0;
        cout << name << " tersisa " << health << " HP.\n";
    }

    void status() {
        cout << name << " [HP: " << health << "]\n";
    }
};

int main() {
    Fighter a("Aang", 100);
    Fighter z("Zuko", 80);

    a.status();
    z.status();

    a.attack(z);

    return 0;
}
