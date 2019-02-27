TextAdventure
implementation of a text adventure game using the C programming language

Files:
- JSON_members.h
- JSON_parser.c
- adventure.c
- avatar.c
- avatar.h
- items.c
- items.h
- room_generator.c
- rooms.c
- rooms.h

JSON_members.h
- Not fully implemented
- Struct to model JSON structures (arrays, objects and primitives) in c

JSON_parser.c
- Not fully implemented
- Reads JSON files and creates JSON_members

adventure.c/adventure.h
- Implements game functionality

avatar.c/avatar.h
- Models sprites/characters (the player, NPCs, enemies, etc.) in the game
  - Has an inventory so that each avatar can carry items with it
- Functions implemented in avatar.c allow for the avatar to interact with the world
- Implements functionality for use/take methods

items.c/items.h
- Models items in the world
- Items are kept in an avatar's inventory, or a room's inventory
- Has members for name, description and the next item in the inventory

room_generator.c
- Not fully implemented
- Takes input from the JSON parser and generates rooms accordingly

rooms.c/rooms.h
- Models all the rooms in the world
  - Has an inventory so that each room can contain a number of items
- Has members for description, items, and connected rooms that the player can move to


