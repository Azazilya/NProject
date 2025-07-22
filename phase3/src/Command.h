#ifndef COMMAND_H
#define COMMAND_H

#include "Character.h"

class Command {
public:
    virtual void execute(Character* target) = 0;
    virtual ~Command() {}
};

#endif
