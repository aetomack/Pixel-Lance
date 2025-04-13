#ifndef RETREAT_H
#define RETREAT_H

#include "task.h"

class Retreat : public Task {
    GDCLASS(Retreat, Task)

protected:
    static void _bind_methods();

public:
    Retreat() = default;
    ~Retreat() = default;

    void run() override;

};

#endif // RETREAT_H
