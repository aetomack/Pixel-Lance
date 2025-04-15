#ifndef MOVE_H
#define MOVE_H

#include "task.h"

class Move : public Task {
    GDCLASS(Move, Task)

protected:
    static void _bind_methods();

private: 
    double SPEED = 200.0;
    Node2D* PLAYER = nullptr;
    class NavigationAgent2D* agent = nullptr;

public:
    Move() = default;
    ~Move() = default;

    void run() override;
    void _physics_process(float delta);
};

#endif // MOVE_H