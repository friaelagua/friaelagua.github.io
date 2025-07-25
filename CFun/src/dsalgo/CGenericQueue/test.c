#include "generic_queue.h"

#include <stdio.h>

int main() {
	GenericQueue *q = createQueue(5, sizeof(int));
	if(!q) {
		printf("Failed to create queue\n");
		return 1;
	}

	int values[] = { 10, 20, 30, 40, 50 };
	for(int i = 0; i < 5; i++) {
		if(!enqueue(q, &values[i])) {
			printf("Queue is full, failed to enqueue %d\n", values[i]);
		}
	}

	int x;
	while(!isEmpty(q)) {
		if(dequeue(q, &x)) {
			printf("Dequeued: %d\n", x);
		}
	}

	destroyQueue(q);
	return 0;
}
