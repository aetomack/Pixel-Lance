#include "retreat.h"

void Retreat::_bind_methods(){
    ClassDB::bind_method(D_METHOD("run"), &Retreat::run);
}

void Retreat::run() {
    // logic to retreat
}