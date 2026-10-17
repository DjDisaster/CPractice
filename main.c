#include <stdio.h>
#include "List.h"
#include "HashMap.h"

int main() {


	HashMap* map = hashmap_create(16);

	hashmap_set(map, "test", 5);
	
	//hashmap_delete(map, "test");
	int value;
	int test = hashmap_get(map, "test", &value);

	printf("test: %d", value);

	hashmap_destroy(map);
	map = NULL;

	return 0;
}


