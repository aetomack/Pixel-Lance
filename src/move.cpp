#include "move.h"
#include <godot_cpp/classes/navigation_agent2d.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/character_body2d.hpp>


void Move::_bind_methods(){
    ClassDB::bind_method(D_METHOD("_process", "delta"), &Move::_process);
    ClassDB::bind_method(D_METHOD("run"), &Move::run);
}

void Move::run(){
    // logic for moving enemy to player position
    if (!player && get_tree()) {
        player = Object::cast_to<CharacterBody2D>(get_tree()->get("player"));
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

void Move::_physics_process(double delta) {
    if (get_status() != RUNNING) { return; }
    if (!agent || !player) { return; }
    
    if (agent->is_navigation_finished()) {
        success(); 
        std::printf("Reached Player");
        return;   
    }
    Vector2 next_path_position = agent->get_next_path_position();

    // Get parent that moves (assumes Move is child of Node2D)
    Node2D* actor = Object::cast_to<Node2D>(get_parent());
    if (!actor) {
        fail();
        return;
    }

    // Move parent toward next path position
    Vector2 current_position = actor->get_global_position();
    Vector2 direction = (next_path_position - current_position).normalized();
    Vector2 velocity = direction * SPEED * delta;

    actor->set_global_position(current_position + velocity);
}