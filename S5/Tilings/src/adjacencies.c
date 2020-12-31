#include "adjacencies.h"
#include <stdio.h>

static set tiles_adjacencies;
static tile_adjacencies tass[MAX_DECK_SIZE];
static pair pairs[MAX_DECK_SIZE];

void* key(void* p)
{
    return ((pair*)p)->key;
}

void init_tiles_adjacencies(struct deck* d)
{
    for (unsigned int i = 0; i < d->size; ++i) {
        pairs[i].key = (struct tile*)d->cards[i].t;
        for (int j = 0; j < MAX_DIRECTION; ++j)
            for (int k = 0; k < MAX_DIRECTION; ++k)
                tass[i].adjacencies[j][k] = j == k ? 1 : (rand() % 100) <= 75;
        pairs[i].value = &(tass[i]);
        set_add(&tiles_adjacencies, &(pairs[i]));
    }
}

int edge_are_adjacent(const struct tile* t, enum direction e1, enum direction e2)
{
    pair tmp = { .key = (struct tile*)t };
    tile_adjacencies* ta = (((pair*)generic_set_find(&tiles_adjacencies, &tmp, &key))->value);
    return ta->adjacencies[e1][e2] && ta->adjacencies[e2][e1];
}

void clear_adjacencies_memory()
{
    clean_set(&tiles_adjacencies);
}
