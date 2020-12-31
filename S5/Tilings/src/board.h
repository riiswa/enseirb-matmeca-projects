#ifndef _BOARD_H_

#define _BOARD_H_

#include "tile.h"

#define MAX_DIMENSION 50

#define MAX_BOARD_SIZE (MAX_DIMENSION * MAX_DIMENSION)

#define MAX_PLAYERS 20

#define COORDS_TO_INT(x, y, m) ((x) + (y) * (m))

/***************************************************************************/ /**
 * The game board
 ******************************************************************************/
struct board;

/***************************************************************************/ /**
 * The indices in a game board
 ******************************************************************************/
struct index {
    unsigned int x; /**< The x-coordinates */
    unsigned int y; /**< The y-coordinates */
};

/***************************************************************************/ /**
 * Initialize the board
 *
 * @param m The board size (m*m)
 * @return pointer to the board (There is only one instance of board)
 ******************************************************************************/
struct board* empty_board(int m);

/***************************************************************************/ /**
 * Get the tile with its coordinates
 *
 * @param b The game board
 * @param x The x-coordinate
 * @param y The y-coordinate
 * @return The tile
 ******************************************************************************/
const struct tile* board_get(struct board* b, unsigned int x, unsigned int y);

struct board* empty_board(int m);

/***************************************************************************/ /**
 * Get the owner of a tile with its coordinates
 *
 * @param b The game board
 * @param x The x-coordinate
 * @param y The y-coordinate
 * @return The owner of a tile
 ******************************************************************************/
int board_get_owner(struct board* b, unsigned int x, unsigned int y);

unsigned int board_get_rotation(struct board* b, unsigned int x, unsigned int y);

struct property_level* board_get_property_level(struct board* b, unsigned int x, unsigned int y);

struct board* empty_board(int m);

/***************************************************************************/ /**
 * Set the tile with its coordinates
 *
 * @param b The game board
 * @param x The x-coordinate
 * @param y The y-coordinate
 * @param t The tile to set
 ******************************************************************************/
void board_set(struct board* b, unsigned int x, unsigned int y, const struct tile* t);

void board_set_rotation(struct board* b, unsigned int x, unsigned int y, unsigned int rotation);

/***************************************************************************/ /**
 * Set the owner of a tile with its coordinates
 *
 * @param b The game board
 * @param x The x-coordinate
 * @param y The y-coordinate
 * @param owner The id of owner
 ******************************************************************************/
void board_set_owner(struct board* b, unsigned int x, unsigned int y, int owner);

/***************************************************************************/ /**
 * Check if a place is empty
 *
 * @param b The game board
 * @param x The x-coordinate
 * @param y The y-coordinate
 ******************************************************************************/
int board_cell_is_empty(struct board* b, unsigned int x, unsigned int y);

/***************************************************************************/ /**
 * Get the size of the board
 *
 * @param b The game board
 ******************************************************************************/
unsigned int board_size(struct board* b);

/***************************************************************************/ /**
 * Pretty display the board in the terminal
 *
 * @param b The game board
 ******************************************************************************/
void print_board(struct board* b, int is_king, struct index* king_id);

/***************************************************************************/ /**
 * Update the list of authorized places for a given coodinates
 *
 * @param n_authorized_places Number of authorized places
 * @param authorized_places List of authorized places
 * @param b The game board
 * @param t The tile to set
 * @param first_turn If it's the first round the algorithm will not check that the tile is related to another one
 ******************************************************************************/
void list_authorized_places(unsigned int* n_authorized_places, struct index* authorized_places, struct board* b, const struct tile* t, int first_turn, unsigned int* authorized_places_rotations);

/***************************************************************************/ /**
 * Check if coordinates is in the bounds of a board
 *
 * @param b The game board
 * @param x The x-coordinate
 * @param y The y-coordinate
 ******************************************************************************/
int is_in_bounds(struct board* b, int x, int y);

/***************************************************************************/ /**
 * Given a direction, returns the opposite direction (Exemple: North -> South)
 *
 * @param d The direction
 * @return The opposite direction
 ******************************************************************************/
enum direction opposite_direction(enum direction d);

#endif
