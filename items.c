
#include "items.h"

/*
 * function: useable_items
 * --------------------------
 * params:
 *      *name             :  the name or identifier of the item
 *		type              :  (char *) C string
 *
 *		*use_room         :  name of the room that the item can be used in
 *		type              :  (char *) C string
 *
 *		*use_description  :  action completed when the item is used
 *		type              :  (char *) C string
 *
 *		*next             :  next link in the item list (used to represent inventories)
 *		type              :  (Item *) pointer to Item struct
 *
 * constructs a new Item struct, represented as a linked list node. Also,
 *      assigns ]the Item an executable message (use_description) when used
 *      in the corresponding room (use_room)
 *
 * returns : pointer to the new struct
 * type	   : (Item *)
 */

Item *useable_items(char *name, char *description, char *use_room, char *use_description, enum item_enum item_enum, Item *next) {
	Item *new_item = NULL;
	new_item = (Item *) malloc(sizeof(Item));

	// checks that dynamic allocation was completed successfully
	if (new_item == NULL) {
		printf("malloc failed\n");
		exit(EXIT_FAILURE);
	}
	// field assignments
	new_item->name = name;
	new_item->description = description;
	new_item->use_room = use_room;
	new_item->use_description = use_description;
	new_item->item_enum = item_enum;
	new_item->next = next;

	return new_item;
}

/*
 * function: items
 * --------------------------
 * psuedo-overloaded constructor
 *
 * same functionality as useable_items but creates an item that
 *      does not directly interact with the game state
 *
 * returns : pointer to the new struct
 * type	   : (Item *)
 */

// accessor methods
Item *items(char *name, char *description, Item *next) {
	return useable_items(name, description, "", "", NONE, next);
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

/*
 * function: add_item
 * --------------------------
 * params:
 *      **list   :  inventory or backpack to be augmented
 *      type     :  (Item **) double pointer to Item struct
 *
 *      *to_add  :	Item to be added to the linked list
 *      type     :  (Item *) pointer to Item struct
 *
 * front insertion, to_add becomes the head of the list,
 *      regardless of whether it is empty or not. Saves memory
 *      by eliminating need for a tail pointer
 *
 * returns : void
 */

void add_item(Item **list, Item *to_add) {
	if (*list == NULL) {
		*list = to_add;
		return;
	}
	to_add->next = *list;
	*list = to_add;
}

/*
 * function: remove_item
 * --------------------------
 * params:
 *      **list   :  inventory or backpack to be reduced
 *      type     :  (Item **) double pointer to Item struct
 *
 *      *object  :	name of Item to be removed from the linked list
 *      type     :  (char *) C string
 *
 * scans the list of Items, updating a staggered pointer (prev) while
 *      checking if the struct pointed to by the iterated (dummy) pointer
 *      contains the desired object. If object is found, it is removed from the list
 *
 * returns : NULL if the inventory is empty or object is not found
             ret_ptr (pointer to the Item being removed)
 */

Item *remove_item(Item **list, char *object) {
	Item *dummy = *list, *prev = NULL, *ret_ptr = NULL;

	// checks if the inventory is empty
	if (dummy == NULL) {
		return NULL;
	}

	//if head has the target node
	if (dummy != NULL && strcmp(dummy->name, object) == 0) {
		ret_ptr = dummy;
		*list = dummy->next;
		dummy->next = NULL;
		return ret_ptr;
	}

	// scans the list until object is found, terminating at the end
	while (dummy != NULL && strcmp(dummy->name, object) != 0) {
		// keeps track of the previous node for removal
		prev = dummy;
		dummy = dummy->next;
	}

	// sets ret_ptr to the Item to be removed
	ret_ptr = prev->next;

	// object is not found
	if (ret_ptr == NULL) {
		return NULL;
	}

	// removal
	prev->next = dummy->next;
	ret_ptr->next = NULL;
	return ret_ptr;
}

// frees a single item from a list: utilized in modifier methods like use
void free_item(Item **to_free) {
	free(*to_free);
	*to_free == NULL;
}

// frees entire item list, to cleanup game state and return all memory to heap
void free_items(Item **list) {
	Item *dummy = *list;
	// backwards recursion to iterate through list
	if (dummy->next != NULL) {
		free_items(&(dummy->next));
	}
	free_item(list);
}

// print method
void list_items(Item **list) {
	if (*list == NULL) {
		printf("->nothing\n");
	}
	Item *dummy = *list;
	while (dummy != NULL) {
		printf("->%s, %s \n", dummy->name, dummy->description);
		dummy = dummy->next;
	}
}
