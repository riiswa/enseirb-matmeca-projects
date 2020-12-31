#ifndef _SET_H_

#include "queue.h"

#define _SET_H_

/***************************************************************************/ /**
 * Set implemented with queue (linked-list)
 ******************************************************************************/
typedef struct set_with_queue {
    struct queue super;
    unsigned int size;
} set;

/***************************************************************************/ /**
 * Create an empty set
 ******************************************************************************/
set empty_set();

/***************************************************************************/ /**
 * Check if a item is present in set
 *
 * @param s The set
 * @param element The element to find
 ******************************************************************************/
int set_search(set* s, void* element);

/***************************************************************************/ /**
 *  Add an element to a set
 *
 * @param s The set
 * @param value The element
 ******************************************************************************/
void set_add(set* s, void* element);

/***************************************************************************/ /**
 *  Remove an element if is present in set
 *
 * @param s The set
 * @param value The element
 ******************************************************************************/
void set_remove(set* s, void* element);

/***************************************************************************/ /**
 *  Get the size of a set
 *
 *  @param s The set
 ******************************************************************************/
unsigned int set_size(set* s);

/***************************************************************************/ /**
 * Free all the memory used by a set
 *
 * @param s The set
 ******************************************************************************/
void clean_set(set* s);

void* generic_set_find(set* s, void* element, void* (*cmp)(void*));

void clear_adjacencies_memory();

#endif
