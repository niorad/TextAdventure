
#include "avatar.h"
#include <ctype.h>

#define BUFFER_SIZE 200

/*
 * function: get_command
 * ---------------------
 * params:
 *      *avatar  :  specified sprite in existing game state
 *      type     :  (Avatar *) pointer to Avatar struct
 *
 * takes the user's input and calls the associated functions
 *
 * example: user inputs "use key", get_command calls "use(avatar, "key")"
 *
 * returns :  0 or positive effect enum values if successful
 *			  -1 if input or command is not valid
 *
 * type  :  int
 */

int get_command(Avatar *avatar) {
	char *command_list = "\
	\nCommand          | Description \
	\nhelp             | this \
	\nlook             | gives you a description of the room you are in \
	\ngo \"direction\"   | moves your player to the room in \"direction\" \
	\ntake \"item\"      | adds \"item\" into the your inventory if \"item\" is in the current room \
	\nuse \"item\"       | uses \"item\" to alter the game state or consume \"item\" \
	\ndrop \"item\"      | removes \"item\" from the your inventory and puts it in the current room \
	\ninventory        | displays your current inventory\n"    ;

	char input[BUFFER_SIZE], command[BUFFER_SIZE / 5] = "", arg[4 * BUFFER_SIZE / 5] = "";
	Room *curr_room = get_location(avatar);
	bool invalid_command = false;
	// all functions that take arguments return either 0 (if they pass) or -1 (if they fail)
	int arg_num = 0;
	// gets the command that the user entered
	do {
		invalid_command = false;
		// reset the buffer
		input[0] = '\0';
		command[0] = '\0';
		arg[0] = '\0';
		printf("what do you do: ");
		fgets(input, BUFFER_SIZE, stdin);
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
			printf("\n");
			look(avatar);
		} else if(strcmp(command, "go") == 0) {
			// reads for which arg the user has entered for the command "go"
			arg_num = INVALID;
			if (strcmp(arg, "north") == 0) {
				arg_num = go_to_room(avatar, NORTH);
			} else if (strcmp(arg, "south") == 0) {
				arg_num = go_to_room(avatar, SOUTH);
			} else if (strcmp(arg, "east") == 0) {
				arg_num = go_to_room(avatar, EAST);
			} else if (strcmp(arg, "west") == 0) {
				arg_num = go_to_room(avatar, WEST);
			} else if (strcmp(arg, "up") == 0) {
				arg_num = go_to_room(avatar, UP);
			} else if (strcmp(arg, "down") == 0) {
				arg_num = go_to_room(avatar, DOWN);
			}
			if (arg_num != INVALID && arg_num != LOCKED_ROOM) look(avatar);
		} else if(strcmp(command, "take") == 0) {
			arg_num = take(avatar, arg);
		} else if (strcmp(command, "use") == 0) {
			arg_num = use(avatar, arg);
		} else if (strcmp(command, "drop") == 0) {
			arg_num = drop(avatar, arg);
		} else if (strcmp(command, "inventory") == 0) {
			printf("\nyour inventory: \n");
			list_items(&(avatar->backpack));
			printf("\n");
		} else if (strcmp(command, "help") == 0) {
				printf("%s \n", command_list);
		} else {
			invalid_command = true;
			printf("Not a valid command, please try again or type 'help' for instructions : \n");
		}
		// sanitizing user input
		if (arg_num == INVALID) {
			printf("\"%s\" is an invalid argument to the command \"%s\" \n", arg, command);
		}
	} while(invalid_command || arg_num == INVALID);
	return arg_num;
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
 * returns : 0
 * type    : int
 */

int init_game(Avatar **player) {

	Item *cell_items = useable_items("cell key", "an old and rusty key; this looks like it could be useful", "prison cell", "the door of the cell creaks open, you're free! The key breaks in the process", PRISON_KEY,
	                                 items("crushed skull", "poor soul; what do you think happened to him?",
	                                       items("jared yeager's sandal", "if only you could get out of here, this would sell for quite the penny", NULL)));
	Item *sewer_items = useable_items("cruddy key", "submerged in a warm, viscous liquid. Your nose flares at the toxic odor but your curiosity is peaked", "vault chamber", "You open the vault door, revealing riches beyond your wildest imagination. Congratulations, you have won!", CRUDDY_KEY,
	                                  items("nic herndon's water bottle", "gives you the taste of home",
	                                        items("radioactive rat", "their squeeks make you uneasy", NULL)));
	Item *market_items = useable_items("ornate key", "seems fitting for something important...", "vault chamber", "It was a ruse! The key disintegrates in your hand, the vault door collapses and you die a tragic death", ORNATE_KEY,
	                                   useable_items("apple", "crisp and refreshing, nutritious and delicious, and you can't resist to take a bite", "anywhere", "you feel refreshed", USELESS, NULL));

	Room *prison_cell = room("prison cell", "a dark, disagreeably damp, musty, and cold prison cell. You need to find a way out.", false, cell_items);

	Room *courtyard = room("courtyard", "the outside of the cell, you don't know this place; better find a way out.", true, NULL);
	Room *guards_barracks = room("guard's quarters", "what looks like the guard's old living quarters.", false, NULL);
	Room *sewer_1 = room("courtyard sewer", "a wet and dirty sewer; why would you go in here?", false, NULL);
	Room *sewer_2 = room("sewer walkway", "a darker part of the sewer, out of the corner of your eye you think you spot something.", false, sewer_items);
	Room *sewer_3 = room("market sewer", "a long and unending corridor, you hear comotion above, better investigate.", false, NULL);
	Room *market = room("marketplace", "a bustling marketplace filled with traders from all over the world. You're relieved that nobody saw you escape.", false, market_items);
	Room *bank = room("Herndon Bank", "a quiet and unasuming bank. The townspeople say that this is the most secure place to hold your money.", false, NULL);
	Room *vault_chamber = room("vault chamber", "the chamber before the vault. The vault door is locked; you need a key", false, NULL);
	Room *vault_interior = room("vault interior", "game ends here", true, NULL);

	prison_cell = connect_room(prison_cell, courtyard, NORTH);
	courtyard = connect_room(courtyard, guards_barracks, EAST);
	courtyard = connect_room(courtyard, sewer_1, DOWN);
	sewer_1 = connect_room(sewer_1, sewer_2, WEST);
	sewer_2 = connect_room(sewer_2, sewer_3, WEST);
	sewer_3 = connect_room(sewer_3, market, UP);
	market = connect_room(market, bank, NORTH);
	bank = connect_room(bank, vault_chamber, EAST);
	vault_chamber = connect_room(vault_chamber, vault_interior, SOUTH);
	*player = avatar(prison_cell, NULL);
	return 0;
}

/*
 * function: play_game
 * -------------------
 * calls init_game to initialize all game objects then runs through the game
 *      by continuously calling get_command
 *
 * returns : 0
 * type    : int
 */

int play_game() {
	Avatar *player;
	init_game(&player);
	bool game_over;
	int arg_num;
	look(player);
	while (!game_over) {
		arg_num = get_command(player);
		if (arg_num == PRISON_KEY) {
			get_location(player)->connections[NORTH]->locked = false;
			printf("\nyou can go: \n");
			list_connections(get_location(player));
		}
		if (arg_num == ORNATE_KEY) {
			game_over = true;
		}
		if (arg_num == CRUDDY_KEY) {
			get_location(player)->connections[SOUTH]->locked = false;
			game_over = true;
		}
	}
	printf("\nGAME OVER\n");
	free_avatar(&player);
	return 0;
}

/*
 * function: main
 * --------------
 * calls play_game
 *
 * returns : 0
 * type    : int
 */

int main(void) {
	play_game();
	return 0;
}
