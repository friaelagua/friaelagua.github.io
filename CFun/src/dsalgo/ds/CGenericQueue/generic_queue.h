#ifndef GENERIC_QUEUE_H
#define GENERIC_QUEUE_H

#include <stdlib.h>

typedef struct {
	void *buffer;				// Pointer to the buffer holding elements
	size_t element_size;		// Size of each element
	int capacity;				// Maximum number of elements
	int front;					// Index of the front element
	int rear;					// Index of the last element
	int size;					// Current number of elements
} GenericQueue;

// Create a queue with given capacity and element size
GenericQueue *createQueue(int capacity, size_t element_size);

// Check if queue is full
int isFull(GenericQueue * q);

// Check if queue is empty
int isEmpty(GenericQueue * q);

// Enqueue: add element at rear
int enqueue(GenericQueue * q, void *element);

// Dequeue: remove element from front and copy it to `element`
int dequeue(GenericQueue * q, void *element);

// Destroy queue and free memory
void destroyQueue(GenericQueue * q);

#endif // GENERIC_QUEUE_H
