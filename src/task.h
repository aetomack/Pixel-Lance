#ifndef TASK_H
#define TASK_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;
class Task: public Node {
    GDCLASS(Task, Node)

public:
    enum Status {
        FRESH,
        RUNNING,
        FAILED,
        SUCCEEDED,
        CANCELLED
    };

    Task(); 
    ~Task();

    // Lifecycle control methods
    void running();
    void success();
    void fail();
    void cancel();

    // Abstract Methods
    virtual void run();
    virtual void child_success();
    virtual void child_fail();
    virtual void child_running();

    // Concrete non-final Methods
    void start();
    void reset();

    // Setters for control/tree
    void set_control(Object* p_control) { control = p_control; }
    void set_tree(Object* p_tree) { tree = p_tree; }

private:      
    Object* control = nullptr;
    Object* tree = nullptr;
    Status status = FRESH;

protected:
    static void _bind_methods();

};

#endif