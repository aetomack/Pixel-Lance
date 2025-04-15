#include "sequence.h"

void Sequence::_bind_methods() {}

void Sequence::start() {
    Task::start();
    current_index = 0;
}

void Sequence::run() {
    if (current_index >= get_child_count()) {
        success();
        return;
    }

    Task* child = Object::cast_to<Task>(get_child(current_index));
    if (child) {
        child->run();
    }
    fail();
}

void Sequence::child_success(){
    current_index++;
    run();
}

void Sequence::child_fail() {
    fail();
}

void Sequence::child_running() {
    running();
}