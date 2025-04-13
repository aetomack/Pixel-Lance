#include "selector.h"

void Selector::_bind_methods(){}

void Selector::start() {
    Task::start();
    current_index = 0;
}

void Selector::run() {
    if (current_index >= get_child_count()){
        fail();
        return;
    }

    Task* child = Object::cast_to<Task>(get_child(current_index));
    if (child) {
        child->run();
    }
    fail();
}

void Selector::child_success() {
    success();
}

void Selector::child_fail() {
    current_index++;
    fail();
}

void Selector::child_running() {
    running();
}
