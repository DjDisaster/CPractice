#include "HashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

unsigned long hash_string(const char *key) {

	unsigned long hash = 5381;

	while (*key != '\0') {
		hash = hash * 33 + (unsigned char)*key;
		key++;
	}

	return hash;
}


HashMap* hashmap_create(int capacity) {

	if (capacity <= 0) {
		fprintf(stderr, "Hashmap could not be created, capacity must be atleast 1.");
		return NULL;
	}

	HashMap* hashmap = malloc(sizeof(HashMap));

	if (hashmap == NULL) {
		fprintf(stderr, "Unknown Error creating hashmap.");
		return NULL;
	}	
	hashmap->capacity = capacity;
	hashmap->size = 0;
	hashmap->buckets = calloc(capacity, sizeof(Entry*));

	if (hashmap->buckets == NULL) {
		fprintf(stderr, "Unknwon error creating buckets for HashMap.");
		return NULL;
	}

	return hashmap;
}

int hashmap_toBucket(HashMap* map, unsigned long hash) {
	if (map == NULL) {
		fprintf(stderr, "hashmap_toBucket called on a null bucket.");
		return -1;
	}
	return hash % map->capacity;
}

void hashmap_set(HashMap* map, const char* key, int value) {
    if (map == NULL) {
        fprintf(stderr, "hashmap_set called with a NULL map.\n");
        return;
    }

    if (key == NULL) {
        fprintf(stderr, "hashmap_set called with a NULL key.\n");
        return;
    }

    unsigned long hash = hash_string(key);
    int bucket = hashmap_toBucket(map, hash);

    if (bucket < 0) {
        fprintf(stderr, "hashmap_set ran into negative bucket number.\n");
        return;
    }

    Entry* entry = map->buckets[bucket];

    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            entry->value = value;
            return;
        }

        entry = entry->next;
    }

    Entry* newEntry = malloc(sizeof(Entry));

    if (newEntry == NULL) {
        fprintf(stderr, "Could not allocate a new entry for HashMap.\n");
        return;
    }

    newEntry->key = malloc(strlen(key) + 1);

    if (newEntry->key == NULL) {
        fprintf(stderr, "Could not allocate memory for key.\n");
        free(newEntry);
        return;
    }

    strcpy(newEntry->key, key);

    newEntry->value = value;
    newEntry->next = map->buckets[bucket];

    map->buckets[bucket] = newEntry;
    map->size++;
}

int hashmap_get(HashMap* map, const char* key, int* value) {	
	if (map == NULL) {
		fprintf(stderr, "hashmap_get called with a NULL map.");
		return -1;
	}

	if (key == NULL) {
		fprintf(stderr, "hashmap_get called with a NULL key.");
		return -1;
	}

	if (value == NULL) {
		fprintf(stderr, "hashmap_get called with a NULL value.");
		return -1;
	}


	unsigned long hash = hash_string(key);
	int bucket = hashmap_toBucket(map, hash);

	if (bucket < 0) {
		fprintf(stderr, "hashmap_get ran into negative bucket number.");
		return -1;
	}

	Entry* entry = map->buckets[bucket];

	while (entry != NULL) {
		if (strcmp(entry->key, key) == 0) {
			*value = entry->value;
			return 1;
		}

		entry = entry->next;
	}
	
	return 0;
}


int hashmap_delete(HashMap* map, const char* key) {

    if (map == NULL) {
        fprintf(stderr, "hashmap_delete called with a NULL map.\n");
        return -1;
    }

    if (key == NULL) {
        fprintf(stderr, "hashmap_delete called with a NULL key.\n");
        return -1;
    }

    unsigned long hash = hash_string(key);
    int bucket = hashmap_toBucket(map, hash);

    if (bucket < 0) {
        fprintf(stderr, "hashmap_delete ran into negative bucket number.\n");
        return -1;
    }

    Entry* entry = map->buckets[bucket];
    Entry* previous = NULL;

    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {

            if (previous == NULL) {
                map->buckets[bucket] = entry->next;
            } else {
	        previous->next = entry->next;
            }

            free(entry->key);
            free(entry);
            map->size--;

            return 1;
        }

        previous = entry;
        entry = entry->next;
    }

    return 0;
}


void hashmap_destroy(HashMap* map) {

	if (map == NULL) {
		fprintf(stderr, "hashmap_destroy called with NULL as hashmap.");
		return;
	}

	int size = map->capacity;
	for (int i = 0; i < size; i++) {
		Entry* entry = map->buckets[i];
		
		while (entry != NULL) {
			Entry* next = entry->next;

			free(entry->key);
			free(entry);

			entry = next;
		}

	}
	free(map->buckets);
	free(map);
}

