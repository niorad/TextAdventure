
#include "avatar.h"

/*
 * function: avatar
 * --------------------------
 * constructs a new avatar struct given the passed specifications
 * params:
 *      *location  :  where the avatar is located at initialization
 *		type       :  pointer to Room struct
 *
 *		*backpack  :  the avatar's inventory
 *		type       :  pointer to Item struct
 *
 * returns : pointer to the new struct
 * type	   : (Avatar *)
 */
Avatar *avatar(Room *location, Item *backpack) {
	Avatar *new_avatar = NULL;
	new_avatar = (Avatar *) malloc(sizeof(Avatar));

	// check that dynamic allocation was completed successfully
	if (new_avatar == NULL) {
		printf("malloc failed\n");
		exit(EXIT_FAILURE);
	}

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
 *      type     :  pointer to Avatar struct
 *
 *      *item    :  object chosen for addition
 *      type     :  pointer to Item struct
 *
 * adds the specified item to the avatar's inventory
 * to avoid using additional memory for a tail pointer, items
 * are added to the front of the list.
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
 *      type     :  pointer to Avatar struct
 *
 *      dir		 :  enumeration of cardinal directions {NORTH, EAST, UP,SOUTH, WEST, DOWN}
 *      type     :  enum direction
 *
 * given the passed directional, checks that the corresponding
 * room exists and relocates the sprite.
 *
 * returns : -1 if the room doesn't exist; 0 upon successful relocation.
 * type	   : int
 */
int go_to_room(Avatar *avatar, enum direction dir) {
	// determines the desired direction and executes the appropriate function
	Room *room = get_location(avatar);
	if (room->connections[dir] == NULL) {
		return -1;
	}
	set_location(avatar, room->connections[dir]);
	return 0;
}

/*
 * function: use
 * --------------------------
 * params:
 */

int use(Avatar *avatar, char *object) {
	Room *curr_room = get_location(avatar);
	Item *to_use = remove_item(&(avatar->backpack), object);

	if (to_use == NULL) {
		return -1;
	}
	// TODO : alter the room, change comparison from room description to room name?
	if (strcmp(curr_room->description, to_use->use_room) == 0) {
		printf("%s \n", to_use->use_description);
		free_item(&to_use);
	} else {
		add_item(&(avatar->backpack), to_use);
	}
	return 0;
}

int take(Avatar *avatar, char *object) {
	Room *curr_room = get_location(avatar);
	Item *to_take = remove_item(&(curr_room->items), object);
	if (to_take == NULL) {
		return -1;
	}

	add_item(&(avatar->backpack), to_take);
	return 0;
}

int drop(Avatar *avatar, char *object) {
	Room *curr_room = get_location(avatar);
	Item *to_drop = remove_item(&(avatar->backpack), object);
	if (to_drop == NULL) {
		return -1;
	}
	add_item(&(curr_room->items), to_drop);
	return 0;
}
