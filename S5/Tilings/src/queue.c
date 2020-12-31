#include "queue.h"

#include "tile.h"
#include <stdio.h>
#include <stdlib.h>

struct queue empty_queue()
{
    return ((struct queue){ NULL, NULL });
}

void enqueue(struct queue* q, void* value)
{

    struct node* n = malloc(sizeof(struct node));
    if (n == NULL) {
        fprintf(stderr, "malloc failed\n");
        exit(EXIT_FAILURE);
    }
    n->value = value;
    n->next = NULL;
    if (q->front == NULL) {
        q->front = n;
        q->rear = n;
    } else {
        q->rear->next = n;
        q->rear = n;
    }
}

void* dequeue(struct queue* q)
{
    if (q->front == NULL)
        return NULL;
    void* value = q->front->value;
    struct node* n = q->front->next;
    free(q->front);
    q->front = n;
    if (q->front == NULL)
        q->rear = NULL;
    return value;
}

struct queue fill_queue(void* arr, int s, size_t item_size)
{
    struct queue q = empty_queue();
    for (int i = 0; i < s; i++, arr += item_size)
        enqueue(&q, arr);
    return q;
}

void* top(struct queue* q)
{
    return (queue_is_empty(q) ? NULL : q->front->value);
}

int queue_is_empty(struct queue* q)
{
    return q->front == NULL;
}

void clean_queue(struct queue* q)
{
    while (!queue_is_empty(q))
        dequeue(q);
}