#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct item{
    char *name;
    char *description;
} Item;

// constructor
Item *item(char* name, char* description);

// getter methods
char *item_name(Item *item);
char *item_description(Item *item);

// retrives an item from an array of Item structs
void item_take(Item *item[], char *target);
