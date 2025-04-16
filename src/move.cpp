#include "move.h"
#include "task.h"

#include <godot_cpp/classes/navigation_agent2d.hpp>
#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void Move::_bind_methods() {
    ClassDB::bind_method(D_METHOD("run"), &Move::run);
}

void Move::run() {
    std::printf("Move::run");
    Object* tree = get_tree();

    if (!player && tree) {
        player = Object::cast_to<CharacterBody2D>(tree->get("player"));
    }

    if (!agent) {
        agent = Object::cast_to<NavigationAgent2D>(get_node<NavigationAgent2D>("NavigationAgent2D"));
    }

    if (!agent || !player) {
        fail();
        std::printf("Move task failed: missing agent or player.\n");
        return;
    }

    agent->set_target_position(player->get_global_position());
    running();
}

void Move::_physics_process(double delta) {
    std::printf("Move::_physics_process");
    Status status = get_status();
    if (status != RUNNING) return;
    if (!agent || !player) return;

    if (agent->is_navigation_finished()) {
        success();
        std::printf("Move task succeeded: reached player.\n");
        return;
    }

    CharacterBody2D* actor = Object::cast_to<CharacterBody2D>(get_parent());
    if (!actor) {
        fail();
        std::printf("Move task failed: parent is not CharacterBody2D.\n");
        return;
    }

    Vector2 next_position = agent->get_next_path_position();
    Vector2 direction = (next_position - actor->get_global_position()).normalized();
    Vector2 velocity = direction * speed;
    actor->set_velocity(velocity);
    actor->move_and_slide();
}
