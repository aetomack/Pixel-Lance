#ifndef MOVE_H
#define MOVE_H

#include "task.h"
#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/navigation_agent2d.hpp>


class Move : public Task {
    GDCLASS(Move, Task)

protected:
    static void _bind_methods();

private: 
    double SPEED = 200.0;
    CharacterBody2D* player = nullptr;
    NavigationAgent2D* agent = nullptr;

public:
    Move() = default;
    ~Move() = default;

    void run() override;
    void _physics_process(double delta);
};

#endif // MOVE_H