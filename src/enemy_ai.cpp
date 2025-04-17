#include "enemy_ai.h"
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/core/math.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/engine.hpp>

using namespace godot;

void EnemyAI::_bind_methods() {
    ClassDB::bind_method(D_METHOD("move_toward", "target", "delta", "orbit"), &EnemyAI::move_toward);
    ClassDB::bind_method(D_METHOD("get_random_surround_position"), &EnemyAI::get_random_surround_position);
    ClassDB::bind_method(D_METHOD("animate_attack", "player_position"), &EnemyAI::animate_attack);
    ClassDB::bind_method(D_METHOD("attack_player"), &EnemyAI::attack_player);
    ClassDB::bind_method(D_METHOD("play_run_animation", "to_target"), &EnemyAI::play_run_animation);
}

void EnemyAI::_ready() {
    player = Object::cast_to<CharacterBody2D>(get_node_or_null("../Player"));
    anim = Object::cast_to<AnimatedSprite2D>(get_node_or_null("AnimatedSprite2D"));
    surround_position = get_random_surround_position();

    // Initialize RNG
    rng = std::mt19937(rd());
    attack_dist = std::uniform_real_distribution<double>(0.75, 1.5);
    retreat_dist = std::uniform_real_distribution<double>(1.0, 2.0);

    attack_delay = 3.0;
    attack_elapsed = 0.0;

    // First randomized durations
    attack_duration = attack_dist(rng);
    retreat_time = retreat_dist(rng);
}


void EnemyAI::_physics_process(double delta) {
    if (Engine::get_singleton()->is_editor_hint()) return;

    switch (state) {
        case SURROUND:
            //anim->play("move");
            attack_elapsed += delta;
            if (player) {
                move_toward(player->get_global_position(), delta, true); // orbiting motion
            }

            if (attack_elapsed >= attack_delay) {
                state = ATTACK;
                attack_elapsed = 0.0;
            }
            break;

        case ATTACK:
            attack_elapsed += delta;
            if (player) {
                move_toward(player->get_global_position(), delta, false);
                animate_attack(player->get_global_position());
            }

            if (attack_elapsed >= attack_duration) {
                state = RETREAT;
                retreat_elapsed = 0.0;
                surround_position = get_random_surround_position(); // Pick new target to retreat to
            }
            break;  

        case RETREAT:
            //anim->play("move");
            retreat_elapsed += delta;
            move_toward(surround_position, delta, true); // Go to a proper surround spot
            if (retreat_elapsed >= retreat_time) {
                surround_position = get_random_surround_position();
                state = SURROUND;
                attack_elapsed = 0.0;
                velocity = Vector2();
        
                // Randomize for next cycle
                attack_duration = attack_dist(rng);
                retreat_time = retreat_dist(rng);
            }
            break;
    }
}


void EnemyAI::move_toward(const Vector2& target, double delta, bool orbit = false) {
    Vector2 to_target = target - get_global_position();
    Vector2 direction = to_target.normalized();

    if (orbit) {
        // Get perpendicular direction (to the right of the vector)
        Vector2 perp = Vector2(-direction.y, direction.x);
        // Mix orbit and slight inward pull for nice spiral
        direction = (perp * 0.8f + direction * 0.2f).normalized();
    }

    Vector2 desired_velocity = direction * SPEED;
    Vector2 steering = (desired_velocity - velocity) * static_cast<float>(delta) * 2.5f;
    velocity += steering;
    set_velocity(velocity);
    move_and_slide();
}


Vector2 EnemyAI::get_random_surround_position() {
    Ref<RandomNumberGenerator> rng = memnew(RandomNumberGenerator);
    rng->randomize();

    float radius = 140.0f;
    float angle = rng->randf_range(0.0f, Math_PI * 2.0f);

    Vector2 center = player ? player->get_global_position() : Vector2();
    return center + Vector2(Math::cos(angle), Math::sin(angle)) * radius;
}

void EnemyAI::attack_player() {
    if (!player) return;

    state = ATTACK;

    // Optionally stop movement:
    velocity = Vector2();

    // Play animation based on relative direction
    animate_attack(player->get_global_position());
}

void EnemyAI::animate_attack(const Vector2& player_position) {
    if (!anim || !player) return;

    Vector2 to_player = player_position - get_global_position();
    double distance_to_player = to_player.length();

    if (distance_to_player > ATTACK_RANGE) {
        // Player too far — revert to move animation
        play_run_animation(to_player);
        return;
    }

    // Now we’re definitely in attack range — play attack animation
    if (Math::abs(to_player.x) > Math::abs(to_player.y)) {
        anim->set_flip_h(to_player.x < 0);
        anim->play("attack_right");
    } else {
        anim->set_flip_h(false);
        anim->play(to_player.y > 0 ? "attack_down" : "attack_up");
    }
}

void EnemyAI::play_run_animation(const Vector2& to_target) {

    if (Math::abs(to_target.x) > Math::abs(to_target.y)) {
        anim->set_flip_h(to_target.x < 0);
        anim->play("move");
    } 
}

