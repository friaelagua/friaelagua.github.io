#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int asccmp(const void *a, const void *b) {
  const char *str1 = *(const char **)a;
  const char *str2 = *(const char **)b;
  return strcmp(str1, str2);
}

int main() {
    char *fruits[] = {"banana","grape","pear","apple","orange"};
    int nfruits = sizeof(fruits) / sizeof(*fruits);

		qsort(&fruits,nfruits,sizeof(*fruits),asccmp);

    char *key = "grape";

    char **found = (char **)bsearch(
        &key,
        fruits,
        nfruits,
        sizeof(*fruits),
      	asccmp
    );

    if (found != NULL) {
        printf("Found: %s\n", *found);
    } else {
        printf("Not found.\n");
    }

    return 0;
}