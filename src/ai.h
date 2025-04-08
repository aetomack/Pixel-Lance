
#ifndef AI_H
#define AI_H

#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/core/class_db.hpp>

namespace godot {
    class Ai : public CharacterBody2D {
        GDCLASS(Ai, CharacterBody2D)

        private:
            enum enemyStatus {
                ATTACK,
                SURROUND, 
                HIT
            };
            double SPEED = 30.0;
            uint32_t random = 0;
            Vector2 velocity = Vector2(0,0);
            CharacterBody2D* player = nullptr;
            enemyStatus state;
            Vector2 target;

        protected:
		    static void _bind_methods();

        public:
            Ai();
            ~Ai();
            void _ready() override;
            void _physics_process(double delta) override;
            void _move(Vector2 target, double delta);
            Vector2 _getCircle(double random, CharacterBody2D* player);
            void _attackTimeout();
    };
}

#endif