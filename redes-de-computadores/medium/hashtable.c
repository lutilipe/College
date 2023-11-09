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

char* listKeys(const struct Map* map) {
    size_t totalLength = 0;
    for (size_t i = 0; i < map->size; i++) {
        totalLength += strlen(map->pairs[i].key);
        if (i != map->size - 1) {
            totalLength += 2;
        }
    }

    char* keysString = (char*)malloc(totalLength + 1);

    keysString[0] = '\0';
    for (size_t i = 0; i < map->size; i++) {
        strcat(keysString, map->pairs[i].key);
        if (i != map->size - 1) {
            strcat(keysString, ";");
        }
    }

    return keysString;
}

/* int main() {
    struct Map map;
    initMap(&map);

    insertPair(&map, "key1", "value1");
    insertPair(&map, "key2", "value2");
    insertPair(&map, "key1", "value3");

    printf("%s\n", listKeys(&map));

    freeMap(&map);

    return 0;
} */