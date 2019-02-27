
#include "avatar.h"

// checks the user for what direction they want to go in
void get_command(Avatar *avatar) {
	char input[30], command[5] = "", arg[25] = "";
	Room *curr_room = get_location(avatar);
	bool invalid_command = false;
	int invalid_arg = 0;
	// gets the command that the user entered
	do {
		invalid_command = false;
		fgets(input, 30, stdin);
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
			// printf("%s\n", ); TODO finish look implementation
			list_connections(curr_room);
		} else if(strcmp(command, "go") == 0) {
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
		} else {
			invalid_command = true;
			printf("Not a valid command, please try again or type h for HELP: "); // TODO add help for command reference manual
		}
		// sanitizing user input
		if (invalid_arg == -1){
			printf("\"%s\" is an invalid argument to the command \"%s\" \n", arg, command);
		}
	} while(invalid_command || invalid_arg == -1);
}

// creates the game environment and all objects within it
int init_game(Avatar **player) {
	Item *test_item = items("apple", "debugging", NULL);
	Item *test_use =  useable_items("key", "debug", "test", "used", NULL);
	Room *main_room = room("test", NULL);
	Room *northen_room = room("northern", NULL);
	main_room = connect_room(main_room, northen_room, NORTH);
	add_item(&(main_room->items), test_item);
	add_item(&(main_room->items), test_use);
	// list_connections(main_room);
	*player = avatar(main_room, NULL);
	return 0;
}

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

int main(void) {
	play_game();
	return 0;
}
