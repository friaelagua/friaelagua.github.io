#include "generic_linked_list.h"

void print_int(void *data) {
	printf("%d ", *(int *) data);
}

int int_cmp(const void *a, const void *b) {
	int x = *(int *) a;
	int y = *(int *) b;
	return (x > y) - (x < y);
}

int main() {
	LinkedList *list = ll_create(sizeof(int));
	if(!list)
		return 1;

	int nums[] = { 10, 20, 30, 40 };
	for(int i = 0; i < 4; i++) {
		ll_insert_end(list, &nums[i]);
	}

	printf("List contents: ");
	ll_traverse(list, print_int);
	printf("\n");

	int key = 30;
	int pos = ll_search(list, &key, int_cmp);
	if(pos != -1)
		printf("Found %d at position %d\n", key, pos);
	else
		printf("%d not found\n", key);

	ll_free(list, NULL);
	return 0;
}
