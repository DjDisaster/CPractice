#include "List.h"
#include <stdlib.h>
#include <stdio.h>

struct List* list_create() {
	List* list = malloc(sizeof(List));
	
	if (list == NULL) {
		return NULL;
	}
	
	list->size = 0;
	list->head = NULL;

	return list;
}

void list_add(List* list, int position, int value) {
	
	if (list == NULL) {
		fprintf(stderr, "list_add called with NULL list.\n");
		return;
	}

	if (position < 0) {
		fprintf(stderr, "list_add called with negative value of: %d\n", value);
		return;
	}

	
	if (position > list->size) {
		fprintf(stderr, "list_add called with value out of bounds %d out of 0-%d", position, list->size);
		return;
	}



	Element* element = list->head;

	for (int i = 0; i < position-1; i++) {
		if (element == NULL) {
			fprintf(stderr, "Could not append element to list, size of %d is out of bounds 0-%d\n", position, list_size(list)-1);
			return;
		}
		element = element->next;
	}

	Element* newElement = malloc(sizeof(Element));
	newElement->value = value;

	list->size++;

	if (position == 0) {
		newElement->next = list->head;
		list->head = newElement;
		return;
	}	
	
	newElement->next = element->next;
	element->next = newElement;
}

void list_delete(List* list, int position) {

	if (list == NULL) {
		fprintf(stderr, "list_delete was ran with null.\n");
		return;
	}

	if (position < 0) {
		fprintf(stderr, "list_delete called with negative value of: %d\n", position);
		return;
	}

	if (position > list->size) {
		fprintf(stderr, "list_delete called with value out of bounds %d out of 0-%d", position, list->size);
		return;
	}



	Element* element = list->head;


	if (element == NULL) {
		fprintf(stderr, "Could not delete element at position %d from list - out of bounds, size: %d\n", position, list->size-1);
		return;
	}


	if (position == 0) {
		Element* deleteElement = list->head;
		list->head = deleteElement->next;
		free(deleteElement);
		list->size--;
		return;
	}

	for (int i = 0; i < position-1; i++) {
		if (element == NULL) {
			fprintf(stderr, "Could not delete element at position %d from list - out of bounds, size: %d\n", position, list->size-1);
			return;
		}
		element = element->next;
	}

	if (element->next == NULL) {
		fprintf(stderr, "Failed to delete element, element at %d out of bounds, list size: %d\n", position, list->size-1);
		return;
	}

	Element* deleteElement = element->next;
	element->next = deleteElement->next;
	list->size--;
	free(deleteElement);
}


int list_get(List* list, int position) {
	
	if (list == NULL) {
		fprintf(stderr, "Called list_get with NULL for list arg.\n");
		return -1;
	}

	if (position < 0) {
		fprintf(stderr, "Called list_get with negative value of: %d\n", position);
		return -1;
	}

	
	Element* element = list->head;

	if (element == NULL) {
		fprintf(stderr, "Could not read element from list, size of %d is out of bounds 0-%d\n", position, list_size(list)-1);
		return -1;
	}

	for (int i = 0; i < position; i++) {
		if (element == NULL) {
			fprintf(stderr, "Could not read element from list, size of %d is out of bounds 0-%d\n", position, list_size(list)-1);
			return -1;
		}

		element = element->next;	
	}

	return element->value;
}

int list_size(List* list) {

	if (list == NULL) {
		fprintf(stderr, "Called list_size with list arg as NULL.\n");
		return -1;
	}

	return list->size;
}


void list_print(List* list) {

	if (list == NULL) {
		fprintf(stderr, "Called list_print with list arg as NULL.\n");
		return;
	}

	printf("\n");
	printf("-----------------------------------------------------------------\n");
	printf("List Size: %d\n", list->size);
	printf("\n");
	printf("%-14s     %-20s      %-25s\n", "Element Number", "Element Value", "Next Reference");
	int ln = 0;
	for (Element* element = list->head; element != NULL; element = element->next) {
		printf("%-14d     %-25d %-25p\n", ln, element->value, element->next);
		ln++;
	}
	printf("-----------------------------------------------------------------");
	printf("\n");

}

void list_destroy(List* list) {

	if (list == NULL) {
		fprintf(stderr, "Attempted to delete an empty list.\n");
		return;
	}

	Element* element = list->head;

	while (element != NULL) {
		Element* next = element->next;
		free(element);
		element = next;
	}

	free(list);
}
