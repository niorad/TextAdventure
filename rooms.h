
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "items.h"

enum direction {NORTH, SOUTH, EAST, WEST, UP, DOWN};

// struct declaration
typedef struct room {
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
Room *room(char* description, Item* items);

Room *addRoom(Room *room, Room *new_room, enum direction d);
