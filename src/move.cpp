#include "move.h"
#include <godot_cpp/classes/navigation_agent2d.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/character_body2d.hpp>


void Move::_bind_methods(){}

void Move::run(){
    // logic for moving enemy to player position
    if (!player && tree) {
        player = Object::cast_to<CharacterBody2D>(tree->get("player"));
    }

    if (!agent) {
        agent = Object::cast_to<NavigationAgent2D>(get("NavigationAgent2D"));
    }

    if(!agent || !player ) {
        fail();
        std::printf("Failed");
        return;
    }

    agent->set_target_position(player->get_global_position());
    running();
}

void Move::_physics_process(float delta) {
    if (status != RUNNING) { return; }
    if (!agent || !player) { return; }

    Vector2 current_position = agent->get_global_position();
    Vector2 target_position = player->get_global_position();

    if (agent->is_navigation_finished()) {
        success(); 
        std::printf("Reached Player");
        return;   
    }

    Vector2 next_path_position = agent->get_next_path_position();
    Vector2 direction = (next_path_position - current_position).normalized();
    Vector2 velocity = direction * SPEED * delta;

    if (Node2D* node = Object::cast_to<Node2D>(get_parent())) {
        node->set_global_position(current_position + velocity);
    }
}