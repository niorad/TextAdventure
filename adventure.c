
#include <stdbool.h>
#include "avatar.h"

#define PRINT_TEST(n) printf("test %i \n", n)


int play_game() {
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
	take(player, "test_item");
	list_items(&(player->backpack));
	// do {
	//  fgets(input, 5, stdin);
	//  invalid_command = false;
	//  //reads for which command the user has entered
	//  if(strcmp(input, "look") == 0) {
	//      look();
	//  } else if(strcmp(input, "go") == 0) {
	//      go();
	//  } else if(strcmp(input, "take") == 0) {
	//      take();
	//  } else if (strcmp(input, "use") == 0) {
	//      use();
	//  } else if (strcmp(input, "drop") == 0) {
	//      drop();
	//  } else {
	//      invalid_command = true;
	//      printf("Not a valid command, try again: ");
	//  }
	// } while(invalid_command);
	return 0;
}

// //allows the user to go to an adjacent room
// void go() {
//     char *input;
//     char cur_char;
//     int i = 0;
//
//     do {
//         //gets the input from the user
//         cur_char = getchar();
//         //allocate memory and assign the current char
//         calloc(i, i * sizeof(char));
//         *(input + i * sizeof(char)) = cur_char;
//         ++i;
//
//     } while(cur_char != '\n');
// }
// //checks the user for what direction they want to go in
// void getCommand() {
//     char *input;
//
//     bool invalid_command = false;
//
//     //gets the command that the user entered
//     do {
//         fgets(input, 5, stdin);
//         invalid_command = false;
//         //reads for which command the user has entered
//         if(strcmp(input, "look") == 0) {
//             look();
//         } else if(strcmp(input, "go") == 0) {
//             go();
//         } else if(strcmp(input, "take") == 0) {
//             take();
//         } else if (strcmp(input, "use") == 0) {
//             use();
//         } else if (strcmp(input, "drop") == 0) {
//             drop();
//         } else {
//             invalid_command = true;
//             printf("Not a valid command, try again: ");
//         }
//     } while(invalid_command);
// }

int main(void){
	// Item *test_item = items("test", "debugging", NULL);
	// PRINT_TEST(0);
	// Item *other_item = items("other", "works", NULL);
	// PRINT_TEST(1);
	// Room *main_room = room("main", test_item);
	// PRINT_TEST(2);
	// Room *other_room = room("other", other_item);
	// PRINT_TEST(3);
	// add_room(main_room, other_room, 0);
	// PRINT_TEST(4);
	// print_room(main_room);
	return play_game();
}
