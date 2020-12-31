#ifndef _CONNECTION_H_

#define _CONNECTION_H_

#include "board.h"
#include "set.h"
#include "tile.h"

/***************************************************************************/ /**
 * Using the flood fill algorithms (https://en.wikipedia.org/wiki/Flood_fill a variant of DFS), awarding points to players according to a connected zone
 *
 * @param b The game board
 * @param x The x-coordinate
 * @param y The y-coordinate
 * @param player_numbers The number of players
 * @param scores The players scores
 ******************************************************************************/
void get_connection_score_at(struct board* b, int x, int y, const int player_numbers, int scores[]);

/***************************************************************************/ /**
 * Free memoty used to detect connection
 ******************************************************************************/
void clear_connection_memory();

#endif