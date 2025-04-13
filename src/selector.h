#ifndef SELECTOR_H
#define SELECTOR_H

#include "task.h"

class Selector : public Task {
    GDCLASS(Selector, Task)

protected:
    static void _bind_methods();

private: 
    int current_index = 0;

public:
    Selector() = default;
    ~Selector() = default;

    void start();

    void run() override;
    void child_success() override;
    void child_fail() override;
    void child_running() override;
};


#endif // SELECTOR_H
