#include "generic_queue.h"

#include <string.h>
#include <stdio.h>

GenericQueue *createQueue(int capacity, size_t element_size) {
	GenericQueue *q = malloc(sizeof(GenericQueue));
	if(!q)
		return NULL;
	q->buffer = malloc(capacity * element_size);
	if(!q->buffer) {
		free(q);
		return NULL;
	}
	q->element_size = element_size;
	q->capacity = capacity;
	q->front = 0;
	q->rear = -1;
	q->size = 0;
	return q;
}

int isFull(GenericQueue *q) {
	return q->size == q->capacity;
}

int isEmpty(GenericQueue *q) {
	return q->size == 0;
}

int enqueue(GenericQueue *q, void *element) {
	if(isFull(q))
		return 0;				// failure
	q->rear = (q->rear + 1) % q->capacity;
	memcpy((char *) q->buffer + q->rear * q->element_size, element,
		   q->element_size);
	q->size++;
	return 1;					// success
}

int dequeue(GenericQueue *q, void *element) {
	if(isEmpty(q))
		return 0;				// failure
	memcpy(element, (char *) q->buffer + q->front * q->element_size,
		   q->element_size);
	q->front = (q->front + 1) % q->capacity;
	q->size--;
	return 1;					// success
}

void destroyQueue(GenericQueue *q) {
	if(q) {
		free(q->buffer);
		free(q);
	}
}
