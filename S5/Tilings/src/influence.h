#ifndef _INFLUENCE_H_

#define _INFLUENCE_H_

#include "board.h"
#include "globals.h"
#include "tile.h"

unsigned int g_number_players;

/***************************************************************************/ /**
 * Proprety level on a Tile
 ******************************************************************************/
struct property_level {
    unsigned int values[MAX_PLAYERS];
    unsigned int next_value;
};

/***************************************************************************/ /**
 * Presence of a player over a  tile
 ******************************************************************************/
typedef enum presence { HERE,
    ABSENT } presence;
/***************************************************************************/ /**
 * 
 ******************************************************************************/
struct owners {
    presence presences[MAX_PLAYERS];
    int n;
};
/***************************************************************************/ /**
 * An emtpy proprety level struct on a tile
 ******************************************************************************/
void empty_property_level(struct property_level* pl);
/***************************************************************************/ /**
 * Get the proprety level over a tile with its coordinates
 * @param b the board
 * @param x the abscissa
 * @param y the ordinate
 * @return the new proprety level
 ******************************************************************************/
struct property_level* board_get_property_level(struct board* b, unsigned int x, unsigned int y);
/***************************************************************************/ /**
 * Update the proprety levels of a tile with its coordinates
 * @param b the board
 * @param x the abscissa
 * @param y the ordinate
 * @param owner the new proprety level 
 ******************************************************************************/
void update_property_levels(struct board* b, unsigned int x, unsigned int y, int owner);

//void print_property_levels(struct board* b);
/***************************************************************************/ /**
 * Get the owner of a tile with its coordonate and its onfluence by the players
 * @param b the board
 * @param x the abscissa
 * @param y the ordinate
 * @param owns the proprety level 
 ******************************************************************************/
void get_owners_by_influence(struct board* b, unsigned int x, unsigned int y, struct owners* ows);
/***************************************************************************/ /**
 * Get the principal owner of a tile thanks to its coordinates
 * @param b the board
 * @param x the abscissa
 * @param y the ordinate
 * @return the number of the owner (player)
 ******************************************************************************/
int get_first_owner(struct board* b, unsigned int x, unsigned int y);
/***************************************************************************/ /**
 * 
 * @param b the board
 *
 ******************************************************************************/
void influence_global_decrement(struct board* b);
/***************************************************************************/ /**
 * 
 * @param b the board
 * @param id the index
 ******************************************************************************/
void the_king_move(struct board* b, struct index* id);

#endif //_INFLUENCES_H_