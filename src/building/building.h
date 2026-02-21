#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <stddef.h>

#include "../other/geometry/direction.h"
#include "../other/geometry/position.h"

struct building
{
    size_t id;
    struct position position;
    enum direction direction;
};

#endif /* ! STRUCTURE_H */
