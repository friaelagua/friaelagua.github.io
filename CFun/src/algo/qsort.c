#include <stdio.h>
#include <stdlib.h>

int cmp(const void *lhs,const void *rhs) {
	return -strcmp(*(char**)lhs,*(char**)rhs);
}

int main() {

	char *names[]={
		"voldemort",
		"harry",
		"ron",
		"hermione",
		"ginny",
		"fleur",
		"snape",
		"dumbledore",
		"hagrid",
		"luna"
	};

	size_t nnames=10;

	qsort(&names,nnames,sizeof(*names),cmp);

	for(int i=0;i<nnames;i++) {
		printf("%s\n",names[i]);
	}

	return 0;
}
