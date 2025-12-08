#include "map.h"

#include <stdio.h>
#include <stdlib.h>

int main(void) {

    Map m = init(1024);

    double d1 = 25.0;
    double d2 = 50.0;

    put(&m, "key1", (void*)&d1);
    put(&m, "key2", (void*)&d2);


    printf("key1=%f;key2=%f\n", *(double*)get(&m, "key1"), *(double*)get(&m, "key2"));

    free(m.buckets);

    return EXIT_SUCCESS;
}
