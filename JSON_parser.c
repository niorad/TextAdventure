
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "JSON_members.h"

//reads the next char, returns false if the next char is EOF
bool next_char(long int *cur_pos, char *cur_char, FILE *fp) {
	// stores position in the file that cur_char is
	*cur_pos = ftell(fp);
	*cur_char = fgetc(fp);
	return *cur_char != EOF;
}

//skips over all the whitespaces (space and new line characters)
void read_whitespace(long int *cur_pos, char *cur_char, FILE *fp) {
	while(next_char(cur_pos, cur_char, fp) && (*cur_char == ' ' || *cur_char == '\n')) {
		//blank
	}
}

//reads a boolean primitive values
bool *read_bool(long int *cur_pos, char *cur_char, FILE *fp) {
	next_char(cur_pos, cur_char, fp);
	char c = *cur_char;
	bool *return_val = malloc(sizeof(bool));


	//moves the reader head to the end
	for(int i = 0; i < 3; ++i) {
		next_char(cur_pos, cur_char, fp);
	}

	if(c == 't') {
		*return_val = true;
	} else if(c == 'f') {
		*return_val = false;
	} else {
		printf("something went wrong reading boolean value\n");
		exit(EXIT_FAILURE);
	}

	return return_val;
}

//reads the next string
//precondition: the reader head is pointing to a valid string
//postcondition: the reader head is pointing to a \" indicating the end of the string
char *read_string(long int *cur_pos, char *cur_char, FILE *fp) {
	long int start_pos = *cur_pos;
	char *value = malloc(sizeof(char));
	char *temp;

	//reads the string until \" and allocates memory
	while(next_char(cur_pos, cur_char, fp)  && *cur_char != '\"') {
		//increases the space in memory
		int length = strlen(value);
		value = realloc(value, (length + 1) * sizeof(char));

		//appends cur_str to value
		value[length] = *cur_char;
		value[length + 1] = '\0';
	}

	// string string_buffer[100];
	//
	// //read the line onto string_buffer
	// if(fgets(buffer, sizeof(string_buffer) / sizeof(char), fp) != NULL) {
	//  //find the length of the string in string_buffer
	//
	//     //find the first \"
	//  while() {
	//
	//  }
	//
	//     //read the string until it finds the second \"
	// }
	return value;
}

//reads a number
//TODO: only unsigned ints supported currently
int *read_int(long int *cur_pos, char *cur_char, FILE *fp) {
	int *value = 0;

	fscanf(fp, "%i", value);

	//calculates the length of
	int length = floor(log10((double) *value)) + 1;

	//moves the reader head forward
	for(int i = 0; i < length; ++i) {
		next_char(cur_pos, cur_char, fp);
	}

}

//prototypes
JSON_array *read_array(long int *cur_pos, char *cur_char, FILE *fp);
JSON_object *read_object(long int *cur_pos, char *cur_char, FILE *fp);
JSON_primitive *read_primitive(long int *cur_pos, char *cur_char, FILE *fp);

//reads the value for a KVP from a JSON file starting at the given position
void *read_value(long int *cur_pos, char *cur_char, FILE *fp) {
	void *value;

	//skips whitespaces
	read_whitespace(cur_pos, cur_char, fp);

	//checks what type the value is and calls the appropriate method
	switch(*cur_char) {
	//array
	case '[':
		value = read_array(cur_pos, cur_char, fp);
		break;
	//object
	case '{':
		value = read_object(cur_pos, cur_char, fp);
		break;
	//primitive
	default:
		//moves the reader head back one spot
		ungetc(*cur_char, fp);
		--cur_pos;
		value = read_primitive(cur_pos, cur_char, fp);
		break;
	}
}

//reads an array starting at the given position, returns a pointer to the first element of the array
JSON_array *read_array(long int *cur_pos, char *cur_char, FILE *fp){
	int size = 0;
	JSON_values type;
	JSON_array *array = malloc(sizeof(JSON_array));

	//while the array still has values
	while(next_char(cur_pos, cur_char, fp) && *cur_char == ',') {
		//skips whitespaces
		read_whitespace(cur_pos, cur_char, fp);

		//reads the next value and adds it to the array
		int length = sizeof(array->value) / sizeof(array->value[0]);
		array->value = realloc(array->value, length + 1);
		void **tmpptr = &array->value;
		tmpptr[length] = read_value(cur_pos, cur_char, fp);

		read_whitespace(cur_pos, cur_char, fp);
	}

	//end of array
	if(next_char(cur_pos, cur_char, fp) && *cur_char == ']') {
		return array;
	} else {
		printf("Something went wrong while reading an array\n");
		exit(EXIT_FAILURE);
		return NULL;
	}
}

//reads an object started at the given position, returns a pointer to the object
JSON_object *read_object(long int *cur_pos, char *cur_char, FILE *fp) {
	JSON_object *object = malloc(sizeof(JSON_object));

	//reads each KVP in the object
	do {
		read_whitespace(cur_pos, cur_char, fp);

		//reads the next kvp and creates the memory for it
		int length = sizeof(object->value) / sizeof(JSON_KVP);
		object->value = realloc(object->value, length + 1);

		//reads the key for the KVP
		if(next_char(cur_pos, cur_char, fp) && *cur_char == '\"') {
			object->value->key = read_string(cur_pos, cur_char, fp);
		}

		read_whitespace(cur_pos, cur_char, fp);

		//indicates start of value in KVP
		if(next_char(cur_pos, cur_char, fp) && *cur_char == ':') {
			read_whitespace(cur_pos, cur_char, fp);
			//reads the value in KVP
			object->value->value = read_value(cur_pos, cur_char, fp);
		}
	} while(next_char(cur_pos, cur_char, fp) && *cur_char == ',');

	//end of object
	if(next_char(cur_pos, cur_char, fp) && *cur_char == '}') {
		return object;
	} else {
		printf("Something went wrong while reading an object\n");
		exit(EXIT_FAILURE);
		return NULL;
	}
}

//reads a primitive starting at the given position, returns a pointer to the primitive
JSON_primitive *read_primitive(long int *cur_pos, char *cur_char, FILE *fp) {
	//cur_char is not accurate when it is passed, it's one char ahead since the reader head was moved back

	JSON_primitive *primitive = malloc(sizeof(JSON_primitive));

	switch(*cur_char) {
	case 't':
		primitive->type = BOOL;
		primitive->value = read_bool(cur_pos, cur_char, fp);
		break;
	case 'f':
		primitive->type = BOOL;
		primitive->value = read_bool(cur_pos, cur_char, fp);
		break;
	case '"':
		primitive->type = STRING;
		primitive->value = read_string(cur_pos, cur_char, fp);
		break;
	default:
		primitive->type = INT;
		primitive->value = read_int(cur_pos, cur_char, fp);
		break;
	}
}

//reads the contents of a JSON object provided a file and a position relative from the start of the file to start reading from
// JSON_object *read_object(long int *cur_pos, char *cur_char, FILE *fp) {
//  JSON_object *obj = malloc(sizeof(JSON_object));
//  if(obj == NULL) {
//      printf("could not malloc obj");
//      exit(EXIT_FAILURE);
//  }
//
//  //does passing FILE keep the reader pointing to the same location? if so the following line is redundant
//  //fseek(*fp, *cur_pos, SEEK_SET); sets reader pointer to specified position
//
//  char *key;
//  JSON_KVP *kvp = malloc(sizeof(JSON_KVP));
//  if(kvp != NULL) {
//      printf("could not malloc kvp");
//      exit(EXIT_FAILURE);
//  }
//  //reads contents of the json object
//  while(next_char(cur_pos, cur_char, fp) && *cur_char == ',') {
//      //TODO: finish reading string for keys in kvp
//      //string started, get the value of the string and assign it to key
//
//      read_whitespace(cur_pos, cur_char, fp);
//
//      if(*cur_char == "\"") {
//          key = read_string(cur_pos, cur_char, fp);
//      }
//      //start of value
//      else if(*cur_char = ":") {
//
//      }
//
//      read_whitespace(cur_pos, cur_char, fp);
//  }
//
//  //end of object
//  if(next_char(cur_char, cur_pos, fp) && *cur_char == '}') {
//      return obj;
//  } else {
//      printf("Something went wrong while reading an object\n");
//      exit(EXIT_FAILURE);
//      return NULL;
//  }
// }

//parser that reads the JSON file at the provided file path
JSON_object *read_file(char *file_path) {
	JSON_object *data;
	// reads the file
	FILE *JSON_file_stream = fopen(file_path, "r");
	if(JSON_file_stream == NULL) {
		// checks if the file path is valid
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
	//*     reads "<string>" : indicating name/value pair
	//*         calls method to read the value, value could be an array, an object or a json_primitive
	//*             [ indicates start of an array
	//*                 calls method to read the value, value could be an array, an object or a json_primitive
	//*                 reads until , indicates end of the object
	//*                 iterates until reads ], indicates then end of the array
	//*             { indicates the start of an object
	//                  recurse
	//              [NOT IMPLEMENTED] reads null, indicates null object
	//*             else: value is a primitive
	//                  reads true/false, indicates boolean
	//                  reads "<string>", indicates a string
	//                  reads <numbers>, indicates an unsigned int
	//                      NOTE: this does not support negatives, decimals, or scientific notation
	//          reads , indicates another string/value pair is after, iterate while there are commas
	//      read until }, indicates end of object

	read_whitespace(cur_pos, cur_char, JSON_file_stream);

	if(*cur_char == '{') {
		//object started
	} else {
		printf("Start of JSON file isn't formatted properly\n");
	}

	do {
		data = read_object(cur_pos, cur_char, JSON_file_stream);

		read_whitespace(cur_pos, cur_char, JSON_file_stream);
		//Doesn't use commas to seperate each object
	} while (*cur_char = '{');

	free(cur_pos);
	cur_pos = NULL;
	free(cur_char);
	cur_char = NULL;

	return data;
}

int main(void) {
	read_file("./testJSON.JSON");
}
