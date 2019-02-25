
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "items.h"

/* by having each cardinal direction be (n + 3 % 6) elements away from one's opposite
   we can save space by using one enum */
enum direction {NORTH, EAST, UP ,SOUTH, WEST, DOWN};

// struct declaration
typedef struct room {
  char *description;
  Item *items;
  struct room *connections[6];
} Room;

// constructor
Room *room(char* description, Item* items);

// link rooms based on a passed direction
Room *add_room(Room *room, Room *new_room, enum direction d);

// prints the room for debugging purposes
void print_room(Room *room);
