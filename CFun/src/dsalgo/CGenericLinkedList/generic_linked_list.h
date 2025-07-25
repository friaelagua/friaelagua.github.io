#ifndef GENERIC_LINKED_LIST_H
#define GENERIC_LINKED_LIST_H

#include <stdlib.h>

// Node structure for generic singly linked list
typedef struct Node {
	void *data;					// Pointer to data of any type
	struct Node *next;			// Pointer to next node
} Node;

// Linked List structure to hold head pointer and size
typedef struct LinkedList {
	Node *head;
	size_t data_size;			// Size of the data type stored
	size_t size;				// Number of nodes in list
} LinkedList;

// Create a new linked list with data size specified
LinkedList *ll_create(size_t data_size);

// Insert at the beginning of the list
int ll_insert_front(LinkedList * list, void *data);

// Insert at the end of the list
int ll_insert_end(LinkedList * list, void *data);

// Insert at a specific position (0-based index)
int ll_insert_at(LinkedList * list, void *data, size_t position);

// Delete node from the beginning
int ll_delete_front(LinkedList * list);

// Delete node from the end
int ll_delete_end(LinkedList * list);

// Delete node at a specific position
int ll_delete_at(LinkedList * list, size_t position);

// Search for data in the list using a comparator function
// Returns 0-based index or -1 if not found
int ll_search(LinkedList * list, void *data,
			  int (*cmp)(const void *, const void *));

// Traverse the list and apply function to each data element
void ll_traverse(LinkedList * list, void (*func)(void *));

// Free the entire list, using an optional free_func to release data if needed
void ll_free(LinkedList * list, void (*free_func)(void *));

#endif // GENERIC_LINKED_LIST_H
