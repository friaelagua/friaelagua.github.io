#include "generic_stack.h"
#include <stdlib.h>
#include <string.h>

Stack *createStack(int capacity, int elementSize) {
	Stack *stack = (Stack *) malloc(sizeof(Stack));
	if(!stack)
		return NULL;
	stack->data = malloc(capacity * elementSize);
	if(!stack->data) {
		free(stack);
		return NULL;
	}
	stack->elementSize = elementSize;
	stack->capacity = capacity;
	stack->top = -1;
	return stack;
}

void freeStack(Stack *stack) {
	if(stack) {
		free(stack->data);
		free(stack);
	}
}

bool isEmpty(Stack *stack) {
	return stack->top == -1;
}

bool isFull(Stack *stack) {
	return stack->top == (stack->capacity - 1);
}

bool push(Stack *stack, void *element) {
	if(isFull(stack))
		return false;
	stack->top++;
	void *target = (char *) stack->data + stack->top * stack->elementSize;
	memcpy(target, element, stack->elementSize);
	return true;
}

bool pop(Stack *stack, void *outElement) {
	if(isEmpty(stack))
		return false;
	void *source = (char *) stack->data + stack->top * stack->elementSize;
	memcpy(outElement, source, stack->elementSize);
	stack->top--;
	return true;
}

bool peek(Stack *stack, void *outElement) {
	if(isEmpty(stack))
		return false;
	void *source = (char *) stack->data + stack->top * stack->elementSize;
	memcpy(outElement, source, stack->elementSize);
	return true;
}
