#include "attack.h"

void Attack::_bind_methods(){
    ClassDB::bind_method(D_METHOD("run"), &Attack::run);
}

void Attack::run(){
    // logic for attack
}