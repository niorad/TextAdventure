#include "avatar.h"

/*
 * prog: avatar
 * ------------
 */

Avatar *avatar(Room *location, Item *backpack) {
    Avatar *new_avatar = NULL;
    new_avatar = (Avatar *) malloc(sizeof(Avatar));
    // checking for null location, doesn't need to be in final build
    #IFDEF DEBUG
    if (location == NULL) {
        printf("WARNING: avatar's location not set");
    }
    #ENDIF
    if (new_avatar == NULL) {
        printf("malloc failed\n");
        exit(EXIT_FAILURE);
    }

    new_avatar->location = location;
    new_avatar->backpack = backpack;
    return new_avatar;
 }

Item *get_inventory(Avatar *avatar) {
    return avatar->backpack;
}

Room *get_location(Avatar *avatar) {
    return avatar->location;
}

void set_location(Avatar *avatar, Room* room){
    avatar->location = room;
}

void add_to_inventory(Avatar *avatar, Item *item) {
    item->next = avatar->backpack;
    avatar->backpack = item;
}

int go_to_room(Avatar *avatar, enum direction dir) {
    // determines the desired direction and executes the appropriate function
    Room *room = get_location(avatar);
    if (room->connections[dir] == NULL) return -1;
    set_location(avatar, room->connections[dir]);
    return 0;
}
