
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define INVALID -1

/*
 * struct: item
 * ------------
 * models an item in the game environment. Can be used
 *      to alter the state of the room that the player is currently in
 */

// enumerates the useable items in the implementation of this game
enum effect {NONE = -1, USELESS, PRISON_KEY, ORNATE_KEY, CRUDDY_KEY};

typedef struct item {
	char *name;
	char *description;
	char *use_room;
	char *use_description;
	enum effect action;
	struct item *next;
} Item;

// constructors
Item *useable_items(char* name, char* description, char *use_room, char *use_description, enum effect action, Item *next);

Item *items(char* name, char* description, Item *next);

// getter methods
char *item_name(Item *item);

char *item_description(Item *item);

Item *item_next(Item *item);

// item list modifiers
void add_item(Item **list, Item *to_add);

Item *remove_item(Item **list, char *object);

// printer methods
void list_items(Item **list);

// free methods
void free_item(Item **to_free);

void free_items(Item **list);
