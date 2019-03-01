
#include "avatar.h"

/*
 * function: avatar
 * --------------------------
 * params:
 *      *location  :  where the avatar is located at initialization
 *		type       :  (Room *) pointer to Room struct
 *
 *		*backpack  :  the avatar's inventory (dynamically allocated)
 *		type       :  (Item *) pointer to Item struct
 *
 * constructs a new avatar struct given the passed specifications
 *
 * returns : pointer to the new struct
 * type	   : (Avatar *)
 */

Avatar *avatar(Room *location, Item *backpack) {
	Avatar *new_avatar = NULL;
	new_avatar = (Avatar *) malloc(sizeof(Avatar));

	// checks that dynamic allocation was completed successfully
	if (new_avatar == NULL) {
		printf("malloc failed\n");
		exit(EXIT_FAILURE);
	}

	// field assignments
	new_avatar->location = location;
	new_avatar->backpack = backpack;

	return new_avatar;
}

// accessor methods
Item *get_inventory(Avatar *avatar) {
	return avatar->backpack;
}

Room *get_location(Avatar *avatar) {
	return avatar->location;
}

void set_location(Avatar *avatar, Room* room){
	avatar->location = room;
}

/*
 * function: add_to_inventory
 * --------------------------
 * params:
 *      *avatar  :  specified sprite in existing game state
 *      type     :  (Avatar *) pointer to Avatar struct
 *
 *      *item    :  object to be added to backpack
 *      type     :  (Item *) pointer to Item struct
 *
 * adds the specified item to the avatar's inventory
 *      to avoid using additional memory for a tail pointer, items
 *      are added to the front of the list
 *
 * returns : void (no scenario exists when addition to linked list fails)
 */

void add_to_inventory(Avatar *avatar, Item *item) {
	item->next = avatar->backpack;
	avatar->backpack = item;
}

/*
 * function: go_to_room
 * --------------------------
 * params:
 *      *avatar  :  specified sprite in existing game state
 *      type     :  (Avatar *) pointer to Avatar struct
 *
 *      dir		 :  enumeration of cardinal directions
 *      type     :  enum direction
 *
 * given the passed directional, checks that the corresponding
 *      room exists and relocates the sprite
 *
 * since the enum integer value doubles as the index of the corresponding
 *      directional in the connections vector, relocation is an elegant and
 *		seamless process
 * ex: {NORTH, EAST, UP, SOUTH, WEST, DOWN}
 *     {  0,     1,   2,   3,    4,    5  }
 *
 * connections = {room1, room2, NULL, NULL, NULL, room7}
 *      represents a room with connections to the NORTH,
 *      EAST, and DOWNWARDS directions
 *
 * go_to_room(DOWN) = go_to_room(5), sets location to room7
 *
 * returns : -1 if the room doesn't exist (NULL)
 *            0 upon successful relocation
 * type	   : int
 */

int go_to_room(Avatar *avatar, enum direction dir) {
	Room *room = get_location(avatar);
	if (room->connections[dir] == NULL) {
		return -1;
	}
	if (room->connections[dir]->locked) {
		printf("the door to the %s is locked\n\n", room->connections[dir]->name);
		return 0;
	}
	set_location(avatar, room->connections[dir]);
	return 0;
}

/*
 * function: use
 * --------------------------
 * params:
 *      *avatar  :  specified sprite in existing game state
 *      type     :  (Avatar *) pointer to Avatar struct
 *
 *		*object  :  name of object in avatar's inventory to be used
 *		type     :  (char *) C string
 *
 * TODO : write the docs for this once implementation finalized
 *
 * returns  :  -1 if the item is not in the backpack OR
 *                if the item is not useable in the current room
 *              0 if the item is used successfully
 * type     :  int
 */

int use(Avatar *avatar, char *object) {
	Room *curr_room = get_location(avatar);
	Item *to_use = remove_item(&(avatar->backpack), object);

	// checks that object is in avatar's backpack
	if (to_use == NULL) {
		return -1;
	}
	// TODO : alter the room, change comparison from room description to room name?
	if (strcmp(curr_room->name, to_use->use_room) == 0 || to_use->item_enum == USELESS) {
		printf("%s \n", to_use->use_description);
		int ret = to_use->item_enum;
		free_item(&to_use);
		return ret;
	}
	add_item(&(avatar->backpack), to_use);
	return -1;
}

/*
 * function: take
 * --------------------------
 * params:
 *      *avatar  :  specified sprite in existing game state
 *      type     :  (Avatar *) pointer to Avatar struct
 *
 *		*object  :  name of object to be taken
 *		type     :  (char *) C string
 *
 * accesses the avatar's current location and searches the Room's items list
 *		for the specified object. If it exists, removes it from
 *      the Room's items list and adds it to the player's inventory
 *
 * returns  :  -1 if the object is not found in the room's inventory
 *              0 if the transfer is successful
 * type     :  int
 */

int take(Avatar *avatar, char *object) {
	Room *curr_room = get_location(avatar);
	Item *to_take = remove_item(&(curr_room->items), object);

	// checks that object is in the curr_room's item list
	if (to_take == NULL) {
		return -1;
	}

	add_item(&(avatar->backpack), to_take);
	return 0;
}

/*
 * function: drop
 * --------------
 * params:
 *      *avatar  :  specified sprite in existing game state
 *      type     :  (Avatar *) pointer to Avatar struct
 *
 *		*object  :  name of object to be dropped
 *		type     :  (char *) C string
 *
 * accesses the avatar's inventory and searches for the desired object. If it
 *      exists, removes it frrom the backpack and adds it to the item list of
 *      the avatar's current room
 *
 * returns  :  -1 if the object is not found in the backpack
 *              0 if transfer is successful
 * type     :  int
 */

int drop(Avatar *avatar, char *object) {
	Room *curr_room = get_location(avatar);
	Item *to_drop = remove_item(&(avatar->backpack), object);

	// checks that object is in avatar's backpack
	if (to_drop == NULL) {
		return -1;
	}
	add_item(&(curr_room->items), to_drop);
	return 0;
}

/*
 * function: look
 * --------------
 * params:
 *      *avatar  :  specified sprite in existing game state
 *      type     :  (Avatar *) pointer to Avatar struct
 *
 * accesses the avatar's current location, prints out the description of room,
 *      all the items in it, and all the possible connections.
 *
 * returns  :  void
 */

void look(Avatar *avatar) {
	Room *curr_room = get_location(avatar);
	printf("you look around and find yourself in ");
	printf("%s\n", curr_room->description);
	printf("\nafter some searching, you discover \n");
	list_items(&(curr_room->items));
	printf("\nyou can go: \n");
	list_connections(curr_room);
	printf("\n");
}

/*
 * function: free_avatar
 * ---------------------
 * params:
 *      **to_free  :  specified sprite in existing game state
 *      type       :  (Avatar **) pointer to a pointer Avatar struct
 *
 * frees the memory used by:
 *		A) the avatar
        B) the items in the avatar's backpack (free_items)
                C) all the rooms that the avatar is in and their connections (free_rooms)
                and points the avatar's pointer to NULL
 *
 * returns  :  void
 */

void free_avatar(Avatar **to_free) {
	free_rooms(&((*to_free)->location), NODIR);
	free_items(&((*to_free)->backpack));
	free(*to_free);
	*to_free = NULL;
}
