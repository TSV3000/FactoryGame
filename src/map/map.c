#include "map.h"

#include <stdlib.h>

#include "../other/geometry/position.h"

struct map map;

void map_create()
{
    map.tile = calloc(MAP_WIDTH * MAP_HEIGHT,
        sizeof(struct building *));
}

struct building *map_get_building(struct position position)
{
    return map.tile[position.x + position.y * MAP_WIDTH];
}
