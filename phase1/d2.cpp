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
        cout << "Nama " << name << ", level " << level << "!" << endl;
    }
    // Constructor
    Character(string n, string r, int h, int l) {
        name = n;
        role = r;
        health = h;
        level = l;
        cout << "Karakter " << name << " dibuat!\n";
    }

    // Destructor
    ~Character() {
        cout << "Karakter " << name << " selesai digunakan.\n";
    }

    void status() {
        cout << name << " [level " << level << "] - HP: " << health << endl;
    }
};

// Main 
int main() {

    // Object dari class
    Character hero("Arthur", "Warrior", 100, 10);
    hero.introduce();
    hero.status();

    Character mage("Merlin", "Mage", 80, 8);
    mage.introduce();
    mage.status();

    return 0;
}
