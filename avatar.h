
#include "rooms.h"

/*
 * Struct: Avatar
 * ------------
 * models a sprite in the game (ex: player)
 *
 * Functions: provide means of
 * 		interacting with the game environment and
 *		modifying fields belonging to the avatar
 */

typedef struct avatar {
	Room *location;
	Item *backpack;
} Avatar;

// constructor
Avatar *avatar(Room *location, Item *backpack);

// getters
Room *get_location(Avatar *avatar);

Item *get_inventory(Avatar *avatar);

// setters
void set_location(Avatar *avatar, Room *room);

// adds an item to the backpack
void add_to_inventory(Avatar *avatar, Item *item);

//changes the room that the avatar currently is in
int go_to_room(Avatar *avatar, enum direction dir);

// inventory modifiers
int use(Avatar *avatar, char *object);

int take(Avatar *avatar, char *object);

int drop(Avatar *avatar, char *object);
