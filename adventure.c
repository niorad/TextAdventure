#include <stdio.h>
#include <stdlib.h>

//checks the user for what direction they want to go in
void getCommand() {
    //reads for look
    //reads for go
    //reads for take
    //reads for use
    //reads for drop
}

enum direction getDirection() {
    char *input;
    char curChar
    int i = 0;

    do {
        //gets the input from the user
        curChar = getChar();

        //allocate memory and assign the current char
        calloc(i, i * sizeof(char));
        *(input + i * sizeof(char)) = curChar;

        ++i;

    } while(curChar != "\n");


}

struct item getItem() {

}
