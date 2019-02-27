
#include "items.h"

enum direction {NORTH, EAST, UP,SOUTH, WEST, DOWN};

/*
 * by having each cardinal direction be (n + 3 % 6) elements
 * away from one's opposite we can save space by using just one enum
 */

// struct declaration
typedef struct room {
	char *description;
	Item *items;
	struct room *connections[6];
} Room;

// constructor
Room *room(char* description, Item* items);

// link rooms based on a passed direction
Room *connect_room(Room *room, Room *other_room, enum direction d);

// prints all available connections from a given room 
void list_connections(Room *room);

// prints the room for debugging purposes
void print_room(Room *room);
