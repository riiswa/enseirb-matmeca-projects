#ifndef _BLOCS_H
#define _BLOCS_H
#include "board.h"

/***************************************************************************/ /**
 * Macro to chek if two coords are adjancent
 ******************************************************************************/
#define CHECK_ADJACENCE(x1, y1, x2, y2) (abs((x1) - (x2)) <= 1 && abs((y1) - (y2)) <= 1)

/***************************************************************************/ /**
 * Return the absolute value of the x interger.
 ******************************************************************************/
int abs(int x);

/***************************************************************************/ /**
 * Filter (update) a list of authorized place according to an index list where the authorized places must be adjacent to the filters.
 *
 * @param n_authorized_places Number of authorized places
 * @param authorized_places The authorized places
 * @param n_filters Number of filter
 * @param filters The filters
 * @param authorized_places_rotations Rotations according to authorized places
 ******************************************************************************/
void filter_authorized_places(unsigned int* n_authorized_places, struct index* authorized_places, unsigned int n_filters, struct index* filters, unsigned int* authorized_places_rotations);

#endif
