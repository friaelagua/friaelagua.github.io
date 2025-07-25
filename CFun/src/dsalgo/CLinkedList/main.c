#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node {
	int data;
	Node *next;
};

void LinkedList_Print(Node *head) {
	Node *currentNode=head;
	printf("head->");
	while(currentNode) {
		printf("%d->", currentNode->data);
		currentNode=currentNode->next;
	}
	printf("(NULL)\n");
}

int main(void) {

	// initilize
	Node *head=NULL;
	Node *one=NULL;
	Node *two=NULL;
	Node *three=NULL;

	// allocate memory
	one=malloc(sizeof(Node));
	two=malloc(sizeof(Node));
	three=malloc(sizeof(Node));

	// assign values
	one->data=1;
	two->data=2;
	three->data=3;

	// connect nodes
	one->next=two;
	two->next=three;
	three->next=NULL;

	// print values
	head=one;
	LinkedList_Print(head);

	return 0;
}


