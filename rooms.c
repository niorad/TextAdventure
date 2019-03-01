
#include "rooms.h"

/*
 * function: room
 * --------------------------
 * params:
 *      *name         :  the room's identifier in the backend
 *		type          :  (char *) C string
 *
 *      *description  :  visual representation of the room in the frontend
 *		type          :  (char *) C string
 *
 *		locked        :  determines if the room is locked or unlocked (accessible to the player)
 *		type          :  bool
 *
 *		*items        :  dynamically allocated list of items contained within the room
 *		type          :  (Item *) pointer to Item struct
 *
 * constructs a new Room struct given the passed specifications
 *      acts as a container within the game state
 *
 * returns : pointer to the new struct
 * type	   : (Room *)
 */

Room *room(char *name, char *description, bool locked, Item *items) {
	Room *new_room = NULL;
	new_room = (Room *) malloc(sizeof(Room));

	// checks that dynamic allocation was completed successfully
	if (new_room == NULL) {
		printf("malloc failed\n");
		exit(EXIT_FAILURE);
	}

	// field assignments
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
 *      *room        :  room whose d connection is to be set to other_room
 *		type         :  (Room *) pointer to Room struct
 *
 *      *other_room  :  room whose opposite, (d + 3) % 6, connection is to be set to room
 *		type         :  (Room *) pointer to Room struct
 *
 *		*items       :  dynamically allocated list of items contained within the room
 *		type         :  (Item *) pointer to Item struct
 *
 * relates two rooms based on a passed cardinal direction
 *      used primarily in hard-coded game setup
 *
 * ex:  connect_room(a, c, SOUTH), connect_room(b, a, WEST), connect_room(a, d, UP)
 *						results in the following psuedo-3D orientation:
 *	    [d]<-[a][b]
 *           [c]
 *
 * returns : pointer to the new struct
 * type	   : (Room *)
 */

Room *connect_room(Room *room, Room *other_room, enum direction d) {
	// can't change orientation once direction is set
	if (room->connections[d] != NULL || other_room->connections[(d + 3) % 6] != NULL) {
		return NULL;
	}

	/*
	 * relates the two rooms: connect_room(a, c, SOUTH) also
	 * 		effectively executes connect_room(c, a, NORTH)
	 */

	room->connections[d] = other_room;
	other_room->connections[(d + 3) % 6] = room;

	return room;
}

/*
 * function: list_connections
 * --------------------------
 * params:
 *      *room  :  room to have connections listed
 *		type   :  (Room *) pointer to Room struct
 *
 * prints out all existing (non-null) connections of a given room
 *
 * returns : void
 */

void list_connections(Room *room) {
	Room **cons = room->connections;
	// array of direction names required because enum values cannot be converted to strings
	char *dirs[6] = {"north", "east", "up", "south", "west", "down"};
	int counter = 0;

	/*
 	 * only iterates three times because three opposite direction pairs
	 * 		(n + 3) % 6 relation allows for the printing of connections
	 * 		in the order: NORTH, SOUTH, EAST, WEST, UP, DOWN
	 */

	for (int i = 0; i < 3; ++i) {
		if (cons[i] != NULL) {
			// if the room is locked, prints out indicator for better user experience
			printf("%s %s\n", dirs[i], (cons[i]->locked ? "(locked)" : ""));
			++counter;
		}
		if (cons[(i + 3) % 6] != NULL) {
			printf("%s %s\n", dirs[(i + 3) % 6], (cons[(i + 3) % 6]->locked ? "(locked)" : ""));
			++counter;
		}
	}

	// hints that, if no connections exist, some action is required for progression
	if (counter == 0) {
		printf("you're trapped, find a way out!\n");
	}
}

/*
 * function: free_room
 * -------------------
 * params:
 *      **to_free  :  room to be freed
 *		type       :  (Room **) double pointer to a Room struct
 *
 * frees the room and all of its items, then sets its pointer to NULL
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
 *      **to_free  :  list of rooms to be freed
 *		type       :  (Room **) pointer to a pointer of a Room struct
 *
 *		dirfrom	   :  used to help with recursion, tells what room you called from (see below)
 *		type	   :  enum direction
 *
 * leverages depth first search to free each room; the dirfrom enum tells the program which
 * 		rooms have already been searched.
 *
 * avoids freeing a room twice
 *               [ c ]
 * 		ex) ["a"][ b ]  suppose a is already freed
 *			     [ d ]  free_rooms(b, WEST) would be called (since a is west of b),
 *							which would then call free_rooms(c, SOUTH) and free_rooms(d, NORTH) etc
 *
 * returns : void
 */

void free_rooms(Room **to_free, enum direction dirfrom) {
	for (int i = 0; i < 6; ++i) {
		// if already checked continue loop
		if (i == dirfrom) continue;

		// if adjacent room exists, recursive call to free all of its connections 
		if ((*to_free)->connections[i] != NULL)
			free_rooms(&((*to_free)->connections[i]), (i + 3) % 6);
		}
	}
	free_room(to_free);
}
