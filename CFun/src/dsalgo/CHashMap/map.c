#include "map.h"

#include <stdlib.h>

const size_t BASE = 0x811c9dc5;
const size_t PRIME = 0x01000193;

size_t hash(Map *m, char *str) {
	size_t initial = BASE;
	while(*str) {
		initial ^= *str++;
		initial *= PRIME;
	}
	return initial & (m->cap - 1);
}

Map init(size_t cap) {
	Map m = { 0, cap };
	m.buckets = malloc(sizeof(void *) * m.cap);
	assert(m.buckets != NULL);
	return m;
}

void put(Map *m, char *str, void *value) {
	m->size++;
	m->buckets[hash(m, str)] = value;
}

void *get(Map *m, char *str) {
	return m->buckets[hash(m, str)];
}
