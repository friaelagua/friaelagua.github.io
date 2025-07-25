#include "generic_linked_list.h"
#include <stdio.h>
#include <string.h>

// Internal helper function to create a new node with data copied
static Node *create_node(void *data, size_t data_size) {
	Node *new_node = (Node *) malloc(sizeof(Node));
	if(!new_node) {
		fprintf(stderr, "Failed to allocate memory for node\n");
		return NULL;
	}
	new_node->data = malloc(data_size);
	if(!new_node->data) {
		fprintf(stderr, "Failed to allocate memory for node data\n");
		free(new_node);
		return NULL;
	}
	memcpy(new_node->data, data, data_size);
	new_node->next = NULL;
	return new_node;
}

LinkedList *ll_create(size_t data_size) {
	LinkedList *list = (LinkedList *) malloc(sizeof(LinkedList));
	if(!list) {
		fprintf(stderr, "Failed to allocate memory for linked list\n");
		return NULL;
	}
	list->head = NULL;
	list->data_size = data_size;
	list->size = 0;
	return list;
}

int ll_insert_front(LinkedList *list, void *data) {
	if(!list)
		return 0;
	Node *new_node = create_node(data, list->data_size);
	if(!new_node)
		return 0;
	new_node->next = list->head;
	list->head = new_node;
	list->size++;
	return 1;
}

int ll_insert_end(LinkedList *list, void *data) {
	if(!list)
		return 0;
	Node *new_node = create_node(data, list->data_size);
	if(!new_node)
		return 0;
	if(!list->head) {
		list->head = new_node;
	} else {
		Node *temp = list->head;
		while(temp->next)
			temp = temp->next;
		temp->next = new_node;
	}
	list->size++;
	return 1;
}

int ll_insert_at(LinkedList *list, void *data, size_t position) {
	if(!list || position > list->size)
		return 0;
	if(position == 0)
		return ll_insert_front(list, data);
	if(position == list->size)
		return ll_insert_end(list, data);

	Node *new_node = create_node(data, list->data_size);
	if(!new_node)
		return 0;

	Node *temp = list->head;
	for(size_t i = 0; i < position - 1; i++) {
		temp = temp->next;
	}
	new_node->next = temp->next;
	temp->next = new_node;
	list->size++;
	return 1;
}

int ll_delete_front(LinkedList *list) {
	if(!list || !list->head)
		return 0;
	Node *to_delete = list->head;
	list->head = list->head->next;
	free(to_delete->data);
	free(to_delete);
	list->size--;
	return 1;
}

int ll_delete_end(LinkedList *list) {
	if(!list || !list->head)
		return 0;
	if(!list->head->next) {
		free(list->head->data);
		free(list->head);
		list->head = NULL;
		list->size--;
		return 1;
	}
	Node *temp = list->head;
	while(temp->next && temp->next->next) {
		temp = temp->next;
	}
	free(temp->next->data);
	free(temp->next);
	temp->next = NULL;
	list->size--;
	return 1;
}

int ll_delete_at(LinkedList *list, size_t position) {
	if(!list || position >= list->size)
		return 0;
	if(position == 0)
		return ll_delete_front(list);

	Node *temp = list->head;
	for(size_t i = 0; i < position - 1; i++) {
		temp = temp->next;
	}
	Node *to_delete = temp->next;
	temp->next = to_delete->next;
	free(to_delete->data);
	free(to_delete);
	list->size--;
	return 1;
}

int ll_search(LinkedList *list, void *data,
			  int (*cmp)(const void *, const void *)) {
	if(!list || !cmp)
		return -1;
	Node *temp = list->head;
	int index = 0;
	while(temp) {
		if(cmp(temp->data, data) == 0) {
			return index;
		}
		temp = temp->next;
		index++;
	}
	return -1;
}

void ll_traverse(LinkedList *list, void (*func)(void *)) {
	if(!list || !func)
		return;
	Node *temp = list->head;
	while(temp) {
		func(temp->data);
		temp = temp->next;
	}
}

void ll_free(LinkedList *list, void (*free_func)(void *)) {
	if(!list)
		return;
	Node *temp = list->head;
	while(temp) {
		Node *next = temp->next;
		if(free_func)
			free_func(temp->data);
		else
			free(temp->data);
		free(temp);
		temp = next;
	}
	free(list);
}
