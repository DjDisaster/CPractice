#ifndef HASHMAP_H
#define HASHMAP_H


typedef struct Entry {
	char* key;
	int value;
	struct Entry* next;
} Entry;

typedef struct HashMap {
	int capacity;
	int size;
	Entry** buckets;
} HashMap;

unsigned long hash_string(const char *key);
HashMap* hashmap_create(int capacity);
int hashmap_toBucket(HashMap* map, unsigned long hash);
void hashmap_set(HashMap* map, const char* key, int value);
int hashmap_get(HashMap* map, const char* key, int* value);
int hashmap_delete(HashMap* map, const char* key);
void hashmap_destroy(HashMap* map);
#endif
