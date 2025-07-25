#include <stdio.h>
#include <stdlib.h>



typedef struct Node Node;

struct Node {
	int data;
	Node *next;
};



void Stack_Print(Node *top) {
	Node *currentNode=top;
	printf("top->");
	while(currentNode) {
		printf("%d->", currentNode->data);
		currentNode=currentNode->next;
	}
	printf("(NULL)\n");
}



void Stack_Push(Node **top,int data) {
	Node *node=malloc(sizeof(Node));
	node->data=data;
	node->next=(*top);
	(*top)=node;
	printf("%d is pushed\n",data);
}



Node *Stack_Pop(Node **top) {
	Node *node=(*top);
	if(node) {
		int data=node->data;
		(*top)=(*top)->next;
		printf("%d is popped\n",data);
	} else {
		printf("Stack is Empty\n");
	}
	return node;
}



int main(void) {



	// initilize

	Node *top=NULL;


	// push data

	Stack_Push(&top,1);

	Stack_Print(top);

	Stack_Push(&top,2);

	Stack_Print(top);

	Stack_Push(&top,3);

	Stack_Print(top);


	// pop data

	Stack_Pop(&top);

	Stack_Print(top);

	Stack_Pop(&top);

	Stack_Print(top);

	Stack_Pop(&top);

	Stack_Print(top);



	// Empty Pop 

	Stack_Pop(&top);


	return 0;
}


