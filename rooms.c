
# include "rooms.h"

Room *room(char* description, Item* items) {
    Room *new_room = NULL;
    new_room = (Room *) malloc(sizeof(Room));

    if (new_room == NULL) {
        printf("malloc failed\n");
        exit(EXIT_FAILURE);
    }

    new_room->description = description;
    new_room->items = items;
    return new_room;
}

Room *add_room(Room *room, Room *new_room, enum direction d) {
    switch(d) {
        case NORTH:
            room->north = new_room;
            break;
        case EAST:
            room->east = new_room;
            break;
        case SOUTH:
            room->south = new_room;
            break;
        case WEST:
            room->west = new_room;
            break;
        case UP:
            room->up = new_room;
            break;
        case DOWN:
            room->down = new_room;
            break;
        default:
            printf("Not a valid direction!\n");
            exit(EXIT_FAILURE);

        return room;
    }
}
