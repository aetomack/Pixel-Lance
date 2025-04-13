#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "task.h"

class Sequence : public Task {
    GDCLASS(Sequence, Task)

protected:
    static void _bind_methods();

private:
    int current_index = 0;

public:
    Sequence() = default;
    ~Sequence() = default;

    void start();

    void run() override;
    void child_success() override;
    void child_fail() override;
    void child_running() override;
};

#endif // SEQUENCE_H
