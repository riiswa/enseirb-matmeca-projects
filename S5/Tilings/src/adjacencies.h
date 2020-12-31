#ifndef _ADJACENCIES_H
#define _ADJACENCIES_H
#include "set.h"
#include "tile.h"

typedef struct tile_adjacencies {
    int adjacencies[MAX_DIRECTION][MAX_DIRECTION];
} tile_adjacencies;

typedef struct pair {
    void* key;
    void* value;
} pair;

/***************************************************************************/ /**
 * Give the first element of a pair
 *
 * @param p The pair
 ******************************************************************************/
void* key(void* p);

/***************************************************************************/ /**
 * Check if two directions of a tiles are adjacent
 *
 * @param t The tile
 * @param e1 First direction
 * @param e2 Second direction
 ******************************************************************************/
int edge_are_adjacent(const struct tile* t, enum direction e1, enum direction e2);

/***************************************************************************/ /**
 * Set adjacencies rules for all tiles in deck
 *
 * @param d The deck
 ******************************************************************************/
void init_tiles_adjacencies(struct deck* d);

#endif
