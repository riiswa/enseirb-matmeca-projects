#ifndef _SYMETRIES_H
#define _SYMETRIES_H

#include "color.h"
#include "tile.h"

/***************************************************************************/ /**
 * Given a direction updated with a rotation 
 ******************************************************************************/
enum direction change_direction(enum direction d, unsigned int rotation);

/***************************************************************************/ /**
 * A rotated tile 
 * @param t A tile
 * @param d A direction
 * @param rotation The number of rotations
 * @return Color after rotation 
 ******************************************************************************/
struct color* rotated_tile_edge(const struct tile* t, enum direction d, unsigned int rotation);

#endif //_SYMETRIES_H
