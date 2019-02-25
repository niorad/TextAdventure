
#include "rooms.h"

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
void go_to_room(Avatar *avatar, enum direction dir);

// inventory modifiers
int take(Avatar *avatar, char *object);

int use(Avatar *avatar, char *object);

int drop(Avatar *avatar, char *object);
