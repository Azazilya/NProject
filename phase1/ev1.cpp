#include <iostream>
#include <string>
using namespace std;

class Character {
private:
    string name, role;
    int health, level;

public:
    Character(string n, string r, int h, int l) {
        name = n;
        role = r;
        setHealth(h);
        setLevel(l);
    }

    ~Character() {
        cout << "Karakter " << name << " selesai digunakan.\n";
    }

    void setHealth(int h) {
        health = (h >= 0) ? h : 0;
    }

    void setLevel(int l) {
        level = (l >= 1) ? l : 1;
    }

    void status() {
        cout << "[ " << name << " the " << role << " ]" << endl;
        cout << "Level : " << level << ", Health : " << health << endl << endl;
    }
};

int main() {
    Character hero("Ragnar", "Berserker", 120, 10);
    Character errorChar("Buggy", "Ghost", -80, 0);

    hero.status();
    errorChar.status();

    return 0;
}
