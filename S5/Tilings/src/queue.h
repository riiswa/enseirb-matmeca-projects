#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <stdlib.h>

/***************************************************************************/ /**
 * Linked-list node
 ******************************************************************************/
struct node {
    void* value; /**< Value of the node */
    struct node* next; /**< Pointer to the next node */
};

/***************************************************************************/ /**
 * Queue implemented with linked-list
 ******************************************************************************/
struct queue {
    struct node* front; /**< Pointer to first element of the queue */
    struct node* rear; /**< Pointer to last element of the queue */
};

/***************************************************************************/ /**
 * Create an empty queue
 ******************************************************************************/
struct queue empty_queue();

/***************************************************************************/ /**
 *  Add an element at the end of the queue
 *
 * @param q The queue
 * @param value The element
 ******************************************************************************/
void enqueue(struct queue* q, void* value);

/***************************************************************************/ /**
 * Remove the first element of the queue
 *
 * @param q The queue
 * @return pointer to the removed element
 ******************************************************************************/
void* dequeue(struct queue* q);

/***************************************************************************/ /**
 *  Fill a queue with an array
 *
 * @param arr The array
 * @param s Size of array
 * @param item_size Size of one element
 * @return New queue with the element of given array
 ******************************************************************************/
struct queue fill_queue(void* arr, int s, size_t item_size);

/***************************************************************************/ /**
 * Get the first element of the queue without remove it
 *
 * @param q The queue
 * @return pointer to the first element
 ******************************************************************************/
void* top(struct queue* q);

/***************************************************************************/ /**
 * Check if given queue is empty
 *
 * @param q The queue
 ******************************************************************************/
int queue_is_empty(struct queue* q);

/***************************************************************************/ /**
 * Free all the memory used by a queue
 *
 * @param q The queue
 ******************************************************************************/
void clean_queue(struct queue* q);

#endif
