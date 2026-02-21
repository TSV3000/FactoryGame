#ifndef MAP_H
#define MAP_H

#define MAP_HEIGHT 16
#define MAP_WIDTH 16

struct map
{
    struct building **tile;

};

extern struct map map;
void map_create();

#endif /* ! MAP_H */
