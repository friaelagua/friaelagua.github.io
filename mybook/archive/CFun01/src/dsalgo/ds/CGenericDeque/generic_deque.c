#include "generic_deque.h"

#include <stdlib.h>
#include <string.h>

Deque *deque_create(size_t element_size, void (*free_func)(void *)) {
    Deque *dq = malloc(sizeof(Deque));
    if (!dq)
        return NULL;
    dq->front = NULL;
    dq->rear = NULL;
    dq->element_size = element_size;
    dq->free_func = free_func;
    return dq;
}

int deque_is_empty(Deque *dq) {
    return dq->front == NULL;
}

int deque_push_front(Deque *dq, void *element) {
    DequeNode *node = malloc(sizeof(DequeNode));
    if (!node)
        return 0;
    node->data = malloc(dq->element_size);
    if (!node->data) {
        free(node);
        return 0;
    }
    memcpy(node->data, element, dq->element_size);
    node->prev = NULL;
    node->next = dq->front;

    if (dq->front) {
        dq->front->prev = node;
    } else {
        dq->rear = node;
    }
    dq->front = node;
    return 1;
}

int deque_push_back(Deque *dq, void *element) {
    DequeNode *node = malloc(sizeof(DequeNode));
    if (!node)
        return 0;
    node->data = malloc(dq->element_size);
    if (!node->data) {
        free(node);
        return 0;
    }
    memcpy(node->data, element, dq->element_size);
    node->next = NULL;
    node->prev = dq->rear;

    if (dq->rear) {
        dq->rear->next = node;
    } else {
        dq->front = node;
    }
    dq->rear = node;
    return 1;
}

int deque_pop_front(Deque *dq) {
    if (deque_is_empty(dq))
        return 0;
    DequeNode *node = dq->front;
    dq->front = node->next;
    if (dq->front)
        dq->front->prev = NULL;
    else
        dq->rear = NULL;
    if (dq->free_func)
        dq->free_func(node->data);
    free(node->data);
    free(node);
    return 1;
}

int deque_pop_back(Deque *dq) {
    if (deque_is_empty(dq))
        return 0;
    DequeNode *node = dq->rear;
    dq->rear = node->prev;
    if (dq->rear)
        dq->rear->next = NULL;
    else
        dq->front = NULL;
    if (dq->free_func)
        dq->free_func(node->data);
    free(node->data);
    free(node);
    return 1;
}

void *deque_front(Deque *dq) {
    return dq->front ? dq->front->data : NULL;
}

void *deque_back(Deque *dq) {
    return dq->rear ? dq->rear->data : NULL;
}

void deque_destroy(Deque *dq) {
    while (!deque_is_empty(dq)) {
        deque_pop_front(dq);
    }
    free(dq);
}
