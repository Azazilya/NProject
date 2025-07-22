#include <iostream>
#include <vector>
#include "Character.h"
#include "Movecommand.h"
#include "Attackcommand.h"
#include "Defendcommand.h"

int main() {
    Character hero("Knight");
    vector<Command*> commandQueue;

    string input;
    cout << "Masukkan perintah (w: move, a: attack, d: defend): ";
    cin >> input;

    for (int i = 0; i < input.size(); ++i) {
        if (input[i] == 'w') commandQueue.push_back(new MoveCommand());
        else if (input[i] == 'a') commandQueue.push_back(new AttackCommand());
        else if (input[i] == 'd') commandQueue.push_back(new DefendCommand());
    }

    for (size_t i = 0; i < commandQueue.size(); ++i)
    {
        commandQueue[i]->execute(&hero);
        delete commandQueue[i];
    }

    return 0;
}
