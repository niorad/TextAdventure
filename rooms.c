
#include "rooms.h"

Room *room(char *description, Item *items) {

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

Room *connect_room(Room *room, Room *new_room, enum direction d) {
	// if direction already set, can't change
	if (room->connections[d] != NULL || new_room->connections[(d + 3) % 6] != NULL) {
		return NULL;
	}
	room->connections[d] = new_room;
	new_room->connections[(d+3) % 6] = room;

	return room;
}

void list_connections(Room *room) {

	Room **cons = room->connections;
	char *dirs[6] = {"north", "east", "up", "south", "west", "down"};
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
	printf("%s \n", room->description);

	// iteration pointer initialization
	Item *dummy_item = room->items;

	printf("inventory: \n");
	while (dummy_item != NULL) {
		printf("%s \n", dummy_item->name);
		dummy_item = dummy_item->next;
	}
	Room *roomcon = room->connections[0];
	printf("%s \n", roomcon->description);
}
