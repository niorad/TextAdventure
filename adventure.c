
#include <stdbool.h>
#include "avatar.h"

#define PRINT_TEST(n) printf("test %i \n", n)

// checks the user for what direction they want to go in
void get_command(Avatar *avatar) {
	char input[30], *command, *arg;
	Room *curr_room = get_location(avatar);
	bool invalid_command = false;
	// TODO: parse input: command "arguments"
	// gets the command that the user entered
	// do {
	while(fgets(input, 30, stdin) != NULL)
	{
		printf("%s\n", input);
	}

	printf("passed");
	//  char dummychar = '0';
	//  int i = 0;
	//  for (; dummychar != ' ' || dummychar != '\0'; ++i) {
	//      command[i] = input[i];
	//  }
	//  strcpy(arg, input + i);
	//
	//
	//  invalid_command = false;
	//  // reads for which command the user has entered
	//  if(strcmp(input, "look") == 0) {
	//
	//      list_connections(curr_room);
	//      break;
	//  } else if(strcmp(command, "go") == 0) {
	//      if (strcmp(arg, "north")) {
	//          go_to_room(avatar, NORTH);
	//      } else if (strcmp(arg, "south")) {
	//          go_to_room(avatar, SOUTH);
	//      } else if (strcmp(arg, "east")) {
	//          go_to_room(avatar, EAST);
	//      } else if (strcmp(arg, "west")) {
	//          go_to_room(avatar, WEST);
	//      } else if (strcmp(arg, "up")) {
	//          go_to_room(avatar, UP);
	//      } else if (strcmp(arg, "down")) {
	//          go_to_room(avatar, DOWN);
	//      }
	//  } else if(strcmp(command, "take") == 0) {
	//      take(avatar, arg);
	//  } else if (strcmp(command, "use") == 0) {
	//      use(avatar, arg);
	//  } else if (strcmp(command, "drop") == 0) {
	//      drop(avatar, arg);
	//  } else {
	//      invalid_command = true;
	//      printf("Not a valid command, please try again: ");
	//  }
	// } while(invalid_command);
}

int play_game() {

	bool game_over;

	while (!game_over) {

	}
	// initialize the game environment
	// TODO: make the rooms

	Item *test_item = items("test_item", "debugging", NULL);
	Room *main_room = room("test", NULL);
	Room *northen_room = room("northern", NULL);
	main_room = add_room(main_room, northen_room, NORTH);
	add_item(&(main_room->items), test_item);
	list_connections(main_room);
	Avatar *player = avatar(main_room, NULL);
	list_items(&(main_room->items));
	// take(player, "test_item");
	get_command(player);
	list_items(&(player->backpack));
	return 0;
}

int main(void){
	return play_game();
}
