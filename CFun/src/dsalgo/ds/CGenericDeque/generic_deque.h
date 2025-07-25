#ifndef GENERIC_DEQUE_H
#define GENERIC_DEQUE_H

#include <stddef.h>  // for size_t

typedef struct DequeNode {
    void *data;
    struct DequeNode *prev;
    struct DequeNode *next;
} DequeNode;

typedef struct {
    DequeNode *front;
    DequeNode *rear;
    size_t element_size;
    void (*free_func)(void *);
} Deque;

// Create a new deque
Deque *deque_create(size_t element_size, void (*free_func)(void *));

// Check if deque is empty
int deque_is_empty(Deque *dq);

// Insert at front
int deque_push_front(Deque *dq, void *element);

// Insert at rear
int deque_push_back(Deque *dq, void *element);

// Remove from front
int deque_pop_front(Deque *dq);

// Remove from rear
int deque_pop_back(Deque *dq);

// Get front element (without removing)
void *deque_front(Deque *dq);

// Get rear element (without removing)
void *deque_back(Deque *dq);

// Dispose entire deque
void deque_destroy(Deque *dq);

#endif /* GENERIC_DEQUE_H */
