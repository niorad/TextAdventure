
#include "rooms.h"

typedef struct avatar {
    Room *location;
    Item *backpack;
} Avatar;

// constructor
Avatar *avatar(Room *location, Item *backpack) {
    Avatar *new_avatar = NULL;
    new_avatar = (Avatar *) malloc(sizeof(Avatar));

    if (new_sprite == NULL) {
        printf("malloc failed\n");
        exit(EXIT_FAILURE);
    }

    new_avatar->location = location;
    new_avatar->backpack = backpack;
    return new_room;
}

// getters
Room *get_location(Avatar *avatar);

Item *get_inventory(Avatar *avatar);

// setters
void *set_location(Avatar *avatar);

//void *set_inventory(Avatar *avatar);
