
#include "rooms.h"

/*
 * struct: avatar
 * ------------
 * models a playable character / sprite in the game
 *
 * functions: provide means of
 *      interacting with the game environment and
 *		modifying fields belonging to the avatar
 */

typedef struct avatar {
	Room *location;
	Item *backpack;
} Avatar;


// constructor
Avatar *avatar(Room *location, Item *backpack);

// getter methods
Room *get_location(Avatar *avatar);

Item *get_inventory(Avatar *avatar);

// setter methods
void set_location(Avatar *avatar, Room *room);

// adds an item to the backpack
void add_to_inventory(Avatar *avatar, Item *item);

//changes the room that the avatar is currently in
int go_to_room(Avatar *avatar, enum direction dir);

// inventory modifiers and interactive methods
int use(Avatar *avatar, char *object);

int take(Avatar *avatar, char *object);

int drop(Avatar *avatar, char *object);

void look(Avatar *avatar);

void free_avatar(Avatar **to_free);
