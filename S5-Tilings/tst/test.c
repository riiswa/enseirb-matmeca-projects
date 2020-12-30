#include "../src/adjacencies.h"
#include "../src/board.h"
#include "../src/color.h"
#include "../src/globals.h"
#include "../src/loops.h"
#include "../src/pattern.h"
#include "../src/queue.h"
#include "../src/set.h"
#include "../src/symetries.h"
#include "../src/tile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int success = 1;

int g_seed;

static struct deck d;

void test(int t, char* name)
{
    printf("Test %s: %s\n", name, t ? "OK!" : "FAILED!");
    success &= t;
}

void test_queue()
{
    int arr[] = { 1, 2, 3, 4, 5, 6, 4, 8 };
    int s = 8;
    struct queue q = fill_queue(arr, s, sizeof(int));
    test(*((int*)dequeue(&q)) == 1, "Dequeue 1");
    test(*((int*)dequeue(&q)) == 2, "Dequeue 2");
    int x = 20;
    enqueue(&q, &x);
    int arr2[7];
    int expectation[] = { 3, 4, 5, 6, 4, 8, x };
    for (int i = 0; i < (s - 1); i++)
        arr2[i] = *((int*)dequeue(&q));
    test(!memcmp(arr2, expectation, 7), "Enqueue");
    test(queue_is_empty(&q) == 1, "Queue is empty");
}

void test_color()
{
    struct color* black_color = color_from_name("BLACK");
    test(strcmp(color_name(black_color), "BLACK") == 0, "NAME BLACK");
    test(strcmp(color_cstring(black_color), "\033[1;30m") == 0, "ANSI BLACK");
    printf("La couleur noire est %s NOIRE\n", color_cstring(black_color));
    printf("\033[0m");
}

void print_tile(const struct tile* t)
{
    int e = tile_is_empty(t);
    printf("[");
    for (int j = 0; j < MAX_DIRECTION; j++) {
        if (e) {
            printf("%6s ", "NULL");
        } else {
            struct color* c = tile_edge(t, j);
            printf("%s", color_cstring(c));
            printf("%6s ", color_name(c));
            printf("\033[0m");
        }
    }
    printf("]");
}

void test_tile_and_board()
{
    printf("Random deck generation:\n");
    for (unsigned int i = 0; i < d.size; i++) {
        const struct tile* t = d.cards[i].t;
        printf("\t(%d,", d.cards[i].n);
        print_tile(t);
        printf("),\n");
    }

    struct board* b = empty_board(3);

    int m = board_size(b);

    printf("Board with tiles:\n");
    board_set(b, m / 2, m / 2, d.cards[0].t);
    board_set(b, 0, 0, d.cards[1].t);
    board_set(b, m - 1, m - 1, d.cards[1].t);
    print_board(b, 0, NULL);

    test(tile_equals(board_get(b, m - 1, m - 1), board_get(b, 0, 0)), "Tiles is equals");
    test(!tile_equals(board_get(b, m / 2, m / 2), board_get(b, 0, 0)), "Tiles is not equals");
    test(board_cell_is_empty(b, 0, 1), "Board cell is empty");
    test(tile_edge(d.cards[0].t, NORTH) == tile_edge(board_get(b, m / 2, m / 2), NORTH), "Tile edge");
}

void print_set(set* s)
{
    struct node* n = s->super.front;
    while (n != NULL) {
        printf("%d ", *((int*)(n->value)));
        n = n->next;
    }
    printf("\n");
}

void test_set()
{
    int arr[] = { 1, 2, 3, 4, 5, 6, 4, 8, 9, 10 };
    int s = 8;

    set my_set = empty_set();

    for (int i = 0; i < s; i++)
        set_add(&my_set, &(arr[i]));
    printf("My set: \n");
    print_set(&my_set);

    test(set_size(&my_set) == 8, "Set size");
    set_add(&my_set, &(arr[7]));
    test(set_size(&my_set) == 8, "Add item already in set");
    print_set(&my_set);
    set_add(&my_set, &(arr[8]));
    test(set_size(&my_set) == 9, "Add new item to set");
    print_set(&my_set);
    set_remove(&my_set, &(arr[9]));
    test(set_size(&my_set) == 9, "Remove item that not in set");
    print_set(&my_set);
    set_remove(&my_set, &(arr[0]));
    test(set_size(&my_set) == 8, "Remove item that in set");
    print_set(&my_set);
    clean_set(&my_set);
    test(set_size(&my_set) == 0, "Clean set");
}

void test_pattern()
{
    struct board* b = empty_board(3);
    const struct tile* t1 = d.cards[12].t;
    const struct tile* t2 = d.cards[15].t;
    const struct tile* t3 = d.cards[3].t;
    board_set(b, 0, 1, t1);
    board_set(b, 1, 1, t2);
    board_set(b, 2, 1, t3);
    print_board(b, 0, NULL);
    test(get_pattern_score_at(b, 1, 1) == 9, "score of pattern");
    test(get_pattern_score_at(b, 0, 1) == 1, "score of pattern");
}

void test_symetries()
{
    const struct tile* t = d.cards[0].t;
    test(tile_edge(t, EAST) == rotated_tile_edge(t, NORTH, 1), "1 rotation");
    test(tile_edge(t, SOUTH) == rotated_tile_edge(t, NORTH, 2), "2 rotation");
    test(tile_edge(t, WEST) == rotated_tile_edge(t, NORTH, 3), "3 rotation");
    test(tile_edge(t, NORTH) == rotated_tile_edge(t, NORTH, 4), "4 rotation");
    test(tile_edge(t, EAST) == rotated_tile_edge(t, NORTH, 5), "5 rotation");
    test(change_direction(NORTH, 1) == EAST, "1 change of direction");
    test(change_direction(NORTH, 2) == SOUTH, "2  changes  of direction");
}
/*
void test_connection()
{
const int player_numbers = 2;


}
*/
int check_struct_in_array(int len, struct index* t, struct index e)
{
    for (int o = 0; o < len; ++o) {
        if (t[0].x == e.x && t[0].y == e.y)
            return 1;
    }

    return 0;
}
/*
void test_list_authorized_places()
    {
        unsigned int n_authorized_places;
        unsigned int* list_authorized_places_rotations[n_authorized_places];
        struct index* authorized_places[n_authorized_places];
        int first_turn = 1;
        struct board* b = empty_board(3);  
        const struct tile* t4 = d.cards[12].t;
        for(int i = 0; i < 3 ; ++i)
        {
            for (int j = 0; i < 3; j++)
            {
    
                list_authorized_places(&n_authorized_places,authorized_places,b,t4 ,first_turn,list_authorized_places_rotations);
                test(check_struct_in_array(n_authorized_places,authorized_places,(struct index){ i, j }) == 1, " Authorized place at the begining");
                    
            }
            
        }

    }
*/
void test_loops()
{
    int limit = 50;
    int x = -1;
    int y = 50;
    update_coord_with_loops(&x, limit);
    update_coord_with_loops(&y, limit);
    test(x == 49 && y == 0, "Coords with loops");
}

void test_adjacencies()
{
    const struct tile* t = d.cards[0].t;
    printf("%d\n", edge_are_adjacent(t, NORTH, EAST));
    printf("%d\n", edge_are_adjacent(t, NORTH, NORTH));
    printf("%d\n", edge_are_adjacent(t, NORTH, SOUTH));
    printf("%d\n", edge_are_adjacent(t, NORTH, WEST));
}

int main(void)
{
    // Init global variables
    g_seed = 0;
    deck_init(&d);
    init_tiles_adjacencies(&d);
    test_queue();
    test_color();
    test_tile_and_board();
    test_set();
    test_symetries();
    test_loops();
    test_adjacencies();
    test_pattern();
    //    test_list_authorized_places();
    if (success)
        printf("\033[0;32m Congratulations, you passed all the tests\n");
    else
        printf("\033[0;31m There are some errors...\n");
    printf("\033[0m");
    return 0;
}
