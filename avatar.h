
#include "rooms.h"

/*
 * struct: avatar
 * ------------
 * models a playable character / sprite in the game
 */

typedef struct avatar {
	Room *location;
	Item *backpack;
} Avatar;


// constructor
Avatar *avatar(Room *location, Item *backpack);

// getter methods
Item *get_backpack(Avatar *avatar);

Room *get_location(Avatar *avatar);

// setter methods
void set_location(Avatar *avatar, Room *room);

//changes the room that the avatar is currently in
int go_to_room(Avatar *avatar, enum direction dir);

// backpack modifiers and room-avatar interactive methods
int use(Avatar *avatar, char *object);

int take(Avatar *avatar, char *object);

int drop(Avatar *avatar, char *object);

void look(Avatar *avatar);

// memory management once game is complete
void free_avatar(Avatar **to_free);
