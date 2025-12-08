#include "generic_stack.h"

#include <stdio.h>

int main() {
	Stack *intStack = createStack(10, sizeof(int));
	int val = 42;
	push(intStack, &val);

	int poppedVal;
	if(pop(intStack, &poppedVal)) {
		printf("Popped: %d\n", poppedVal);
	}

	freeStack(intStack);
	return 0;
}
