#include "board.h"
#include "influence.h"
#include "loops.h"
#include "symetries.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#define TILE_CHARACTER ' '
#define RESET_COLOR "\033[0m"
#define REVERSE_COLOR "\033[;7m"
#define KING_CHARACTER 'X'

#define ID_TO_CHAR(id) ((id) > 9 ? 'A' + (id)-10 : '0' + (id))

struct board {
    const struct tile* cells[MAX_BOARD_SIZE];
    int owners[MAX_BOARD_SIZE];
    unsigned int m; // m*m matrix size
    struct property_level property_levels[MAX_BOARD_SIZE];
    unsigned int rotations[MAX_BOARD_SIZE];
};

struct board e_board;

struct board* empty_board(int m)
{
    e_board.m = m;
    const struct tile* t = empty_tile();
    for (int i = 0; i < m * m; i++) {
        e_board.cells[i] = t;
        e_board.rotations[i] = 0;
        empty_property_level(&(e_board.property_levels[i]));
    }
    return &e_board;
}

void check_indices(struct board* b, unsigned int x, unsigned int y)
{
    unsigned int m = b->m;
    if (x >= m && y >= m) {
        fprintf(stderr, "Board Index Out of Bounds! Exiting...\n");
        exit(EXIT_FAILURE);
    }
}

const struct tile* board_get(struct board* b, unsigned int x, unsigned int y)
{
    check_indices(b, x, y);
    return b->cells[COORDS_TO_INT(x, y, b->m)];
}

unsigned int board_get_rotation(struct board* b, unsigned int x, unsigned int y)
{
    check_indices(b, x, y);
    return b->rotations[COORDS_TO_INT(x, y, b->m)];
}

int board_get_owner(struct board* b, unsigned int x, unsigned int y)
{
    check_indices(b, x, y);
    return b->owners[COORDS_TO_INT(x, y, b->m)];
}

struct property_level* board_get_property_level(struct board* b, unsigned int x, unsigned int y)
{
    check_indices(b, x, y);
    return &(b->property_levels[COORDS_TO_INT(x, y, b->m)]);
}

void board_set(struct board* b, unsigned int x, unsigned int y, const struct tile* t)
{
    check_indices(b, x, y);
    b->cells[COORDS_TO_INT(x, y, b->m)] = t;
}

void board_set_rotation(struct board* b, unsigned int x, unsigned int y, unsigned int rotation)
{
    check_indices(b, x, y);
    b->rotations[COORDS_TO_INT(x, y, b->m)] = rotation;
}
void board_set_owner(struct board* b, unsigned int x, unsigned int y, int owner)
{
    check_indices(b, x, y);
    b->owners[COORDS_TO_INT(x, y, b->m)] = owner;
}

int board_cell_is_empty(struct board* b, unsigned int x, unsigned int y)
{
    return tile_is_empty(board_get(b, x, y));
}

unsigned int board_size(struct board* b)
{
    return b->m;
}

void print_tile_level(const struct tile* t, unsigned int level, int owner, unsigned int rotation)
{
    if (tile_is_empty(t)) {
        printf("   ");
        return;
    }

    switch (level) {
    case 0:
        printf(" %s%s%c%s ", REVERSE_COLOR, color_cstring(rotated_tile_edge(t, NORTH, rotation)), TILE_CHARACTER, RESET_COLOR);
        break;
    case 1:
        if (owner != -1)
            printf("%s%s%c%s%c%s%s%c%s", REVERSE_COLOR, color_cstring(rotated_tile_edge(t, WEST, rotation)), TILE_CHARACTER, RESET_COLOR, ID_TO_CHAR(owner),
                REVERSE_COLOR, color_cstring(rotated_tile_edge(t, EAST, rotation)), TILE_CHARACTER, RESET_COLOR);
        else {
            printf("%s%s%c%s%c%s%s%c%s", REVERSE_COLOR, color_cstring(rotated_tile_edge(t, WEST, rotation)), TILE_CHARACTER, RESET_COLOR, KING_CHARACTER,
                REVERSE_COLOR, color_cstring(rotated_tile_edge(t, EAST, rotation)), TILE_CHARACTER, RESET_COLOR);
        }
        break;
    case 2:
        printf(" %s%s%c%s ", REVERSE_COLOR, color_cstring(rotated_tile_edge(t, SOUTH, rotation)), TILE_CHARACTER, RESET_COLOR);
        break;
    default:
        printf("   ");
    }
}

void print_board(struct board* b, int is_king, struct index* king_id)
{
    for (unsigned int i = 0; i < b->m; i++) {
        for (unsigned int k = 0; k < 3; k++) {
            for (unsigned int j = 0; j < b->m; j++)
                if (is_king && king_id->x == i && king_id->y == j)
                    print_tile_level(board_get(b, i, j), k, -1, board_get_rotation(b, i, j));
                else
                    print_tile_level(board_get(b, i, j), k, get_first_owner(b, i, j), board_get_rotation(b, i, j));
            printf("\n");
        }
    }
}

enum direction opposite_direction(enum direction d)
{
    switch (d) {
    case NORTH:
        return SOUTH;
    case SOUTH:
        return NORTH;
    case WEST:
        return EAST;
    case EAST:
        return WEST;
    default:
        return ERROR_DIRECTION;
    }
}

int is_in_bounds(struct board* b, int x, int y)
{
    return x >= 0 && x < (int)b->m && y >= 0 && y < (int)b->m;
}

int check_place(struct board* b, int x, int y, const struct tile* t, unsigned int rotation)
{
    if (!board_cell_is_empty(b, x, y))
        return 0;
    int have_neighbors = 0;
    for (enum direction d = 0; d < MAX_DIRECTION; d++) {
        int next_x = x, next_y = y;

        switch (d) {
        case NORTH:
            next_x--;
            break;
        case SOUTH:
            next_x++;
            break;
        case EAST:
            next_y++;
            break;
        case WEST:
            next_y--;
            break;
        default:
            break;
        }

        update_coord_with_loops(&next_x, board_size(b));
        update_coord_with_loops(&next_y, board_size(b));

        const struct tile* next_t = board_get(b, next_x, next_y);
        if (!tile_is_empty(next_t)) {
            if (rotated_tile_edge(t, d, rotation) != rotated_tile_edge(next_t, opposite_direction(d), board_get_rotation(b, next_x, next_y)))
                return 0;
            have_neighbors = 1;
        }
    }
    return have_neighbors;
}

void list_authorized_places(unsigned int* n_authorized_places, struct index* authorized_places, struct board* b, const struct tile* t, int first_turn, unsigned int* authorized_places_rotations)
{
    int place = 0;
    for (unsigned int i = 0; i < b->m; i++) {
        for (unsigned int j = 0; j < b->m; j++) {
            for (unsigned int o = 0; o < 4; o++)
                if (first_turn || check_place(b, i, j, t, o)) {
                    authorized_places[place] = ((struct index){ i, j });
                    authorized_places_rotations[place] = o;
                    place++;
                    break;
                }
        }
    }
    *n_authorized_places = place;
}
