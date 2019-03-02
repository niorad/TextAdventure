
#include "items.h"

/*
 * function: useable_items
 * --------------------------
 * params:
 *      *name             :  the name or identifier of the item
 *		type              :  (char *) C string
 *
 *		*description      :  the description of the item
 *		type              :  (char *) C string
 *
 *		*use_room         :  name of the room that the item can be used in
 *		type              :  (char *) C string
 *
 *		*use_description  :  action completed when the item is used
 *		type              :  (char *) C string
 *
 *		action            :  use case corresponding to the item
 *		type              :  enum effect
 *
 *		*next             :  next link in the item list (used to represent inventories)
 *		type              :  (Item *) pointer to Item struct
 *
 * constructs a new Item struct, represented as a linked list node. Also,
 *      assigns the Item an executable message (use_description) when used
 *      in the corresponding room (use_room). action is a number that
 * 		relates to the appropriate function to be executed upon the use of this item
 *
 * returns : pointer to the new struct
 * type	   : (Item *)
 */

Item *useable_items(char *name, char *description, char *use_room, char *use_description, enum effect action, Item *next) {
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
	new_item->action = action;
	new_item->next = next;

	return new_item;
}

/*
 * function: items
 * --------------------------
 * psuedo-overloaded constructor
 * params:
 *      *name             :  the name or identifier of the item
 *		type              :  (char *) C string
 *
 *		*description      :  the description of the item
 *		type              :  (char *) C string
 *
 *		*next             :  next link in the item list (used to represent inventories)
 *		type              :  (Item *) pointer to Item struct
 *
 * same functionality as useable_items but creates an item that
 *      does not directly interact with the game state (action == NONE)
 *
 * returns : pointer to the new struct
 * type	   : (Item *)
 */

Item *items(char *name, char *description, Item *next) {
	return useable_items(name, description, "", "", NONE, next);
}

// accessor methods
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
	// if list is empty, to_add next is NULL
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
 *           target_ptr (pointer to the Item being removed)
 */

Item *remove_item(Item **list, char *object) {
	Item *dummy = *list, *prev = NULL, *target_ptr = NULL;

	// checks if the inventory is empty
	if (dummy == NULL) {
		return NULL;
	}

	//if head has the target node
	if (dummy != NULL && strcmp(dummy->name, object) == 0) {
		target_ptr = dummy;
		// removal involves simply setting the head to the next node
		*list = dummy->next;
		dummy->next = NULL;
		return target_ptr;
	}

	// scans the list until object is found, terminating at the end
	while (dummy != NULL && strcmp(dummy->name, object) != 0) {
		// keeps track of the previous node for removal
		prev = dummy;
		dummy = dummy->next;
	}

	// sets target_ptr to the Item to be removed
	target_ptr = prev->next;

	// object is not found
	if (target_ptr == NULL) {
		return NULL;
	}

	// removal
	prev->next = dummy->next;
	target_ptr->next = NULL;

	/*
	 * do not free in this method because object may still be required
	 * 		in other functions where remove_item is utilized
	 */

	return target_ptr;
}

/*
 * function: list_items
 * --------------------
 * params:
 *      **list  :  head of the list of Items to be printed out
 *		type    :  (Item **) pointer to a pointer of an Item struct
 *
 * prints out the names of the items in **list as well as their descriptions
 *
 * returns : void
 */

void list_items(Item **list) {
	// if the list is empty
	if (*list == NULL) {
		printf("->nothing\n");
	}

	// iteration till the end of the list
	Item *dummy = *list;
	while (dummy != NULL) {
		printf("->%s, %s \n", dummy->name, dummy->description);
		dummy = dummy->next;
	}
}

/*
 * function: free_item
 * -------------------
 * params:
 *      **to_free  :  item to be freed
 *		type       :  (Item **) pointer to a pointer of an Item struct
 *
 * frees the item then sets its pointer to NULL
 *
 * returns : void
 */

void free_item(Item **to_free) {
	free(*to_free);
	*to_free == NULL;
}

/*
 * function: free_items
 * --------------------
 * params:
 *      **list  :  head of the list of items to be freed
 *		type    :  (Item **) pointer to a pointer of an Item struct
 *
 * recursively calls itself to free the whole list using free_item calls
 *
 * returns : void
 */

void free_items(Item **list) {
	// base case: list is empty
	if (*list == NULL) {
		return;
	}

	// backwards recursion to iterate through list
	free_items(&((*list)->next));
	free_item(list);
}
