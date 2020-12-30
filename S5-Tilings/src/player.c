#include "player.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

void distribute_deck(struct deck* d, struct queue* hand)
{
    const int initial_size = d->size;

    struct deck_pair* available_dp[initial_size];
    int memo_n[initial_size];
    for (int i = 0; i < initial_size; i++) {
        available_dp[i] = &(d->cards[i]);
        memo_n[i] = d->cards[i].n;
    }

    int n_possibility = d->size;

    while (n_possibility != 0) {
        int id = rand() % n_possibility;
        struct deck_pair* dp = available_dp[id];
        enqueue(hand, (struct tile*)dp->t);
        if (--dp->n == 0)
            available_dp[id] = available_dp[--n_possibility];
    }

    for (int i = 0; i < initial_size; i++)
        d->cards[i].n = memo_n[i];
}
