#ifndef ATTACK_H
#define ATTACK_H

#include "task.h"

class Attack : public Task {
    GDCLASS(Attack, Task)

protected:
    static void _bind_methods();

public: 
    Attack();
    ~Attack();

    void run() override; // logic for attacking
};

#endif // ATTACK_H