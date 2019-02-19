#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// struct declaration
struct typedef room {
  char *description;
  Item *items;
  struct room *north;
  struct room *south;
  struct room *east;
  struct room *west;
  struct room *up;
  struct room *down;
} Room;

// constructor
Room *room(char* description, Item* items, Room *north, Room  *south, Room *east, Room *west, Room *up, Room *down) {
    Room *new_room = NULL;
    new_room = (struct Room *) malloc(sizeof(struct Room));
    new_room->description = description);
    new_room->items = items;






  return new_room;
}

Room *addRoom(Room *room, Room *new_room, direction d) {
    swtich(d){
        case NORTH:
            new_room->north = new_room;
        case EAST:
            new_room->east = new_room;
        case SOUTH:
            new_room->south = new_room;
        case WEST:
            new_room->west = new_room;
        case UP:
            new_room->up = new_room;
        case DOWN:
            new_room->down = new_room;

    }


    if(direction == NORTH){

    } else if (direction == EAST) {

    } else if (direction == SOUTH) {

    }
}
