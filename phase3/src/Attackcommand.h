#ifndef ATTACKCOMMAND_H
#define ATTACKCOMMAND_H

#include "Command.h"

class AttackCommand : public Command {
public:
    void execute(Character* target) override {
        if (target) {
            target->attack();
            std::cout << target->getName() << " has attacked the enemy!\n";
        } else {
            std::cout << "No target to attack!\n";
        }
    }
};