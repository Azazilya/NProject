#include <iostream>
#include <string>
using namespace std;

class Character {
private:
    string name;
    string role;
    int health;
    int level;

public:
    Character(string n, string r, int h, int l) {
        name = n;
        role = r;
        setHealth(h);  // gunakan setter agar aman
        setLevel(l);
    }

    // Setter
    void setHealth(int h) {
        if (h >= 0) health = h;
        else health = 0;
    }

    void setLevel(int l) {
        if (l >= 1) level = l;
        else level = 1;
    }

    // Getter
    int getHealth() { return health; }
    int getLevel() { return level; }
    string getName() { return name; }
    string getRole() { return role; }

    void status() {
        cout << "=== STATUS ===" << endl;
        cout << "Nama  : " << name << endl;
        cout << "Role  : " << role << endl;
        cout << "Level : " << level << endl;
        cout << "HP    : " << health << endl << endl;
    }
};

int main() {
    Character hero("Arthur", "Warrior", 100, 5);
    hero.status();

    Character mage("Merlin", "Mage", -50, 0); // Uji setter
    mage.status();

    return 0;
}
