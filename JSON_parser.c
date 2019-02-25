
#include <stdbool.h>
#include <stdio.h>
#include "JSON_object.h"

//checks the provided data to see if there is an object with the provided name
bool has_object(JSON_member data, string object_name) {

}

//checks the JSON file and sees if there is another object that can be parsed
bool has_next_member() {

}

//reads the next char, returns false if the next char is EOF
bool next_char(long int *cur_pos, char *cur_char, FILE *fp) {
    *cur_pos = ftell(*fp);//stores position in the file that cur_char is
    *cur_char = fgetc(*fp);
    return cur_char != EOF;
}

//reads the contents of a JSON object provided a file and a position relative from the start of the file to start reading from
JSON_object *read_object(long int *cur_pos, char *cur_char, FILE *JSON_file_stream) {
    JSON_object *obj = malloc(sizeof(JSON_object));
    if(obj == NULL) {
        printf("could not malloc obj");
        exit(EXIT_FAILURE);
    }

    //does passing FILE keep the reader pointing to the same location? if so the following line is redundant
    fseek(*JSON_file_stream, *cur_pos, SEEK_SET);//sets reader pointer to specified position

    char *key;
    JSON_KVP *kvp = malloc(sizeof(JSON_KVP));
    if(kvp == null) {
        printf("could not malloc kvp");
        exit(EXIT_FAILURE);
    }
    //reads contents of the json object
    while(next_char(cur_pos, cur_char, JSON_file_stream)) {
        if(*cur_char == '}') {//breaks if we reach the end of the object
            break;
        }
        //TODO: finish reading string for keys in kvp

    }
}

//parser that reads the JSON file at the provided file path
JSON_member *read_file(string file_path) {
    JSON_node *objects;


    FILE *JSON_file_stream = fopen(file_path, "r");//reads the file
    if(*JSON_file_stream == NULL) {//checks if the file path is valid
        printf("File not found\n");
        exit(EXIT_FAILURE);
    }

    //ftell gets the current position in the file
    //fseek sets the current position in the file
    long int *cur_pos = malloc(sizeof(long int));
    if(cur_pos == NULL) {
        printf("could not malloc cur_pos\n");
        exit(0);
    }
    char *cur_char = malloc(sizeof(char));
    if(cur_char == NULL) {
        printf("could not malloc cur_char\n");
        exit(0);
    }




    //iterates while there is still file to read

    //TODO: everything w/o a star


    //*  { indicates start of JSON object
    //      reads "<string>" : indicating name/value pair
    //          calls method to read the value, value could be an array, an object or a json_primitive
    //              [ indicates start of an array
    //                  calls method to read the value, value could be an array, an object or a json_primitive
    //                  reads until , indicates end of the object
    //                  iterates until reads ], indicates then end of the array
    //              { indicates the start of an object
    //                  recurse
    //              reads null, indicates null object
    //              else: value is a primitive
    //                  reads true/false, indicates boolean
    //                  reads "<string>", indicates a string
    //                  reads <numbers>, indicates an unsigned int
    //                      NOTE: this does not support negatives, decimals, or scientific notation
    //          reads , indicates another string/value pair is after, iterate while there are commas
    //      read until }, indicates end of object
    while(next_char(cur_pos, cur_char, JSON_file_stream)){
        if(*cur_char == '{') {
            //object started
            *objects = read_object(cur_pos, cur_char, JSON_file_stream)
        }

    }

    free(cur_pos);
    cur_pos = NULL;
    free(cur_char);
    cur_char = NULL;
}
