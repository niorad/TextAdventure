
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>



typedef struct item {
	char *name;
	char *description;
	char *use_room;
	char *use_description;
	struct item *next;
} Item;

// constructor
Item *useable_items(char* name, char* description, char *use_room, char *use_description, Item *next);

Item *items(char* name, char* description, Item *next);

// getter methods
char *item_name(Item *item);
char *item_description(Item *item);
Item *item_next(Item *item);

// item list modifiers
void add_item(Item **list, Item *to_add);
Item *remove_item(Item **list, char *object);

// free methods
void free_item(Item **to_free);
void free_items(Item **list);

// printer methods
void list_items(Item **list);
