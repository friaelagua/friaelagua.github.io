#include <stdio.h>
#include <stdlib.h>



typedef struct Node Node;

struct Node {
	int data;
	Node *next;
};



size_t Queue_Length(Node *head) {
	Node *currentNode=head;
	size_t n=0;
	while(currentNode) {
		n++;
		currentNode=currentNode->next;
	}
	return n;
}



void Queue_Print(Node *head) {
	Node *currentNode=head;
	printf("back->");
	while(currentNode) {
		printf("%d->", currentNode->data);
		currentNode=currentNode->next;
	}
	printf("front  ");
	printf("Length: %zu\n",Queue_Length(head));
}



void Queue_Enqueue(Node **head,int data) {
	Node *node=malloc(sizeof(Node));
	node->data=data;
	node->next=(*head);
	(*head)=node;
	printf("%d enqueued\n",data);
}



Node *Queue_Dequeue(Node **head) {
	Node *currentNode=(*head);
	Node *node=NULL;
	if(currentNode) {
		if(currentNode->next) {
			while(currentNode->next) {
				node=currentNode;
				currentNode=currentNode->next;
			}
			node->next=currentNode->next;
		} else {
			(*head)=currentNode->next;
		}
		printf("%d dequeued\n",currentNode->data);
	} else {
		printf("Empty Queue\n");
	}
	return currentNode;
}



int main(void) {



	// initilize

	Node *head=NULL;
	Node *dequeued=NULL;



	// Enqueue data

	Queue_Enqueue(&head,1);

	Queue_Print(head);

	Queue_Enqueue(&head,2);

	Queue_Print(head);

	Queue_Enqueue(&head,3);

	Queue_Print(head);



	// Dequeue data

	dequeued=Queue_Dequeue(&head);

	Queue_Print(head);

	dequeued=Queue_Dequeue(&head);

	Queue_Print(head);

	dequeued=Queue_Dequeue(&head);

	Queue_Print(head);



	// Empty Dequeue

	dequeued=Queue_Dequeue(&head);

	
	return 0;
}


