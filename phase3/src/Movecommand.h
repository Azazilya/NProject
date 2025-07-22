#ifndef MOVECOMMAND_H
#define MOVECOMMAND_H

#include "Command.h"

class MoveCommand : public Command {
public:
    void execute(Character* target) override {
        if (target) {
            target->move();
            std::cout << target->getName() << " has moved forward!\n";
        } else {
            std::cout << "No target to move!\n";
        }
    }
};