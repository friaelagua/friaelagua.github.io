#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void shuffle(int a[],size_t n) {
	for(int i=n-1;i>0;i--) {
		int j=rand()%(i+1);
		int tmp=a[i];
		a[i]=a[j];
		a[j]=tmp;
	}
}

int main() {

	int a[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	size_t n = 10;

	srand(time(NULL));

	shuffle(a,n);

	for(int i=0;i<n;i++) {
		printf("%d ",a[i]);
	}
	printf("\n");

	return 0;
}
