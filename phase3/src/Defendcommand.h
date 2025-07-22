#ifndef DEFENDCOMMAND_H
#define DEFENDCOMMAND_H

#include "Command.h"

class DefendCommand : public Command {
public:
    void execute(Character* target) override {
        if (target) {
            target->defend();
            std::cout << target->getName() << " has defended!\n";
        } else {
            std::cout << "No target to defend!\n";
        }
    }
};