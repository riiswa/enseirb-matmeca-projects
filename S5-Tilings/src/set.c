#include "set.h"
#include <stdlib.h>

set empty_set()
{
    return (set){ empty_queue(), 0 };
}

void* identity(void* e)
{
    return e;
}

void* generic_set_find(set* s, void* element, void* (*cmp)(void*))
{
    struct node* n = s->super.front;
    while (n != NULL && cmp(element) != cmp(n->value))
        n = n->next;
    return n == NULL ? NULL : n->value;
}

void* set_find(set* s, void* element)
{
    return generic_set_find(s, element, &identity);
}

int set_search(set* s, void* element)
{
    struct node* n = s->super.front;
    while (n != NULL && element != n->value)
        n = n->next;
    return n != NULL;
}

void set_add(set* s, void* element)
{
    if (!set_search(s, element)) {
        enqueue(&(s->super), element);
        s->size++;
    }
}

void set_remove(set* s, void* element)
{
    if (s->size > 0) {
        struct node* current_node = s->super.front;
        struct node* previous_node = NULL;
        while (current_node != NULL && element != current_node->value) {
            previous_node = current_node;
            current_node = current_node->next;
        }

        if (previous_node == NULL) {
            dequeue(&(s->super));
            s->size--;
        }

        else if (current_node != NULL) {
            previous_node->next = current_node->next;
            free(current_node);
            if (s->super.front == NULL)
                s->super.rear = NULL;
            s->size--;
        }
    }
}

unsigned int set_size(set* s)
{
    return s->size;
}

void clean_set(set* s)
{
    clean_queue(&(s->super));
    s->size = 0;
}
