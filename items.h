
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct item {
	char *name;
	char *description;
	struct item *next;
} Item;

// constructor
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
