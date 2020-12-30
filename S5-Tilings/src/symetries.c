#include "symetries.h"
#include <stdio.h>
enum direction change_direction(enum direction d, unsigned int rotation)
{
    if (!rotation)
        return d;
    switch (d) {
    case NORTH:
        return change_direction(EAST, rotation - 1);
    case SOUTH:
        return change_direction(WEST, rotation - 1);
    case EAST:
        return change_direction(SOUTH, rotation - 1);
    case WEST:
        return change_direction(NORTH, rotation - 1);
    default:
        return d;
    }
}

struct color* rotated_tile_edge(const struct tile* t, enum direction d, unsigned int rotation)
{

    return tile_edge(t, change_direction(d, rotation));
}
