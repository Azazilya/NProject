#include <iostream>
#include <string>
using namespace std;

// Class 
class Character {
public:
    string name;
    string role;
    int health;
    int level;

    // Method (Fungsi di dalam class)
    void introduce() {
        cout << "Namaku " << name << ", levelku " << level << "!" << endl;
    }
        void status() {
        cout << "=== STATUS ===" << endl;
        cout << "Nama  : " << name << endl;
        cout << "Role  : " << role << endl;
        cout << "Level : " << level << endl;
        cout << "HP    : " << health << endl;
        cout << endl;
    }
};

// Main 
int main() {

    // Object dari class
    Character hero;
    hero.role = "Warrior";
    hero.name = "Arthur";
    hero.level = 5;
    hero.health = 100;
    hero.introduce();
    hero.status();

    Character mage;
    mage.name = "Merlin";
    mage.role = "Mage";
    mage.health = 70;
    mage.level = 12;
    mage.introduce();
    mage.status();

    return 0;
}
