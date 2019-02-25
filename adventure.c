
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "rooms.h"
#define PRINT_TEST(n) printf("test %i \n", n)

//allows for the user to look at what is in the room
void look() {

}
//allows the user to go to an adjacent room
void go() {
    char *input;
    char cur_char;
    int i = 0;

    do {
        //gets the input from the user
        cur_char = getchar();
        //allocate memory and assign the current char
        calloc(i, i * sizeof(char));
        *(input + i * sizeof(char)) = cur_char;
        ++i;

    } while(cur_char != '\n');
}
//allows the user to take an item out of the room they're currently in
void take() {

}
//allows the user to use an item in their inventory
void use() {

}
//allows the user to reomve an item from their inventory and place it in the room they are currently in
void drop() {

}

//checks the user for what direction they want to go in
void getCommand() {
    char *input;

    bool invalid_command = false;

    //gets the command that the user entered
    do{
        fgets(input, 5, stdin);
        invalid_command = false;
        //reads for which command the user has entered
        if(strcmp(input, "look") == 0) {
            look();
        } else if(strcmp(input, "go") == 0) {
            go();
        } else if(strcmp(input, "take") == 0) {
            take();
        } else if (strcmp(input, "use") == 0) {
            use();
        } else if (strcmp(input, "drop") == 0) {
            drop();
        } else {
            invalid_command = true;
            printf("Not a valid command, try again: ");
        }
    } while(invalid_command);
}

int main(void){
    Item *test_item = items("test", "debugging", NULL);
    PRINT_TEST(0);
    Item *other_item = items("other", "works", NULL);
    PRINT_TEST(1);
    Room *main_room = room("main", test_item);
    PRINT_TEST(2);
    Room *other_room = room("main", other_item);
    PRINT_TEST(3);
    add_room(main_room, other_room, 0);
    PRINT_TEST(4);
    print_room(main_room);
}
