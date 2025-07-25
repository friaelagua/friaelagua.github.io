#ifndef MAP_H
#define MAP_H

#include <stddef.h>
#include <assert.h>

typedef struct Map {
	size_t size;
	size_t cap;
	void **buckets;
} Map;

size_t hash(Map *m, char *str);
Map init(size_t cap);
void put(Map *m, char *str, void *value);
void *get(Map *m, char *str);

#endif /* HASH_MAP */
