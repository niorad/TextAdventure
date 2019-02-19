#include <items.h>
#include <string.h>


Item *item(char* name, char* description) {
    Item *new_item = NULL;
    new_item = (struct Item *) malloc(sizeof(Item));
    // assign the passed variables
    new_item->name = name;
    new_item->description = description;
    return new_item;
}

char *item_name(Item *item) {
  return item->name;
}

char *item_description(Item *item) {
  return item->description;
}

void item_take(Item *items[], char *target) {
    for (int i = 0; i < sizeof(items) / sizeof(Item))
}




Item *itemArray()
