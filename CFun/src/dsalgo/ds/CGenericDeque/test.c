#include <stdio.h>
#include "generic_deque.h"

// Optional free function for complex data types (not needed here for int)
void free_func(void *data) {
    // No dynamic allocation inside int, so nothing to free here.
    // Just a placeholder if you want to use structs or heap data.
}

int main() {
    // Create a deque for int elements
    Deque *dq = deque_create(sizeof(int), free_func);
    if (!dq) {
        printf("Failed to create deque.\n");s
        return 1;
    }

    // Push ints at the back
    for (int i = 1; i <= 5; i++) {
        if (!deque_push_back(dq, &i)) {
            printf("Failed to push %d at back.\n", i);
        }
    }

    // Push int at the front
    int front_val = 0;
    if (!deque_push_front(dq, &front_val)) {
        printf("Failed to push %d at front.\n", front_val);
    }

    // Print elements from front to back
    printf("Deque elements from front to back: ");
    DequeNode *current = dq->front;
    while (current) {
        printf("%d ", *(int *)current->data);
        current = current->next;
    }
    printf("\n");

    // Peek front and back
    int *front_element = (int *)deque_front(dq);
    int *back_element = (int *)deque_back(dq);
    if (front_element) printf("Front element: %d\n", *front_element);
    if (back_element) printf("Back element: %d\n", *back_element);

    // Pop from front
    if (deque_pop_front(dq)) {
        printf("Popped from front.\n");
    }

    // Pop from back
    if (deque_pop_back(dq)) {
        printf("Popped from back.\n");
    }

    // Print elements after pops
    printf("Deque elements after popping front and back: ");
    current = dq->front;
    while (current) {
        printf("%d ", *(int *)current->data);
        current = current->next;
    }
    printf("\n");

    // Clean up
    deque_destroy(dq);

    return 0;
}
