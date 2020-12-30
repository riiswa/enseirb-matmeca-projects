#include "adjacencies.h"
#include "blocs.h"
#include "board.h"
#include "color.h"
#include "connection.h"
#include "globals.h"
#include "influence.h"
#include "pattern.h"
#include "player.h"
#include "queue.h"
#include "tile.h"

#include <getopt.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define GOTO(ligne, col) printf("\x1B[%d;%dH", ligne, col)

#define THE_KING_ID (-1)

// Global seed for the random number generator
static int seed = 0;
static unsigned int number_players = 2;
static int b_size = 10;
static int output = 0;
int g_seed;
unsigned int g_number_players;

////////////////////////////////////////////////////////////////
// Function for parsing the options of the program
// Currently available options are :
// -s <seed> : sets the seed
void parse_opts(int argc, char* argv[])
{
    int opt;
    while ((opt = getopt(argc, argv, "s:n:b:o")) != -1) {
        switch (opt) {
        case 's':
            seed = atoi(optarg);
            break;
        case 'n':
            number_players = atoi(optarg);
            break;
        case 'b':
            b_size = atoi(optarg);
            break;
        case 'o':
            output = 1;
            break;

        default: /* '?' */
            fprintf(stderr, "Usage: %s [-s seed] [-n number_players] [-b board_size] [-o]\n",
                argv[0]);
            exit(EXIT_FAILURE);
        }
    }
}

////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
    seed = time(0);
    parse_opts(argc, argv);

    if (number_players < 2 || number_players > 20) {
        fprintf(stderr, "Number of players should be between 2 and 20, you gave %d. Exiting...", number_players);
        exit(EXIT_FAILURE);
    }
    if (b_size < 1 || b_size > 50) {
        fprintf(stderr, "Board size should be between 1 and 50, you gave %d. Exiting...", b_size);
        exit(EXIT_FAILURE);
    }

    printf("Seed : %d\n", seed);
    printf("Number of players : %d\n", number_players);
    printf("Board Size : %d x %d\n", b_size, b_size);
    g_seed = seed;
    g_number_players = number_players;

    //The pseudo-random number generator is initialized
    srand(seed);

    clock_t begin = clock();

    // Init variables
    struct deck d;
    deck_init(&d);
    init_tiles_adjacencies(&d);

    struct board* b = empty_board(b_size);

    const int n = number_players;

    int players_ids[n + 1], players_scores[n];
    struct queue players_hands[n];
    for (unsigned int i = 0; i < number_players; i++) {
        players_hands[i] = empty_queue();
        distribute_deck(&d, &players_hands[i]);
        players_ids[i] = i;
        players_scores[i] = 0;
    }

    players_ids[n] = THE_KING_ID; // Add The King

    struct queue players_queue = fill_queue(players_ids, n + 1, sizeof(int));

    struct index authorized_places[MAX_BOARD_SIZE];
    unsigned int authorized_places_rotations[MAX_BOARD_SIZE];
    unsigned int n_authorized_places = 0, skipped_turn = 0;
    struct tile* current_tile;
    struct queue* current_player_hand;
    int current_player_id = 0;
    struct index current_index = { 0, 0 };
    struct index king_id;

    int first_turn = 1;
    int turn = 0;
    int winner = -1;

    if (output)
        system("clear");

    // Main loop
    while (skipped_turn != number_players) {
        current_player_id = *((int*)top(&players_queue));

        if (current_player_id != THE_KING_ID) {
            current_player_hand = &players_hands[current_player_id];

            if (output) {
                GOTO(0, 0);
                printf("Player: %2d -- Turn %d\n", current_player_id, turn);
            }

            int limit = 3;
            struct index filters[MAX_BOARD_SIZE];
            unsigned int n_filters = 0;

            while (limit) {
                current_tile = top(current_player_hand);
                if (queue_is_empty(current_player_hand)) {
                    skipped_turn++;
                    break;
                }
                list_authorized_places(&n_authorized_places, authorized_places, b, current_tile, first_turn, authorized_places_rotations);
                filter_authorized_places(&n_authorized_places, authorized_places, n_filters, filters, authorized_places_rotations);

                if (n_authorized_places != 0) {
                    first_turn = 0;
                    int random_index = rand() % n_authorized_places;
                    current_index = authorized_places[random_index];
                    board_set(b, current_index.x, current_index.y, current_tile);
                    board_set_owner(b, current_index.x, current_index.y, current_player_id);
                    board_set_rotation(b, current_index.x, current_index.y, authorized_places_rotations[random_index]);
                    update_property_levels(b, current_index.x, current_index.y, current_player_id);
                    dequeue(current_player_hand);
                    skipped_turn = 0;
                    filters[n_filters] = current_index;
                    n_filters++;
                } else {
                    if (limit == 3) {
                        enqueue(current_player_hand, dequeue(current_player_hand));
                        skipped_turn++;
                    }
                    break;
                }
                limit--;
            }

        } else if (output) {
            the_king_move(b, &king_id);
            GOTO(0, 0);
            printf("The King -- Turn %d           \n", turn);
        }

        enqueue(&players_queue, dequeue(&players_queue));
        influence_global_decrement(b);

        n_authorized_places = 0;
        turn++;
        if (output) {
            printf("==================================================\n");
            print_board(b, current_player_id == THE_KING_ID, &king_id);
            printf("==================================================\n");
            //if (current_player_id == THE_KING_ID) sleep(1);
        }
    }

    struct owners ows;

    for (int i = 0; i < b_size; i++) {
        for (int j = 0; j < b_size; j++) {
            if (!tile_is_empty(board_get(b, i, j))) {
                int s = get_pattern_score_at(b, i, j);
                get_owners_by_influence(b, i, j, &ows);
                for (unsigned int k = 0; k < number_players; ++k) {
                    if (ows.presences[k])
                        players_scores[k] += s;
                }
                get_connection_score_at(b, i, j, number_players, players_scores);
            }
        }
    }

    for (unsigned int i = 0; i < number_players; i++)
        printf("Player %2d |", i);
    printf("\n");

    for (unsigned int i = 0; i < number_players; i++)
        printf("%9d |", players_scores[i]);
    printf("\n");

    int max = 0;
    for (unsigned int i = 0; i < number_players; i++)
        if (players_scores[i] > max) {
            max = players_scores[i];
            winner = i;
        }

    printf("Woaw ! Player %d win with a score of %d\n", winner, players_scores[winner]);

    //print_property_levels(b);

    // Freeing allocated memory
    clean_queue(&players_queue);
    for (unsigned int i = 0; i < number_players; i++)
        clean_queue(&(players_hands[i]));
    clear_connection_memory();
    clear_adjacencies_memory();

    clock_t end = clock();

    printf("Elapsed: %f seconds\n", (double)(end - begin) / CLOCKS_PER_SEC);

    return EXIT_SUCCESS;
}
