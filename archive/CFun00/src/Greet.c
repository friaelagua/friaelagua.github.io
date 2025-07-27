#include <stdio.h>

int main(void) {
	char name[32];

	printf("What is your name? ");
	scanf("%19s",name);

	printf("Hello, %s!\n",name);

	return 0;
}
