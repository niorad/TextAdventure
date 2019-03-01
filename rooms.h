
#include "items.h"

/*
 * struct: room
 * ------------
 * models a room container in the game. Has the identifier name and a textual
 *      representation description. Also has its own inventory that the player
 *      can interact with as well as an array of adjacent rooms
 */

typedef struct room {
	char *name;
	char *description;
	bool locked;
	Item *items;
	struct room *connections[6];
} Room;

/*
 * by having each cardinal direction be (n + 3) % 6 elements
 * away from one's opposite (ex: DOWN, UP) we can save space by using just one enum
 */

enum direction {NORTH, EAST, UP, SOUTH, WEST, DOWN, NODIR};

// constructor
Room *room(char *name, char *description, bool locked, Item *items);

// link rooms based on a passed direction
Room *connect_room(Room *room, Room *other_room, enum direction d);

// prints all available connections from a given room
void list_connections(Room *room);

// prints the room for debugging purposes
// void print_room(Room *room);

void free_room(Room **to_free);

void free_rooms(Room **to_free, enum direction dirfrom);
