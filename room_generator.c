
#include <stdio.h>

#include "rooms.h"

#define ROOM_PATH = 'all_rooms.txt'

/*
 * Syntax for the room file (JSON Syntax):
 *
 *  {
 *      "room_name" : "room name text"
 *      "room_desc" : "room description text"
 *      "items" : [
 *          {
                "item_name" : "item name text"
                "item_desc" : "item description text"
            },
            {
                           "item_name" : "item name text"
                           "item_desc" : "item description text"
            }
 *      ]
 *  }
 *
 */



static int num_rooms = 0;//total number of rooms in the file

//gets a room from a specified index
Room *get_room(int room_index){

}
