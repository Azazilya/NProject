#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Character {
protected:
    string name;
    int health,level;

public:
    Character(string n, int h, int l) {
        if (l < 1) l = 1; 
        if (h < 0) h = 0;
        name = n;
        setHealth(h);
        setLevel(l);
    }
bool isAlive() {
        return health > 0;
    }
    void setLevel(int l) { level = (l >= 1) ? l : 1; }
    void setHealth(int h) { health = (h >= 0) ? h : 0; }

    virtual void status() {
        cout << "Name : " << name << ", Health : " << health << "\n\n";
    }

        void attack(Character& target) {
        int damage = 10 * level; // Damage based on level
        if (damage < 0) damage = 0; // Ensure damage is not negative
        if (target.health <= 0) {
            cout << target.name << " telah dikalahkan, tidak bisa diserang lagi!\n";
            return;
        }
        if (health <= 0) {
            cout << name << " telah dikalahkan, tidak bisa menyerang!\n";
            return;
        }   

        cout << name << " menyerang " << target.name << " dengan " << damage << " damage!\n";
        target.takeDamage(damage);
    }

    void takeDamage(int dmg) {
        health -= dmg;
        if (health < 0) health = 0;
        cout << name << " tersisa " << health << " HP.\n";
    }
};

int main() {

    Character mage("Merlin", 100, 5);
    Character assasin("Shadow", 80, 3); 
    Character hero("Arthur", 120, 6);

    while(mage.isAlive() && assasin.isAlive() && hero.isAlive()) {
        mage.status();
        assasin.status();
        hero.status();
        cout << "---------------------------------\n";
        hero.attack(mage);
        mage.attack(assasin);
        assasin.attack(hero);
        cout << "---------------------------------\n";

    }
    cout << "Pertarungan selesai!\n";
    if (!mage.isAlive()) {
        cout << "Merlin telah dikalahkan!\n";
    }
    if (!assasin.isAlive()) {
        cout << "Shadow telah dikalahkan!\n";
    }
    if (!hero.isAlive()) {
        cout << "Arthur telah dikalahkan!\n";
    }
    return 0;
}
