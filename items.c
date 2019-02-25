
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

void item_take(Item **items, char *target) {
    Item *dummy = *items, *prev = NULL;

    // if head has the target node
    if (dummy != NULL && strcmp(dummy->name, target) == 0) {
        *items = dummy->next;
        free(dummy);
        return;
    }

    // traverses the linked list to the desired node
    while (dummy != NULL && strcmp(dummy->name, target) != 0) {
        // keeps track of the previous node for removal
        prev = dummy;
        dummy = dummy->next;
    }

    prev->next = dummy->next;
    free(dummy);
    dummy = NULL;
}

// #ifndef DEBUG
// int main(void) {
//     // initialization
//     Item *itemsRoom1 = items("bronze key", "a dull bronze key",
//                            items("rope", "a leather-bound rope", items("knife", "a rusty shank", NULL)));
//     Item *itemsRoom2 = items("lamp", "ikea lamp",
//                            items("table", "#1 dining table", NULL));
//                            // print before removal
//     printf("before\nname: %s, desc: %s\n", item_name(itemsRoom1), item_description(itemsRoom1));
//     printf("name: %s, desc: %s\n", item_name(itemsRoom1->next), item_description(itemsRoom1->next));
//
//     item_take(&itemsRoom1, "bronze key");
//     // post removal
//     printf("before\nname: %s, desc: %s\n", item_name(itemsRoom1), item_description(itemsRoom1));
//     printf("name: %s, desc: %s\n", item_name(itemsRoom1->next), item_description(itemsRoom1->next));
//
//     return 0;
// }
// #endif
// }
