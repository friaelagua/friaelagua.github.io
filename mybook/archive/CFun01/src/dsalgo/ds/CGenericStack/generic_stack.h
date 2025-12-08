// stack.h
#ifndef GENERIC_STACK_H
#define GENERIC_STACK_H

#include <stdbool.h>

typedef struct {
	void *data;					// Pointer to stack's data buffer
	int elementSize;			// Size of each element in bytes
	int capacity;				// Maximum number of elements
	int top;					// Index of the top element
} Stack;

// Create a stack with specified capacity and element size
Stack *createStack(int capacity, int elementSize);

// Free the stack memory
void freeStack(Stack * stack);

// Push an element onto the stack
bool push(Stack * stack, void *element);

// Pop the top element from the stack into the provided buffer
bool pop(Stack * stack, void *outElement);

// Peek the top element without removing it
bool peek(Stack * stack, void *outElement);

// Check if the stack is empty
bool isEmpty(Stack * stack);

// Check if the stack is full
bool isFull(Stack * stack);

#endif // GENERIC_STACK_H
