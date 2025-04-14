#include "task.h"

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/node2d.hpp>


using namespace godot;

void Task::_bind_methods() {
    ClassDB::bind_method(D_METHOD("start"), &Task::start);
    ClassDB::bind_method(D_METHOD("reset"), &Task::reset);
    ClassDB::bind_method(D_METHOD("run"), &Task::run);
    ClassDB::bind_method(D_METHOD("cancel"), &Task::cancel);
    ClassDB::bind_method(D_METHOD("child_success"), &Task::child_success);
    ClassDB::bind_method(D_METHOD("child_fail"), &Task::child_fail);
    ClassDB::bind_method(D_METHOD("child_running"), &Task::child_running);

    BIND_ENUM_CONSTANT(FRESH);
    BIND_ENUM_CONSTANT(RUNNING);
    BIND_ENUM_CONSTANT(FAILED);
    BIND_ENUM_CONSTANT(SUCCEEDED);
    BIND_ENUM_CONSTANT(CANCELLED);
}

void Task::running() {
    status = RUNNING;
    if (control) {
        Variant ret;
        control -> call("child_running");
    }
}

void Task::success() {
    status = SUCCEEDED;
    if (control) {
        control -> call("child_success");
    }
}

void Task::fail() {
    status = FAILED;
    if (control) {
        control -> call("child_fail");
    }
}

void Task::cancel() {
    if (status==RUNNING) {
        status = CANCELLED;

        for (int i = 0; i <get_child_count(); ++i) {
            Node* child = Object::cast_to<Node>(get_child(i));
            if (child) {
                Variant ret;
                child -> call("cancel");
            }
        }
    }
}

void Task::run(){
    // overriden in subclass
}

void Task::child_success() {
    success();
}

void Task::child_fail() {
    fail();
}

void Task::child_running() {
    running();
}

void Task::start(){
    status = FRESH;

    for(int i = 0; i < get_child_count(); ++i) {
        Task* child = Object::cast_to<Task>(get_child(i));
        if (child) {
            child->set_control(this);
            child->set_tree(tree);
            child->start();
        }
    }
}

void Task::reset(){
    cancel();
    status = FRESH;
}