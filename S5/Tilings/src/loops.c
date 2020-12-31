#include "loops.h"

void update_coord_with_loops(int* z, const int limit)
{
    if (*z < 0)
        *z = limit + (*z);
    else if (*z >= limit)
        *z = (*z) % limit;
}