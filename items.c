
#include "items.h"

Item *items(char* name, char* description, Item *next) {
	Item *new_item = NULL;
	new_item = (Item *) malloc(sizeof(Item));
	if (new_item == NULL) {
		printf("malloc failed\n");
		exit(EXIT_FAILURE);
	}
	// assign the passed variables
	new_item->name = name;
	new_item->description = description;
	new_item->next = next;
	return new_item;
}

char *item_name(Item *item) {
	return item->name;
}

char *item_description(Item *item) {
	return item->description;
}

Item *item_next(Item *item) {
	return item->next;
}

void add_item(Item **list, Item *to_add) {
	if (*list == NULL) {
		*list = to_add;
		return;
	}
	to_add->next = *list;
}

Item *remove_item(Item **list, char *object) {
	Item *dummy = *list, *prev = NULL, *ret_ptr = NULL;

	//if head has the target node
	if (dummy != NULL && strcmp(dummy->name, object) == 0) {
		ret_ptr = dummy;
		*list = dummy->next;
		return ret_ptr;
	}

	while (dummy != NULL && strcmp(dummy->name, object) != 0) {
		// keeps track of the previous node for removal
		prev = dummy;
		dummy = dummy->next;
	}

	ret_ptr = prev->next;
	prev->next = dummy->next;
	// if object is not found, returns NULL
	return ret_ptr;
}

void list_items(Item **list) {
	Item *dummy = *list;
	while (dummy != NULL) {
		printf("%s: %s\n", dummy->name, dummy->description);
		dummy = dummy->next;
	}
}
