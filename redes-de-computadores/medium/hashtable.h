#ifndef HASHTABLE_H
#define HASHTABLE_H

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

void init_map(struct Map* map);

void insert_pair(struct Map* map, const char* key, const char* value);

void free_map(struct Map* map);

char** list_keys(const struct Map* map);

int has_key(const struct Map* map, const char* key);

int has_value(const struct Map* map, const char* key, const char* value);

void remove_value(struct Map* map, const char* key, const char* value);

char** get_values(const struct Map* map, const char* key);

#endif
