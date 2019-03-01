TextAdventure - Brendon Ky, Deniz Guler, Valeriy Soltan
implementation of a text adventure game using the C programming language

Files:
- adventure.c
- avatar.c
- avatar.h
- items.c
- items.h
- rooms.c
- rooms.h

adventure.c
- Implements game functionality and command input
- Utilizes functions from items.c, rooms.c and avatar.c

avatar.c/avatar.h
- Models sprite (the player) in the game
  - Has an inventory so that each avatar can carry items with it
- Functions implemented in avatar.c allow for the avatar to interact with the world
- Implements functionality for use/take methods

items.c/items.h
- Models items in the world
- Items are kept in an avatar's inventory, or a room's inventory
- Has members for name, description and the next item in the inventory

rooms.c/rooms.h
- Models all the rooms in the world
  - Has an inventory so that each room can contain a number of items
- Has members for description, items, and connected rooms that the player can move to
