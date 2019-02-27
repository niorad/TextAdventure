
#include <stdbool.h>
#include "avatar.h"

// #define PRINT_TEST(n) printf("test %i \n", n)

// checks the user for what direction they want to go in
void get_command(Avatar *avatar) {
	char input[30], command[5] = "", arg[25] = "";
	Room *curr_room = get_location(avatar);
	bool invalid_command = false;
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
				go_to_room(avatar, NORTH);
			} else if (strcmp(arg, "south")) {
				go_to_room(avatar, SOUTH);
			} else if (strcmp(arg, "east")) {
				go_to_room(avatar, EAST);
			} else if (strcmp(arg, "west")) {
				go_to_room(avatar, WEST);
			} else if (strcmp(arg, "up")) {
				go_to_room(avatar, UP);
			} else if (strcmp(arg, "down")) {
				go_to_room(avatar, DOWN);
			}
		} else if(strcmp(command, "take") == 0) {
			take(avatar, arg);
		} else if (strcmp(command, "use") == 0) {
			use(avatar, arg);
		} else if (strcmp(command, "drop") == 0) {
			drop(avatar, arg);
		} else {
			invalid_command = true;
			printf("Not a valid command, please try again: ");
		}
	} while(invalid_command);
}

// creates the game environment and all objects within it
int init_game(Avatar **player) {
	Item *test_item = items("apple", "debugging", NULL);
	Room *main_room = room("test", NULL);
	Room *northen_room = room("northern", NULL);
	main_room = add_room(main_room, northen_room, NORTH);
	add_item(&(main_room->items), test_item);
	// list_connections(main_room);
	*player = avatar(main_room, NULL);
	return 0;
}

int play_game() {
	Avatar **player;
	init_game(player);
	bool game_over;
	// printf
	// while (!game_over) {
	// 	get_command(player);
	// }
	// initialize the game environment
	// TODO: make the rooms
	// list_items(&(main_room->items));
	get_command(*player);
	// list_items(&(player->backpack));
	return 0;
}

int main(void) {
	play_game();
	return 0;
}
