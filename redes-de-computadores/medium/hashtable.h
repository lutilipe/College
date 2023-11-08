#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdbool.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Pair {
    char* key;
    char** values;
    size_t num_values;
};

struct Map {
    struct Pair* pairs;
    size_t size;
};

void initMap(struct Map* map);

void insertPair(struct Map* map, const char* key, const char* value);

char** getValuesForKey(struct Map* map, const char* key, size_t* num_values);

void freeMap(struct Map* map);

void listKeys(const struct Map* map);

#endif
