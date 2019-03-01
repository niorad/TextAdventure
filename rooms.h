
#include "items.h"
#define LOCKED_ROOM -2

/*
 * struct: room
 * ------------
 * models a room container in the game. Has the identifier 'name'; a textual
 *      representation 'description'; an inventory 'items' that the player
 *      can interact with; a state of being locked 'locked'; and an array of
 * 		adjacent rooms 'connections'
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
 * 		away from one's opposite (ex: DOWN, UP) we can save space by
 * 		using a single enum
 */

// enumerates all possible directions in which a room can have a connection
enum direction {NORTH, EAST, UP, SOUTH, WEST, DOWN, NODIR};

// constructor
Room *room(char *name, char *description, bool locked, Item *items);

// link rooms based on a passed direction
Room *connect_room(Room *room, Room *other_room, enum direction d);

// prints all available connections from a given room
void list_connections(Room *room);

// memory management at the end of the game
void free_room(Room **to_free);

void free_rooms(Room **to_free, enum direction dirfrom);
