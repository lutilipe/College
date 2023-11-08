#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

void initMap(struct Map* map) {
    map->pairs = NULL;
    map->size = 0;
}

void insertPair(struct Map* map, const char* key, const char* value) {
    for (size_t i = 0; i < map->size; i++) {
        if (strcmp(map->pairs[i].key, key) == 0) {
            map->pairs[i].num_values++;
            map->pairs[i].values = (char**)realloc(map->pairs[i].values, map->pairs[i].num_values * sizeof(char*));
            map->pairs[i].values[map->pairs[i].num_values - 1] = strdup(value);
            return;
        }
    }

    map->size++;
    map->pairs = (struct Pair*)realloc(map->pairs, map->size * sizeof(struct Pair));
    map->pairs[map->size - 1].key = strdup(key);
    map->pairs[map->size - 1].num_values = 1;
    map->pairs[map->size - 1].values = (char**)malloc(sizeof(char*));
    map->pairs[map->size - 1].values[0] = strdup(value);
}

char** getValuesForKey(struct Map* map, const char* key, size_t* num_values) {
    for (size_t i = 0; i < map->size; i++) {
        if (strcmp(map->pairs[i].key, key) == 0) {
            *num_values = map->pairs[i].num_values;
            return map->pairs[i].values;
        }
    }
    *num_values = 0;
    return NULL;
}

void freeMap(struct Map* map) {
    for (size_t i = 0; i < map->size; i++) {
        free(map->pairs[i].key);
        for (size_t j = 0; j < map->pairs[i].num_values; j++) {
            free(map->pairs[i].values[j]);
        }
        free(map->pairs[i].values);
    }
    free(map->pairs);
    map->size = 0;
}

void listKeys(const struct Map* map) {
    for (size_t i = 0; i < map->size; i++) {
        printf("%s", map->pairs[i].key);
        if (i != map->size - 1) {
            printf("; ");
        } else {
            printf("\n");
        }
    }
}
