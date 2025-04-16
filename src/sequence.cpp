#include "sequence.h"
#include <stdlib.h>

void Sequence::_bind_methods() {
    ClassDB::bind_method(D_METHOD("start"), &Sequence::start);
    ClassDB::bind_method(D_METHOD("run"), &Sequence::run);
    ClassDB::bind_method(D_METHOD("child_success"), &Sequence::child_success);
    ClassDB::bind_method(D_METHOD("child_fail"), &Sequence::child_fail);
    ClassDB::bind_method(D_METHOD("child_running"), &Sequence::child_running);
}

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