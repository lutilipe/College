#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

void init_map(struct Map* map) {
    map->pairs = NULL;
    map->size = 0;
}

void insert_pair(struct Map* map, const char* key, const char* value) {
    for (size_t i = 0; i < map->size; i++) {
        if (strcmp("", value) != 0 && strcmp(map->pairs[i].key, key) == 0) {
            map->pairs[i].num_values++;
            map->pairs[i].values = (char**)realloc(map->pairs[i].values, map->pairs[i].num_values * sizeof(char*));
            map->pairs[i].values[map->pairs[i].num_values - 1] = strdup(value);
            return;
        }
    }

    map->size++;
    map->pairs = (struct Pair*)realloc(map->pairs, map->size * sizeof(struct Pair));
    map->pairs[map->size - 1].key = strdup(key);
    if (strcmp("", value) != 0) {
        map->pairs[map->size - 1].num_values = 1;
        map->pairs[map->size - 1].values = (char**)malloc(sizeof(char*));
        map->pairs[map->size - 1].values[0] = strdup(value);
    } else {
        map->pairs[map->size - 1].num_values = 0;
    }
}

void free_map(struct Map* map) {
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

char** list_keys(const struct Map* map) {
    char** keysArray = (char**)malloc(map->size * sizeof(char*));
    
    for (size_t i = 0; i < map->size; i++) {
        keysArray[i] = strdup(map->pairs[i].key);
    }

    return keysArray;
}

int has_key(const struct Map* map, const char* key) {
    for (size_t i = 0; i < map->size; i++) {
        if (strcmp(map->pairs[i].key, key) == 0) {
            return 1;
        }
    }
    return 0;
}

int has_value(const struct Map* map, const char* key, const char* value) {
    for (size_t i = 0; i < map->size; i++) {
        if (strcmp(map->pairs[i].key, key) == 0) {
            for (size_t j = 0; j < map->pairs[i].num_values; j++) {
                if (strcmp(map->pairs[i].values[j], value) == 0) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

void remove_value(struct Map* map, const char* key, const char* value) {
    for (size_t i = 0; i < map->size; i++) {
        if (strcmp(map->pairs[i].key, key) == 0) {
            for (size_t j = 0; j < map->pairs[i].num_values; j++) {
                if (strcmp(map->pairs[i].values[j], value) == 0) {
                    free(map->pairs[i].values[j]);
                    for (size_t k = j; k < map->pairs[i].num_values - 1; k++) {
                        map->pairs[i].values[k] = map->pairs[i].values[k + 1];
                    }
                    map->pairs[i].num_values--;
                    map->pairs[i].values = (char**)realloc(map->pairs[i].values, map->pairs[i].num_values * sizeof(char*));
                    return;
                }
            }
        }
    }
}

void remove_value_from_all(struct Map* map, const char* value) {
    for (size_t i = 0; i < map->size; i++) {
        for (size_t j = 0; j < map->pairs[i].num_values; j++) {
            if (strcmp(map->pairs[i].values[j], value) == 0) {
                free(map->pairs[i].values[j]);
                for (size_t k = j; k < map->pairs[i].num_values - 1; k++) {
                    map->pairs[i].values[k] = map->pairs[i].values[k + 1];
                }
                map->pairs[i].num_values--;
                map->pairs[i].values = (char**)realloc(map->pairs[i].values, map->pairs[i].num_values * sizeof(char*));
                break;
            }
        }
    }
}

char** get_values(const struct Map* map, const char* key) {
    for (size_t i = 0; i < map->size; i++) {
        if (strcmp(map->pairs[i].key, key) == 0) {
            return map->pairs[i].values;
        }
    }

    return NULL;
}
