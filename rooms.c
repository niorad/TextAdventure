
#include "rooms.h"

/*
 * function: room
 * --------------------------
 * constructs a new Room struct given the passed specifications
 *      acts as a container within the game state
 * params:
 *      *name         :  the room's identifier in the backend
 *		type          :  (char *) C string
 *
 *      *description  :  textual (visual) representation in the frontend
 *		type          :  (char *) C string
 *
 *		*items        :  dynamically allocated list of items contained within the room
 *		type          :  (Item *) pointer to Item struct
 *
 * returns : pointer to the new struct
 * type	   : (Room *)
 */

Room *room(char *name, char *description, bool locked, Item *items) {
	Room *new_room = NULL;
	new_room = (Room *) malloc(sizeof(Room));

	if (new_room == NULL) {
		printf("malloc failed\n");
		exit(EXIT_FAILURE);
	}
	new_room->name = name;
	new_room->description = description;
	new_room->locked = locked;
	new_room->items = items;
	return new_room;
}

/*
 * function: connect_room
 * --------------------------
 * params:
 *      *room        :  room whose d connection is to be set
 *		type         :  (Room *) pointer to Room struct
 *
 *      *other_room  :  room whose opposite (d + 3) % 6 connection is to be set
 *		type         :  (Room *) pointer to Room struct
 *
 *		*items       :  dynamically allocated list of items contained within the room
 *		type         :  (Item *) pointer to Item struct
 *
 * relates two rooms based on a passed cardinal direction;
 *      used primarily in hard-coded (OR JSON) game setup
 * ex:  connect_room(a, c, NORTH), connect_room(b, a, EAST), connect_room(a, d, UP)
 *						results in the following psuedo-3D orientation:
 *	    [d]<-[a][b]
 *           [c]
 *
 * returns : pointer to the new struct
 * type	   : (Room *)
 */

Room *connect_room(Room *room, Room *other_room, enum direction d) {
	// if direction already set, can't change
	if (room->connections[d] != NULL || other_room->connections[(d + 3) % 6] != NULL) {
		return NULL;
	}
	room->connections[d] = other_room;
	other_room->connections[(d + 3) % 6] = room;

	return room;
}

/*
 * function: list_connections
 * --------------------------
 * params:
 *      *room        :  room to have connections listed
 *		type         :  (Room *) pointer to Room struct
 *
 * prints out all non-NULL connections of a given room in the order:
 *		NORTH, SOUTH, EAST, WEST, UP, DOWN
 *
 * returns : void
 */

void list_connections(Room *room) {
	Room **cons = room->connections;
	char *dirs[6] = {"north", "east", "up", "south", "west", "down"};
	int counter = 0;

	// using the (i + 3) % 6 expression, we can print out the directions "in order"
	for (int i = 0; i < 3; ++i) {
		if (cons[i] != NULL) {
			printf("%s %s\n", dirs[i], (cons[i]->locked ? "(locked)" : ""));
			++counter;
		}
		if (cons[(i + 3) % 6] != NULL) {
			printf("%s %s\n", dirs[(i + 3) % 6], (cons[(i + 3) % 6]->locked ? "(locked)" : ""));
			++counter;
		}
	}

	if (counter == 0) {
		printf("you're trapped, find a way out!\n");
	}
}

/*
 * function: free_room
 * -------------------
 * params:
 *      **to_free        :  room to be freed
 *		type             :  (Room **) pointer to a pointer of a Room struct
 *
 * frees the room and all of it's items then sets its pointer to NULL
 *
 * returns : void
 */

void free_room(Room **to_free) {
	free_items(&((*to_free)->items));
	free(*to_free);
	*to_free = NULL;
}

/*
 * function: free_rooms
 * --------------------
 * params:
 *      **to_free        :  room to be freed
 *		type             :  (Room **) pointer to a pointer of a Room struct
 *
 *		dirfrom			 :  used to help with recursion, tells what room you called from (see below)
 *		type			 :  enum direction
 *
 * does a depth first search and frees each room utilizing the dirfrom enum to tell where has already been searched.
 *
 * returns : void
 */

void free_rooms(Room **to_free, enum direction dirfrom) {
	for (int i = 0; i < 6; ++i) {
		if (i == dirfrom) continue;
		if ((*to_free)->connections[i] != NULL) {
			free_rooms(&((*to_free)->connections[i]), (i + 3) % 6);
		}
	}
	free_room(to_free);
}
