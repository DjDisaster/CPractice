#ifndef LIST_H
#define LIST_H

typedef struct List {
	int size;
	struct Element* head;	
} List;

typedef struct Element {
	int value;
	struct Element* next;
} Element;

List* list_create();
void list_add(List* list, int position, int value);
void list_delete(List* list, int position);
int list_get(List* list, int position);
int list_size(List* list);
void list_print(List* list);
void list_destroy(List* list);


#endif
