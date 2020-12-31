#include "connection.h"
#include "adjacencies.h"
#include "influence.h"
#include "loops.h"
#include "stdio.h"
#include "string.h"
#include "symetries.h"

#define SQUARE(x) ((x) * (x))

static struct index indices[MAX_BOARD_SIZE];

static set visited_colors[MAX_BOARD_SIZE];

static int first_time = 1;

int index_to_int(struct index* id, int m)
{
    return COORDS_TO_INT(id->x, id->y, m);
}

const struct tile* tile_from_index(struct board* b, struct index* id)
{
    return board_get(b, id->x, id->y);
}

void flood_fill_algorithm(struct board* b, struct index* current, struct color* c, set* visited_cells)
{
    if (set_search(visited_cells, current) || set_search(&(visited_colors[index_to_int(current, board_size(b))]), c))
        return;
    else if (tile_is_empty(tile_from_index(b, current)))
        return;
    else {
        set_add(visited_cells, current);
        set_add(&(visited_colors[index_to_int(current, board_size(b))]), c);
        for (enum direction d = 0; d < MAX_DIRECTION; d++) {
            int next_x = current->x, next_y = current->y;

            switch (d) {
            case NORTH:
                if (!edge_are_adjacent(board_get(b, current->x, current->y),
                        change_direction(NORTH, board_get_rotation(b, current->x, current->y)),
                        change_direction(SOUTH, board_get_rotation(b, current->x, current->y))))
                    continue;
                next_x--;
                break;
            case SOUTH:
                if (!edge_are_adjacent(board_get(b, current->x, current->y),
                        change_direction(NORTH, board_get_rotation(b, current->x, current->y)),
                        change_direction(SOUTH, board_get_rotation(b, current->x, current->y))))
                    continue;
                next_x++;
                break;
            case EAST:
                if (!edge_are_adjacent(board_get(b, current->x, current->y),
                        change_direction(WEST, board_get_rotation(b, current->x, current->y)),
                        change_direction(EAST, board_get_rotation(b, current->x, current->y))))
                    continue;
                next_y++;
                break;
            case WEST:
                if (!edge_are_adjacent(board_get(b, current->x, current->y),
                        change_direction(WEST, board_get_rotation(b, current->x, current->y)),
                        change_direction(EAST, board_get_rotation(b, current->x, current->y))))
                    continue;
                next_y--;
                break;
            default:
                break;
            }

            update_coord_with_loops(&next_x, board_size(b));
            update_coord_with_loops(&next_y, board_size(b));

            struct index* next_id = &(indices[COORDS_TO_INT(next_x, next_y, board_size(b))]);
            struct color* base_color = rotated_tile_edge(tile_from_index(b, current), d, board_get_rotation(b, current->x, current->y));
            if (base_color == c && rotated_tile_edge(tile_from_index(b, next_id), opposite_direction(d), board_get_rotation(b, next_id->x, next_id->y)) == c)
                flood_fill_algorithm(b, next_id, c, visited_cells);
        }
    }
}

void init_statics(struct board* b)
{
    int m = board_size(b);
    for (int i = 0; i < m; i++)
        for (int j = 0; j < m; j++) {
            struct index id = (struct index){ i, j };
            int index = index_to_int(&id, m);
            indices[index] = id;
            visited_colors[index] = empty_set();
        }
}

void count_points(struct board* b, set* visited_cells, const int player_numbers, int scores[])
{
    int tmp[player_numbers];
    memset(tmp, 0, player_numbers * sizeof(int));

    int count = 0;
    int max = 0;

    for (struct node* n = visited_cells->super.front; n != NULL; n = n->next) {
        struct index* id = ((struct index*)n->value);
        struct property_level* pl = board_get_property_level(b, id->x, id->y);
        for (int i = 0; i < player_numbers; ++i) {
            tmp[i] += (pl->values)[i];
            if (tmp[i] > max)
                max = tmp[i];
        }
        count++;
    }

    if (count == 0)
        return;

    int n_players_with_max = 0;

    for (int i = 0; i < player_numbers; i++)
        n_players_with_max += tmp[i] == max;

    for (int i = 0; i < player_numbers; i++)
        scores[i] += (tmp[i] == max ? SQUARE(count) / n_players_with_max : 0);
}

void get_connection_score_at(struct board* b, int x, int y, const int player_numbers, int scores[])
{
    if (first_time) {
        init_statics(b);
        first_time = 0;
    }
    const struct tile* t = board_get(b, x, y);
    if (tile_is_empty(t))
        return;
    set colors_to_check = empty_set();
    set visited_cells = empty_set();

    struct index* id = &(indices[COORDS_TO_INT(x, y, board_size(b))]);

    for (enum direction d = 0; d < MAX_DIRECTION; d++) {
        struct color* c = rotated_tile_edge(t, d, board_get_rotation(b, x, y));
        if (!set_search(&colors_to_check, c)) {
            flood_fill_algorithm(b, id, c, &visited_cells);
            if (set_size(&visited_cells) > 1)
                count_points(b, &visited_cells, player_numbers, scores);
            clean_set(&visited_cells);
        }
    }
    clean_set(&colors_to_check);
}

void clear_connection_memory()
{
    for (int i = 0; i < MAX_BOARD_SIZE; i++)
        clean_set(&(visited_colors[i]));
}
