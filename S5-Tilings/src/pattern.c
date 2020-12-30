#include "pattern.h"

#include <stdio.h>
#include <stdlib.h>

#define PATTERN_NUMBER 21

typedef struct pattern {
    predicate_t predicate;
    char score;
} pattern;

bool universal_pattern(board_part* bp)
{
    return tile_is_empty(bp->base) ? false : true;
}

bool short_vertical_line_pattern(board_part* bp)
{
    const struct tile* ts[] = { bp->base, bp->neighbors[N1], bp->neighbors[S1] };

    if (!all_empty(ts, 3)) {
        struct color* cs[] = { tile_edge(bp->base, NORTH), tile_edge(bp->base, SOUTH), tile_edge(bp->neighbors[N1], SOUTH), tile_edge(bp->neighbors[S1], NORTH) };
        return all_equals(cs, 4);
    }
    return false;
}

bool short_horizontal_line_pattern(board_part* bp)
{
    const struct tile* ts[] = { bp->base, bp->neighbors[E1], bp->neighbors[W1] };
    if (!all_empty(ts, 3)) {
        struct color* cs[] = { tile_edge(bp->base, EAST), tile_edge(bp->base, WEST), tile_edge(bp->neighbors[E1], WEST), tile_edge(bp->neighbors[W1], EAST) };
        return all_equals(cs, 4);
    }
    return false;
}

bool short_horizontal_alternation(board_part* bp)
{
    const struct tile* ts[] = { bp->base, bp->neighbors[E1], bp->neighbors[W1] };
    if (!all_empty(ts, 3)) {
        struct color* cs1[] = { tile_edge(bp->base, EAST), tile_edge(bp->base, WEST) };
        struct color* cs2[] = { tile_edge(bp->neighbors[E1], WEST), tile_edge(bp->neighbors[W1], EAST) };
        return all_equals(cs1, 2) && all_equals(cs2, 2);
    }

    return false;
}

bool short_vertical_alternation(board_part* bp)
{
    const struct tile* ts[] = { bp->base, bp->neighbors[S1], bp->neighbors[N1] };
    if (!all_empty(ts, 3)) {
        struct color* cs1[] = { tile_edge(bp->base, NORTH), tile_edge(bp->base, SOUTH) };
        struct color* cs2[] = { tile_edge(bp->neighbors[S1], NORTH), tile_edge(bp->neighbors[N1], SOUTH) };
        return all_equals(cs1, 2) && all_equals(cs2, 2);
    }

    return false;
}
bool vertical_alternation(board_part* bp)
{
    const struct tile* ts[] = { bp->base, bp->neighbors[N1], bp->neighbors[N2], bp->neighbors[S1], bp->neighbors[S2] };
    if (!all_empty(ts, 5)) {
        struct color* cs1[] = { tile_edge(bp->base, NORTH), tile_edge(bp->neighbors[N1], NORTH), tile_edge(bp->neighbors[N2], NORTH), tile_edge(bp->neighbors[S1], NORTH), tile_edge(bp->neighbors[S2], NORTH) };
        struct color* cs2[] = { tile_edge(bp->base, SOUTH), tile_edge(bp->neighbors[N1], SOUTH), tile_edge(bp->neighbors[N2], SOUTH), tile_edge(bp->neighbors[S1], SOUTH), tile_edge(bp->neighbors[S2], SOUTH) };
        return all_equals(cs1, 5) && all_equals(cs2, 5);
    }
    return false;
}

bool horizontal_alternation(board_part* bp)
{
    const struct tile* ts[] = { bp->base, bp->neighbors[W1], bp->neighbors[W2], bp->neighbors[E1], bp->neighbors[E2] };
    if (!all_empty(ts, 5)) {
        struct color* cs1[] = { tile_edge(bp->base, WEST), tile_edge(bp->neighbors[W1], WEST), tile_edge(bp->neighbors[W2], WEST), tile_edge(bp->neighbors[E1], WEST), tile_edge(bp->neighbors[E2], WEST) };
        struct color* cs2[] = { tile_edge(bp->base, EAST), tile_edge(bp->neighbors[W1], EAST), tile_edge(bp->neighbors[W2], EAST), tile_edge(bp->neighbors[E1], EAST), tile_edge(bp->neighbors[E2], EAST) };
        return all_equals(cs1, 5) && all_equals(cs2, 5);
    }
    return false;
}

bool small_square_alternation(board_part* bp)
{

    const struct tile* ts[] = { bp->base, bp->neighbors[W1], bp->neighbors[N1], bp->neighbors[E1], bp->neighbors[S1] };
    if (!all_empty(ts, 5)) {
        struct color* cs1[] = { tile_edge(bp->base, NORTH), tile_edge(bp->base, EAST), tile_edge(bp->base, SOUTH), tile_edge(bp->base, WEST) };
        struct color* cs2[] = { tile_edge(bp->neighbors[W1], NORTH), tile_edge(bp->neighbors[W1], SOUTH), tile_edge(bp->neighbors[W1], EAST), tile_edge(bp->neighbors[W1], WEST), tile_edge(bp->neighbors[E1], NORTH), tile_edge(bp->neighbors[E1], SOUTH), tile_edge(bp->neighbors[E1], EAST), tile_edge(bp->neighbors[E1], WEST), tile_edge(bp->neighbors[N1], NORTH), tile_edge(bp->neighbors[N1], SOUTH), tile_edge(bp->neighbors[N1], EAST), tile_edge(bp->neighbors[N1], WEST), tile_edge(bp->neighbors[S1], NORTH), tile_edge(bp->neighbors[S1], SOUTH), tile_edge(bp->neighbors[S1], EAST), tile_edge(bp->neighbors[E1], WEST) };
        return all_equals(cs1, 4) && all_equals(cs2, 16);
    }
    return false;
}

bool three_squares_horizontal_alike(board_part* bp)
{

    const struct tile* ts[] = { bp->base, bp->neighbors[W1], bp->neighbors[W2], bp->neighbors[E1], bp->neighbors[E2] };
    if (!all_empty(ts, 5)) {
        struct color* cs1[] = { tile_edge(bp->base, NORTH), tile_edge(bp->base, EAST), tile_edge(bp->base, SOUTH), tile_edge(bp->base, WEST) };
        struct color* cs2[] = { tile_edge(bp->neighbors[W1], NORTH), tile_edge(bp->neighbors[W1], EAST), tile_edge(bp->neighbors[W1], SOUTH), tile_edge(bp->neighbors[W1], WEST) };
        struct color* cs3[] = { tile_edge(bp->neighbors[E1], NORTH), tile_edge(bp->neighbors[E1], EAST), tile_edge(bp->neighbors[E1], SOUTH), tile_edge(bp->neighbors[E1], WEST) };
        struct color* cs4[] = { tile_edge(bp->neighbors[W2], NORTH), tile_edge(bp->neighbors[W2], EAST), tile_edge(bp->neighbors[W2], SOUTH), tile_edge(bp->neighbors[W2], WEST) };
        struct color* cs5[] = { tile_edge(bp->neighbors[E2], NORTH), tile_edge(bp->neighbors[E2], EAST), tile_edge(bp->neighbors[E2], SOUTH), tile_edge(bp->neighbors[E2], WEST) };
        if ((all_equals(cs1, 4) && all_equals(cs2, 4) && all_equals(cs4, 4)) || (all_equals(cs1, 4) && all_equals(cs3, 4) && all_equals(cs5, 4)))
            return true;
    }
    return false;
}

bool three_squares_vertical_alike(board_part* bp)
{

    const struct tile* ts[] = { bp->base, bp->neighbors[N1], bp->neighbors[N2], bp->neighbors[S1], bp->neighbors[S2] };
    if (!all_empty(ts, 5)) {
        struct color* cs1[] = { tile_edge(bp->base, NORTH), tile_edge(bp->base, EAST), tile_edge(bp->base, SOUTH), tile_edge(bp->base, WEST) };
        struct color* cs2[] = { tile_edge(bp->neighbors[N1], NORTH), tile_edge(bp->neighbors[N1], EAST), tile_edge(bp->neighbors[N1], SOUTH), tile_edge(bp->neighbors[N1], WEST) };
        struct color* cs3[] = { tile_edge(bp->neighbors[S1], NORTH), tile_edge(bp->neighbors[S1], EAST), tile_edge(bp->neighbors[S1], SOUTH), tile_edge(bp->neighbors[S1], WEST) };
        struct color* cs4[] = { tile_edge(bp->neighbors[N2], NORTH), tile_edge(bp->neighbors[N2], EAST), tile_edge(bp->neighbors[N2], SOUTH), tile_edge(bp->neighbors[N2], WEST) };
        struct color* cs5[] = { tile_edge(bp->neighbors[S2], NORTH), tile_edge(bp->neighbors[S2], EAST), tile_edge(bp->neighbors[S2], SOUTH), tile_edge(bp->neighbors[S2], WEST) };
        if ((all_equals(cs1, 4) && all_equals(cs2, 4) && all_equals(cs4, 4)) || (all_equals(cs1, 4) && all_equals(cs3, 4) && all_equals(cs5, 4)))
            return true;
    }
    return false;
}

bool four_squares_horizontal_alike(board_part* bp)
{

    const struct tile* ts[] = { bp->base, bp->neighbors[W1], bp->neighbors[W2], bp->neighbors[E1], bp->neighbors[E2] };
    if (!all_empty(ts, 5)) {
        struct color* cs1[] = { tile_edge(bp->base, NORTH), tile_edge(bp->base, EAST), tile_edge(bp->base, SOUTH), tile_edge(bp->base, WEST) };
        struct color* cs2[] = { tile_edge(bp->neighbors[W1], NORTH), tile_edge(bp->neighbors[W1], EAST), tile_edge(bp->neighbors[W1], SOUTH), tile_edge(bp->neighbors[W1], WEST) };
        struct color* cs3[] = { tile_edge(bp->neighbors[E1], NORTH), tile_edge(bp->neighbors[E1], EAST), tile_edge(bp->neighbors[E1], SOUTH), tile_edge(bp->neighbors[E1], WEST) };
        struct color* cs4[] = { tile_edge(bp->neighbors[W2], NORTH), tile_edge(bp->neighbors[W2], EAST), tile_edge(bp->neighbors[W2], SOUTH), tile_edge(bp->neighbors[W2], WEST) };
        struct color* cs5[] = { tile_edge(bp->neighbors[E2], NORTH), tile_edge(bp->neighbors[E2], EAST), tile_edge(bp->neighbors[E2], SOUTH), tile_edge(bp->neighbors[E2], WEST) };
        if ((all_equals(cs1, 4) && all_equals(cs2, 4) && all_equals(cs4, 4) && all_equals(cs3, 4)) || ((all_equals(cs1, 4) && all_equals(cs3, 4) && all_equals(cs5, 4)) && all_equals(cs2, 4)))
            return true;
    }
    return false;
}

bool four_squares_vertical_alike(board_part* bp)
{

    const struct tile* ts[] = { bp->base, bp->neighbors[W1], bp->neighbors[W2], bp->neighbors[E1], bp->neighbors[E2] };
    if (!all_empty(ts, 5)) {
        struct color* cs1[] = { tile_edge(bp->base, NORTH), tile_edge(bp->base, EAST), tile_edge(bp->base, SOUTH), tile_edge(bp->base, WEST) };
        struct color* cs2[] = { tile_edge(bp->neighbors[N1], NORTH), tile_edge(bp->neighbors[N1], EAST), tile_edge(bp->neighbors[N1], SOUTH), tile_edge(bp->neighbors[N1], WEST) };
        struct color* cs3[] = { tile_edge(bp->neighbors[S1], NORTH), tile_edge(bp->neighbors[S1], EAST), tile_edge(bp->neighbors[S1], SOUTH), tile_edge(bp->neighbors[S1], WEST) };
        struct color* cs4[] = { tile_edge(bp->neighbors[N2], NORTH), tile_edge(bp->neighbors[N2], EAST), tile_edge(bp->neighbors[N2], SOUTH), tile_edge(bp->neighbors[N2], WEST) };
        struct color* cs5[] = { tile_edge(bp->neighbors[S2], NORTH), tile_edge(bp->neighbors[S2], EAST), tile_edge(bp->neighbors[S2], SOUTH), tile_edge(bp->neighbors[S2], WEST) };
        if ((all_equals(cs1, 4) && all_equals(cs2, 4) && all_equals(cs4, 4) && all_equals(cs3, 4)) || ((all_equals(cs1, 4) && all_equals(cs3, 4) && all_equals(cs5, 4)) && all_equals(cs2, 4)))
            return true;
    }
    return false;
}

bool small_diamond(board_part* bp)
{

    const struct tile* ts[] = { bp->base, bp->neighbors[W1], bp->neighbors[W2], bp->neighbors[E1], bp->neighbors[E2] };
    if (!all_empty(ts, 5)) {
        struct color* cs1[] = { tile_edge(bp->base, NORTH), tile_edge(bp->base, EAST), tile_edge(bp->base, SOUTH), tile_edge(bp->base, WEST) };
        struct color* cs2[] = { tile_edge(bp->neighbors[N1], SOUTH), tile_edge(bp->neighbors[W1], EAST), tile_edge(bp->neighbors[S1], NORTH), tile_edge(bp->neighbors[E1], WEST) };
        return all_equals(cs1, 4) && all_equals(cs2, 4);
    }
    return false;
}

bool up_right_diagonal_line(board_part* bp)
{

    const struct tile* ts[] = { bp->base, bp->neighbors[E1], bp->neighbors[N1] };
    if (!all_empty(ts, 3)) {
        struct color* cs[] = {
            tile_edge(bp->base, NORTH),
            tile_edge(bp->base, EAST),
            tile_edge(bp->neighbors[E1], WEST),
            tile_edge(bp->neighbors[E1], NORTH),
            tile_edge(bp->neighbors[N1], SOUTH),
            tile_edge(bp->neighbors[N1], EAST),
        };
        return all_equals(cs, 6);
    }

    return false;
}

bool up_left_diagonal_line(board_part* bp)
{

    const struct tile* ts[] = { bp->base, bp->neighbors[W1], bp->neighbors[N1] };
    if (!all_empty(ts, 3)) {
        struct color* cs[] = { tile_edge(bp->base, NORTH), tile_edge(bp->base, WEST), tile_edge(bp->neighbors[W1], EAST), tile_edge(bp->neighbors[W1], SOUTH), tile_edge(bp->neighbors[N1], SOUTH), tile_edge(bp->neighbors[N1], EAST) };
        return all_equals(cs, 6);
    }

    return false;
}

bool down_right_diagonal_line(board_part* bp)
{

    const struct tile* ts[] = { bp->base, bp->neighbors[E1], bp->neighbors[S1] };
    if (!all_empty(ts, 3)) {
        struct color* cs[] = { tile_edge(bp->base, SOUTH), tile_edge(bp->base, EAST), tile_edge(bp->neighbors[E1], WEST), tile_edge(bp->neighbors[E1], NORTH), tile_edge(bp->neighbors[S1], WEST), tile_edge(bp->neighbors[S1], NORTH) };
        return all_equals(cs, 6);
    }

    return false;
}

bool down_left_diagonal_line(board_part* bp)
{

    const struct tile* ts[] = { bp->base, bp->neighbors[W1], bp->neighbors[S1] };
    if (!all_empty(ts, 3)) {
        struct color* cs[] = { tile_edge(bp->base, SOUTH), tile_edge(bp->base, WEST), tile_edge(bp->neighbors[W1], EAST), tile_edge(bp->neighbors[W1], NORTH), tile_edge(bp->neighbors[S1], EAST), tile_edge(bp->neighbors[S1], NORTH) };
        return all_equals(cs, 6);
    }
    return false;
}

bool right_triangle(board_part* bp)
{
    const struct tile* ts[] = { bp->base, bp->neighbors[E1] };
    if (!all_empty(ts, 2)) {
        struct color* cs[] = { tile_edge(bp->base, SOUTH), tile_edge(bp->base, EAST), tile_edge(bp->neighbors[E1], WEST), tile_edge(bp->neighbors[E1], SOUTH) };
        return all_equals(cs, 4);
    }
    return false;
}

bool left_triangle(board_part* bp)
{
    const struct tile* ts[] = { bp->base, bp->neighbors[W1] };
    if (!all_empty(ts, 2)) {
        struct color* cs[] = { tile_edge(bp->base, SOUTH), tile_edge(bp->base, WEST), tile_edge(bp->neighbors[W1], EAST), tile_edge(bp->neighbors[W1], SOUTH) };
        return all_equals(cs, 4);
    }
    return false;
}

bool big_triangle(board_part* bp)
{
    const struct tile* ts[] = { bp->base, bp->neighbors[W1], bp->neighbors[E1] };
    if (!all_empty(ts, 3)) {
        struct color* cs[] = { tile_edge(bp->base, SOUTH), tile_edge(bp->base, WEST), tile_edge(bp->base, NORTH), tile_edge(bp->base, EAST), tile_edge(bp->neighbors[W1], EAST), tile_edge(bp->neighbors[W1], SOUTH), tile_edge(bp->neighbors[E1], WEST), tile_edge(bp->neighbors[E1], SOUTH) };
        return all_equals(cs, 8);
    }
    return false;
}

bool all_in(board_part* bp)
{
    const struct tile* ts[] = { bp->base, bp->neighbors[W1], bp->neighbors[W2], bp->neighbors[E1], bp->neighbors[E2], bp->neighbors[N1], bp->neighbors[N2], bp->neighbors[S1], bp->neighbors[S2] };
    if (!all_empty(ts, 9)) {
        struct color* cs[] = { tile_edge(bp->base, WEST), tile_edge(bp->base, EAST), tile_edge(bp->base, NORTH), tile_edge(bp->base, SOUTH), tile_edge(bp->neighbors[W1], NORTH), tile_edge(bp->neighbors[W1], SOUTH), tile_edge(bp->neighbors[W1], EAST), tile_edge(bp->neighbors[W1], WEST), tile_edge(bp->neighbors[W2], NORTH), tile_edge(bp->neighbors[W2], SOUTH), tile_edge(bp->neighbors[W2], EAST), tile_edge(bp->neighbors[W2], WEST), tile_edge(bp->neighbors[E1], NORTH), tile_edge(bp->neighbors[E1], SOUTH), tile_edge(bp->neighbors[E1], EAST), tile_edge(bp->neighbors[E1], WEST), tile_edge(bp->neighbors[E2], NORTH), tile_edge(bp->neighbors[E2], SOUTH), tile_edge(bp->neighbors[E2], EAST), tile_edge(bp->neighbors[E2], WEST), tile_edge(bp->neighbors[N1], NORTH), tile_edge(bp->neighbors[N1], SOUTH), tile_edge(bp->neighbors[N1], EAST), tile_edge(bp->neighbors[N1], WEST), tile_edge(bp->neighbors[N2], NORTH), tile_edge(bp->neighbors[N2], SOUTH), tile_edge(bp->neighbors[N2], EAST), tile_edge(bp->neighbors[N2], WEST), tile_edge(bp->neighbors[S1], NORTH), tile_edge(bp->neighbors[S1], SOUTH), tile_edge(bp->neighbors[S1], EAST), tile_edge(bp->neighbors[S1], WEST), tile_edge(bp->neighbors[S2], NORTH), tile_edge(bp->neighbors[S2], SOUTH), tile_edge(bp->neighbors[S2], EAST), tile_edge(bp->neighbors[S2], WEST) };
        return all_equals(cs, 36);
    }
    return false;
}

static pattern patterns[21] = {
    { &universal_pattern, 1 },
    { &short_vertical_line_pattern, 4 },
    { &short_horizontal_line_pattern, 4 },
    { &vertical_alternation, 10 },
    { &horizontal_alternation, 10 },
    { &small_square_alternation, 10 },
    { &short_horizontal_alternation, 5 },
    { &short_vertical_alternation, 5 },
    { &three_squares_vertical_alike, 10 },
    { &three_squares_horizontal_alike, 10 },
    { &four_squares_horizontal_alike, 10 },
    { &four_squares_vertical_alike, 10 },
    { &small_diamond, 15 },
    { &up_right_diagonal_line, 10 },
    { &up_left_diagonal_line, 10 },
    { &down_right_diagonal_line, 10 },
    { &down_left_diagonal_line, 10 },
    { &right_triangle, 15 },
    { &left_triangle, 15 },
    { &big_triangle, 20 },
    { &all_in, 100 },
};

int get_pattern_score_at(struct board* b, int x, int y)
{
    board_part bp;
    set_board_part(&bp, b, x, y);

    int score = 0;

    for (int i = 0; i < PATTERN_NUMBER; i++)
        score += (*(patterns[i].predicate))(&bp) ? patterns[i].score : 0;

    return score == 1 ? score : score - 1;
}
