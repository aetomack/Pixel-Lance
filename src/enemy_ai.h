#ifndef ENEMY_AI_H
#define ENEMY_AI_H

#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/timer.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <random>

using namespace godot;

class EnemyAI : public CharacterBody2D {
    GDCLASS(EnemyAI, CharacterBody2D);

public:
    enum State {
        SURROUND,
        ATTACK,
        RETREAT
    };

protected:
    static void _bind_methods();

public:
    EnemyAI() = default;
    ~EnemyAI() = default;

    void _ready();
    void _physics_process(double delta);

private:
    void move_toward(const Vector2& target, double delta, bool orbit);
    void attack_player();
    void animate_attack(const Vector2& player_position);
    void play_run_animation(const Vector2& to_target);
    Vector2 get_random_surround_position();
    std::random_device rd;
    std::mt19937 rng;
    std::uniform_real_distribution<double> attack_dist;
    std::uniform_real_distribution<double> retreat_dist;

    double attack_delay;
    double retreat_time = 1.5;
    double retreat_elapsed = 0.0;
    double attack_duration = 1.5;
    double attack_elapsed = 0.0;
    const float ATTACK_RANGE = 80.0f; // Distance threshold for continuing the attack
    CharacterBody2D* player = nullptr;
    AnimatedSprite2D* anim = nullptr;

    State state = SURROUND;
    Vector2 surround_position;
    float SPEED = 60.0f;
    float HEALTH = 100.0f;
    Vector2 velocity = Vector2();

};

#endif // ENEMY_AI_H
