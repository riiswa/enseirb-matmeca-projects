#ifndef _PATTERN_H_

#include "pattern_utils.h"

#define _PATTERN_H_

#define MAX_PATTERNS 20

struct pattern; /**< Represents a pattern */

/***************************************************************************/ /**
 * Gives the score of a player at a given place.
 *
 * @param b The game board
 * @param x The x-coordinate
 * @param y The y-coordinate
 * @return The score
 ******************************************************************************/
int get_pattern_score_at(struct board* b, int x, int y);

#endif