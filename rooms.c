
#include "rooms.h"

Room *room(char *description, Item *items) {

    Room *new_room = NULL;
    new_room = (Room *) malloc(sizeof(Room));

    if (new_room == NULL) {
        printf("malloc failed\n");
        exit(EXIT_FAILURE);
    }

    new_room->description = description;
    new_room->items = items;
    // new_room->connections = {NULL};
    return new_room;
}

Room *add_room(Room *room, Room *new_room, enum direction d) {
    if (d < 0 || 5 < d) {
        return NULL;
    }
    room->connections[d] = new_room;
    new_room->connections[(d+3) % 6] = room;

    return room;
}

void print_room(Room *room) {
    printf("%s \n", room->description);

    // iteration pointer initialization
    Item *dummy_item = room->items;

    printf("inventory: \n");
    while (dummy_item != NULL) {
        printf("%s \n", dummy_item->name);
        ++dummy_item;
    }
    Room *roomcon = room->connections[0];
    printf("%s\n", roomcon->description);
}
