/*
 * prog: avatar
 * ------------
 *
 *
 *
 *
 *
 */


// getter methods
Item *get_inventory(Avatar *avatar) {
    return avatar->backpack;
}

Room *get_location(Avatar *avatar) {
    return avatar->location;
}

// setter methods
void set_location(Avatar avatar, Room* room){
    avatar->location = room;
}

// adds an item to the backpack
void add_to_inventory(Avatar *avatar, Item *item) {
    item->next = avatar->backpack;
    avatar->backpack = item;
}

//changes the room that the avatar currently is in
void go_to_room(Avatar avatar, enum direction dir) {
    Room *room = get_location(avatar);
    // determines the desired direction and executes the appropriate function
    switch (dir) {
        case NORTH:
            set_location(avatar, room->north);
        case EAST:
            set_location(avatar, room ->east);
        case SOUTH:
            set_location(avatar, room->south);
        case WEST:
            set_location(avatar, room->west);
        case UP:
            set_location(avatar, room->up);
        case DOWN:
            set_location(avatar, room->down);
        default:
            printf("not a valid room");
            exit(EXIT_FAILURE);
    }
}
