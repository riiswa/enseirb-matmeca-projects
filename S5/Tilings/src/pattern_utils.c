#include "pattern_utils.h"
#include "loops.h"
#include <stdio.h>

bool all_equals(struct color* cs[], int n)
{
    while (--n > 0 && cs[n] == cs[0])
        ;
    return n == 0;
}

bool all_empty(const struct tile* ts[], int n)
{
    while (--n > 0 && tile_is_empty(ts[n]))
        ;
    return n == 0;
}

void update_coords_with_neighbors_i(direction_t i, int* x, int* y)
{
    switch (i) {
    case N1:
    case N2:
        (*x)--;
        if (i % 2)
            (*x)--;
        break;
    case S1:
    case S2:
        (*x)++;
        if (i % 2)
            (*x)++;
        break;
    case E1:
    case E2:
        (*y)++;
        if (i % 2)
            (*y)++;
        break;
    case W1:
    case W2:
        (*y)--;
        if (i % 2)
            (*y)--;
        break;
    default:;
    };
}

void set_board_part(struct board_part* bp, struct board* b, int x, int y)
{
    bp->base = board_get(b, x, y);
    for (int i = 0; i < PATTERN_NEIGHBORS_SIZE; i++) {
        int next_x = x;
        int next_y = y;
        update_coords_with_neighbors_i(i, &next_x, &next_y);
        update_coord_with_loops(&next_x, board_size(b));
        update_coord_with_loops(&next_y, board_size(b));
        bp->neighbors[i] = board_get(b, next_x, next_y);
    }
}