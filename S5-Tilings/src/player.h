#ifndef _PLAYER_H_

#include "queue.h"
#include "tile.h"

#define _PLAYER_H_

/***************************************************************************/ /**
 * Randomly deal cards to a player from a deck 
 *
 * @param d The deck
 * @param hand The hand of a player
 ******************************************************************************/
void distribute_deck(struct deck* d, struct queue* hand);

#endif