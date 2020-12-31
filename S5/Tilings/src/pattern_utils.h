#ifndef _PATTERN_UTILS_H_

#define _PATTERN_UTILS_H_

#define PATTERN_NEIGHBORS_SIZE (2 * MAX_DIRECTION)

#include "board.h"
#include "color.h"
#include "tile.h"

/***************************************************************************/ /**
 * Represents management with 2 seats
 ******************************************************************************/
typedef enum direction_t { N1,
    N2,
    S1,
    S2,
    E1,
    E2,
    W1,
    W2 } direction_t;

/***************************************************************************/ /**
 * Simple boolean
 ******************************************************************************/
typedef enum { false,
    true } bool;

/***************************************************************************/ /**
 * Extraction of the game board with 1 central tile, and 2 tiles in each direction
 ******************************************************************************/
typedef struct board_part {
    const struct tile* base; /**< The central tile */
    const struct tile* neighbors[PATTERN_NEIGHBORS_SIZE]; /**< The 8 neighbors */
} board_part;

/***************************************************************************/ /**
 * A function that takes an extraction from a board and returns a boolean
 ******************************************************************************/
typedef bool (*predicate_t)(board_part*);

/***************************************************************************/ /**
 * Check if all colors are the same
 *
 * @param cs An array of colors
 * @param n The array size
 ******************************************************************************/
bool all_equals(struct color* cs[], int n);

/***************************************************************************/ /**
 * Check if all tiles are empty
 *
 * @param ts An array of tiles
 * @param n The array size
 ******************************************************************************/
bool all_empty(const struct tile* ts[], int n);

/***************************************************************************/ /**
 * Updates contact information in relation to a direction 
 *
 * @param i An direction
 * @param x A pointer to the x-coordinate
 * @param y A pointer to the y-coordinate
 ******************************************************************************/
void update_coords_with_neighbors_i(direction_t i, int* x, int* y);

/***************************************************************************/ /**
 * Update a board_part from the game board and these coordinates
 *
 * @param bp An board_part
 * @param b The game board
 * @param x The x-coordinate
 * @param y The y-coordinate
 ******************************************************************************/
void set_board_part(struct board_part* bp, struct board* b, int x, int y);

#endif
