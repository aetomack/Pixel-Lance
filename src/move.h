#ifndef MOVE_H
#define MOVE_H

#include "task.h"

class Move : public Task {
    GDCLASS(Move, Task)

protected:
    static void _bind_methods();

public:
    Move() = default;
    ~Move() = default;

    void run() override;
};

#endif // MOVE_H