#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <ai.h>
#include <stdint.h>

using namespace godot;

void Ai::_bind_methods() {
    ClassDB::bind_method(D_METHOD("_move", "target", "delta"), &Ai::_move);
    ClassDB::bind_method(D_METHOD("_getCircle", "random", "player"), &Ai::_getCircle);
    ClassDB::bind_method(D_METHOD("_attackTimeout"), &Ai::_attackTimeout);
}


Ai::Ai(){}

Ai::~Ai(){}

void Ai::_ready() {
    state = SURROUND;
    Node* node = get_node_or_null(NodePath("/root/Root/Player"));
    player = Object::cast_to<CharacterBody2D>(node);

    if (player) {
        random = rand() % 100;
        target = _getCircle(random, player);
    } else {
        UtilityFunctions::print("⚠️ Player not found. Skipping AI setup.");
    }
}
void Ai::_physics_process(double delta) {
    if(!player) return;
    if(state==SURROUND) {
        // Move to target
        _move(_getCircle(random, player), delta);
    }

    if(state==ATTACK) {
        _move(player->get_global_position(), delta);
    }

    if(state==HIT) {
        _move(player->get_global_position(), delta);
    }

}

void Ai::_move(Vector2 target, double delta) {
    Vector2 direction = (target - get_global_position()).normalized();
    Vector2 desired_velocity = direction * SPEED;
    Vector2 steering = (desired_velocity - velocity) * delta * 2.5;
    velocity += steering;
    move_and_slide();
}

Vector2 Ai::_getCircle(double random, CharacterBody2D* player) {
    Vector2 center = player->get_global_position();
    float angle = random / 100.0 * Math_TAU; 
    float radius = 40.0f;
    return Vector2(center.x + Math::cos(angle) * radius, center.y + Math::sin(angle) * radius);
}

void Ai::_attackTimeout() {

}


