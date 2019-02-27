
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

Room *room(char *name, char *description, Item *items) {

	Room *new_room = NULL;
	new_room = (Room *) malloc(sizeof(Room));

	if (new_room == NULL) {
		printf("malloc failed\n");
		exit(EXIT_FAILURE);
	}
	new_room->name = name;
	new_room->description = description;
	new_room->items = items;
	return new_room;
}

/*
 * function: connect_room
 * --------------------------
 * relates two rooms based on a passed cardinal direction;
 *      used primarily in hard-coded (OR JSON) game setup
 * ex:  connect_room(a, c, NORTH), connect_room(b, a, EAST), connect_room(a, d, UP)
                        results in the following psuedo-3D orientation:
 *	    [d]<-[a][b]
 *           [c]
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

// prints out all non-NULL connections of a given room
void list_connections(Room *room) {
	Room **cons = room->connections;
	char *dirs[6] = {"north", "east", "up", "south", "west", "down"};

	// using the (i + 3) % 6 expression, we can print out the directions "in order"
	for (int i = 0; i < 3; ++i) {
		if (cons[i] != NULL) {
			printf("%s \n", dirs[i]);
		}
		if (cons[(i + 3) % 6] != NULL) {
			printf("%s \n", dirs[i]);
		}
	}
}

void print_room(Room *room) {
	printf("%s \n", room->name);

	// iteration pointer initialization
	Item *dummy_item = room->items;

	printf("inventory: \n");
	while (dummy_item != NULL) {
		printf("%s \n", dummy_item->name);
		dummy_item = dummy_item->next;
	}
	Room *roomcon = room->connections[0];
	printf("%s \n", roomcon->name);
}
