
#include "avatar.h"
#include <ctype.h>

/*
 * function: get_command
 * ---------------------
 * params:
 *      *avatar  :  specified sprite in existing game state
 *      type     :  (Avatar *) pointer to Avatar struct
 *
 * takes the user's input and calls the associated functions
 *
 * example  : user inputs: "use key"; get_command calls "use(avatar, "key")"
 *
 * returns  :  void
 */

void get_command(Avatar *avatar) {
	char input[30], command[5] = "", arg[25] = "";
	Room *curr_room = get_location(avatar);
	bool invalid_command = false;
	// all functions that take arguments return either 0 (if they pass) or -1 (if they fail)
	int invalid_arg = 0;
	// gets the command that the user entered
	do {
		invalid_command = false;
		fgets(input, 30, stdin);
		// puts the input into lower-case so user can input either.
		for (int j = 0; input[j]; j++) {
			input[j] = tolower(input[j]);
		}
		// copy all the characters before the first space/new line into command
		int i = 0;
		for (; input[i] != ' ' && input[i] != '\n'; ++i) {
			command[i] = input[i];
		}
		// copy the rest of the input string into arguments
		strcpy(arg, input + i + 1);
		// still have to remove the new line char
		arg[strlen(arg) - 1] = '\0';

		// reads for which command the user has entered
		if(strcmp(command, "look") == 0) {
			printf("you look around and find yourself in ");
			printf("%s\n", curr_room->description);
			printf("after some searching, you discover \n");
			list_items(&(curr_room->items));
			printf("you can go to: \n");
			list_connections(curr_room);
		} else if(strcmp(command, "go") == 0) {
			// reads for which arg the user has entered for the command "go"
			if (strcmp(arg, "north")) {
				invalid_arg = go_to_room(avatar, NORTH);
			} else if (strcmp(arg, "south")) {
				invalid_arg = go_to_room(avatar, SOUTH);
			} else if (strcmp(arg, "east")) {
				invalid_arg = go_to_room(avatar, EAST);
			} else if (strcmp(arg, "west")) {
				invalid_arg = go_to_room(avatar, WEST);
			} else if (strcmp(arg, "up")) {
				invalid_arg = go_to_room(avatar, UP);
			} else if (strcmp(arg, "down")) {
				invalid_arg = go_to_room(avatar, DOWN);
			}
		} else if(strcmp(command, "take") == 0) {
			invalid_arg = take(avatar, arg);
		} else if (strcmp(command, "use") == 0) {
			invalid_arg = use(avatar, arg);
		} else if (strcmp(command, "drop") == 0) {
			invalid_arg = drop(avatar, arg);
		} else if(strcmp(command, "examine") == 0) {

		} else if (strcmp(command, "inventory") == 0) {
			printf("your inventory: \n")
			list_items(&(avatar->backpack));
		} else {
			invalid_command = true;
			printf("Not a valid command, please try again or type h for HELP: ");                                                                                                                                                                                                                                                                                                                                                             // TODO add help for command reference manual
		}
		// sanitizing user input
		if (invalid_arg == -1) {
			printf("\"%s\" is an invalid argument to the command \"%s\" \n", arg, command);
		}
	} while(invalid_command || invalid_arg == -1);
}

/*
 * function: init_game
 * -------------------
 * params:
 *      *avatar  :  specified sprite in existing game state
 *      type     :  (Avatar *) pointer to Avatar struct
 *
 * creates the game environment and all objects within it
 *
 * returns  :
 * type     :  int
 */

int init_game(Avatar **player) {

	Item *cell_items = useable_items("cell key", "this looks like it could be useful", "prison cell", "you open the cell door and leave",
	                                 items("rotting skull", "poor soul; what do you think happened to him?",
	                                       items("Jared Yeager's sandal", "", NULL)));
	Room *prison_cell = room("prison cell", "a dark, disagreeably damp, musty, and cold room. You need to find a way out.", cell_items);

	// Item *courtyard_items =;
	Room *courtyard = room("courtyard", "the outside of the cell, you don't know this place; better find a way out.", NULL);


	Room *guards_barracks = room("guard's quarters", "what looks like the guard's old living quarters.", NULL);
	Room *sewer_1 = room("courtyard sewer", "a wet and dirty sewer; why would you go in here?", NULL);
	Room *sewer_2 = room("sewer walkway", "a darker part of the sewer, out of the corner of your eye you think you spot something.", NULL);
	Room *sewer_3 = room("market sewer", "a long and unending corridor, you hear comotion above, better investigate.", NULL);
	Room *market = room("marketplace", "a bustling ", NULL);
	Room *prison_walkway = room("prison walkway", "a gloomy prison walkway lit only by the torches on the walls. You see some light coming from a door up ahead", NULL);
	Room *vault_chamber = room("vault chamber", "the chamber before the vault. The vault door is locked; I need a key", NULL);
	Room *vault_interior = room("vaul interior", "the inside of the vault. You could have never dream of so much wealth in one place", NULL);
	// Item *test_item = items("apple", "debugging", NULL);
	// Item *test_use =  useable_items("key", "debug", "test", "used", NULL);
	// main_room = connect_room(main_room, northen_room, NORTH);
	// add_item(&(main_room->items), test_item);
	// add_item(&(main_room->items), test_use);
	// list_connections(main_room);
	*player = avatar(prison_cell, NULL);
	return 0;
}

/*
 * function: play_game
 * -------------------
 * calls init_game to initialize all game objects then runs through the game
 *      by continuously calling get_command
 *
 * returns  :
 * type     :  int
 */

int play_game() {
	Avatar *player;
	init_game(&player);
	bool game_over;
	// printf
	// while (!game_over) {
	//  get_command(player);
	// }
	// initialize the game environment
	// TODO: make the rooms
	Room *main_room = get_location(player);
	printf("room inventory: \n");
	list_items(&(main_room->items));
	printf("player inventory: \n");
	list_items(&(player->backpack));

	get_command(player);

	printf("room inventory: \n");
	list_items(&(main_room->items));
	printf("player inventory: \n");
	list_items(&(player->backpack));

	get_command(player);

	printf("room inventory: \n");
	list_items(&(main_room->items));
	printf("player inventory: \n");
	list_items(&(player->backpack));

	get_command(player);

	printf("room inventory: \n");
	list_items(&(main_room->items));
	printf("player inventory: \n");
	list_items(&(player->backpack));
	printf("\n");
	return 0;
}

/*
 * function: main
 * --------------
 * calls play_game
 *
 * returns  :
 * type     :  int
 */

int main(void) {
	play_game();
	return 0;
}
