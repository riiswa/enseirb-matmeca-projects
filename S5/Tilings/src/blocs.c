#include "blocs.h"

void filter_authorized_places(unsigned int* n_authorized_places, struct index* authorized_places, unsigned int n_filters, struct index* filters, unsigned int* authorized_places_rotations)
{
    if (!n_filters)
        return;
    int place = 0;
    for (unsigned int i = 0; i < *n_authorized_places; ++i) {
        int valid = 0;
        for (unsigned int j = 0; j < n_filters; ++j)
            valid |= CHECK_ADJACENCE(authorized_places[i].x, authorized_places[i].y, filters[j].x, filters[j].y);
        if (valid) {
            authorized_places[place] = authorized_places[i];
            authorized_places_rotations[place] = authorized_places_rotations[i];
            place++;
        }
    }
    *n_authorized_places = place;
}

int abs(int x)
{
    return x >= 0 ? x : -x;
}