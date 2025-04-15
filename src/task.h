#ifndef TASK_H
#define TASK_H

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;
class Task: public Node2D {
    GDCLASS(Task, Node2D)

public:
    enum Status {
        FRESH,
        RUNNING,
        FAILED,
        SUCCEEDED,
        CANCELLED
    };

    Task() = default; 
    virtual ~Task() = default;

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

    //getter mothods
    Object* get_control() { return control; }
    Object* get_tree() { return tree; }
    Status get_status() { return status; }
    
protected:
    static void _bind_methods();

private:
    Object* control = nullptr;
    Object* tree = nullptr;
    Status status = FRESH;
};

VARIANT_ENUM_CAST(Task::Status);

#endif // TASK_H