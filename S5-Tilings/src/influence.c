#include "influence.h"
#include "adjacencies.h"
#include "loops.h"
#include "symetries.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NEIGHBORS_COUNT 8

#define MIN(x, y) ((x) > (y) ? (y) : (x))

static int eight_neighbors[8][2] = { { -1, -1 }, { -1, 0 }, { -1, +1 }, { 0, -1 }, { 0, +1 }, { +1, -1 }, { +1, 0 }, { +1, +1 } };

void empty_property_level(struct property_level* pl)
{
    memset(pl->values, 0, sizeof(unsigned int) * g_number_players);
    pl->next_value = 90;
}

void update_property_levels(struct board* b, unsigned int x, unsigned int y, int owner)
{
    struct property_level* pl = board_get_property_level(b, x, y);
    pl->values[owner] = 100;

    for (int i = 0; i < NEIGHBORS_COUNT; ++i) {
        int next_x = x + (eight_neighbors[i][0]);
        int next_y = y + (eight_neighbors[i][1]);

        update_coord_with_loops(&next_x, board_size(b));
        update_coord_with_loops(&next_y, board_size(b));
        if (!tile_is_empty(board_get(b, next_x, next_y))) {
            pl = board_get_property_level(b, next_x, next_y);
            pl->values[owner] += (pl->next_value);
            (pl->next_value) -= 10;
        }
    }
}

void get_owners_by_influence(struct board* b, unsigned int x, unsigned int y, struct owners* ows)
{
    struct property_level* pl = board_get_property_level(b, x, y);
    unsigned int max = (pl->values)[0];
    for (unsigned int i = 1; i < g_number_players; ++i)
        if (pl->values[i] > max)
            max = pl->values[i];

    for (unsigned int i = 0; i < g_number_players; ++i) {
        presence p = pl->values[i] == max;
        ows->presences[i] = p;
        ows->n += p;
    }
}

int get_first_owner(struct board* b, unsigned int x, unsigned int y)
{
    struct property_level* pl = board_get_property_level(b, x, y);
    unsigned int max = (pl->values)[0];
    for (unsigned int i = 1; i < g_number_players; ++i)
        if (pl->values[i] > max)
            max = pl->values[i];
    for (unsigned int i = 0; i < g_number_players; ++i) {
        if (pl->values[i] == max)
            return i;
    }
    return board_get_owner(b, x, y);
}

void influence_global_decrement(struct board* b)
{
    int m = board_size(b);
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < m; ++j) {
            struct property_level* pl = board_get_property_level(b, i, j);
            for (unsigned int k = 0; k < g_number_players; ++k)
                if ((pl->values)[k] > 0)
                    --((pl->values)[k]);
        }
}

void print_property_levels(struct board* b)
{
    printf("%d\n", g_number_players);
    for (unsigned int i = 0; i < board_size(b); ++i) {
        for (unsigned int j = 0; j < board_size(b); ++j) {
            printf("[");
            for (int k = 0; k < 5; ++k) {
                printf("%3d ", (board_get_property_level(b, i, j)->values)[k]);
            }
            printf("]");
        }
        printf("\n");
    }
    printf("\n");
}

void decrement_by_50_op(struct board* b, unsigned int x, unsigned int y)
{
    struct property_level* pl = board_get_property_level(b, x, y);
    struct owners ows;
    get_owners_by_influence(b, x, y, &ows);

    for (unsigned int i = 0; i < g_number_players; ++i)
        if (ows.presences[i])
            pl->values[i] -= MIN(50, pl->values[i]);
}

void decrement_by_50(struct board* b, int x, int y, int x_increment, int y_increment, unsigned int cpt)
{
    decrement_by_50_op(b, x, y);
    if (!(!x_increment ? edge_are_adjacent(board_get(b, x, y), change_direction(EAST, board_get_rotation(b, x, y)), change_direction(WEST, board_get_rotation(b, x, y))) : edge_are_adjacent(board_get(b, x, y), change_direction(NORTH, board_get_rotation(b, x, y)), change_direction(SOUTH, board_get_rotation(b, x, y)))))
        return;
    int next_x = x + x_increment;
    int next_y = y + y_increment;
    update_coord_with_loops(&next_x, board_size(b));
    update_coord_with_loops(&next_y, board_size(b));
    if (cpt < board_size(b) && !tile_is_empty(board_get(b, next_x, next_y)))
        decrement_by_50(b, next_x, next_y, x_increment, y_increment, cpt + 1);
}

void the_king_move(struct board* b, struct index* id)
{
    int m = board_size(b);
    id->x = rand() % m;
    id->y = rand() % m;

    const struct tile* t = board_get(b, id->x, id->y);

    if (!tile_is_empty(t)) {
        decrement_by_50_op(b, id->x, id->y);
        for (enum direction d = 0; d < MAX_DIRECTION; d++) {
            int next_x = id->x, next_y = id->y;
            int x_increment = 0;
            int y_increment = 0;

            switch (d) {
            case NORTH:
                x_increment = -1;
                next_x--;
                break;
            case SOUTH:
                x_increment = +1;
                next_x++;
                break;
            case EAST:
                y_increment = +1;
                next_y++;
                break;
            case WEST:
                y_increment = -1;
                next_y--;
                break;
            default:
                break;
            }

            update_coord_with_loops(&next_x, board_size(b));
            update_coord_with_loops(&next_y, board_size(b));
            if (!tile_is_empty(board_get(b, next_x, next_y)))
                decrement_by_50(b, next_x, next_y, x_increment, y_increment, 1);
        }
    }
}