#ifndef SURROUND_H
#define SURROUND_H

#include "task.h"

class Surround : public Task {
    GDCLASS(Surround, Task)

protected:
    static void _bind_methods();

public:
    Surround() = default;
    ~Surround() = default;

    void run() override; // Logic for surrounding
};

#endif // SURROUND_H