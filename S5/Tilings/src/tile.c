#include <stddef.h>
#include <stdlib.h>

#include "colors.h"
#include "globals.h"
#include "tile.h"

#define MAX_TILES 20
#define MAX_COLORS 5

static int deck_is_init = 0;

struct tile {
    struct color* colors[MAX_DIRECTION];
};

static struct tile tiles[MAX_TILES];

const struct tile e_tile = { { NULL, NULL, NULL, NULL } };

const struct tile* empty_tile()
{
    return &e_tile;
}

int tile_is_empty(const struct tile* t)
{
    return tile_equals(t, &e_tile);
}

int tile_equals(const struct tile* t1, const struct tile* t2)
{
    return t1 == t2;
}

struct color* tile_edge(const struct tile* t, enum direction d)
{
    return t->colors[d];
}

struct tile random_tile()
{
    struct tile t;
    for (int i = 0; i < MAX_DIRECTION; i++) {
        t.colors[i] = color_from_name(array_name[rand() % MAX_COLORS]);
    }

    return t;
}

void init_random_tiles()
{
    for (int i = 0; i < MAX_TILES; i++) {
        const struct tile t = random_tile();
        tiles[i] = t;
    }
}

void deck_init(struct deck* d)
{
    // The deck can be initialized only one time
    if (deck_is_init)
        return;

    init_random_tiles();

    d->size = MAX_TILES;

    unsigned int next_value, n_repartition = (MAX_DECK_SIZE + MAX_TILES - 1) / MAX_TILES;
    for (int i = 0, j = 0; j < MAX_TILES; i += n_repartition, j++) {
        next_value = i + n_repartition;
        d->cards[j] = (struct deck_pair){
            &tiles[j],
            next_value > MAX_DECK_SIZE ? next_value - MAX_DECK_SIZE : n_repartition
        };
    }

    deck_is_init = 1;
}
