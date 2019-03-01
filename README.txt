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
- Makefile

adventure.c
- Implements game functionality and command input
- Utilizes functions from items.c, rooms.c and avatar.c
- Creates 9 rooms some with and some without items in them
- Recognizes when the game is over (win or loss)

avatar.c/avatar.h
- Models sprite (the player) in the game with a C struct
  - Has an inventory so that each avatar can carry items with it
- Functions implemented in avatar.c allow for the avatar to interact with the world
  - Has a function which allows the avatar to:
    - Move through the world
    - Take items from rooms
    - Use items to alter the game state
    - Drop items from its inventory into the current room
- Has a function to free memory and removes dangling pointers
  - Utilizes the free function in items.c
  - Utilizes the free function in rooms.c

items.c/items.h
- Models items in the world with a C struct
- Items are kept in an avatar's inventory, or a room's inventory
- Has members for name, description and the next item in the inventory
  - If the item is useable it also has members for what room it can be used in, the description of it being used, and an enum that dictates its effect on the game state
- Has a function to free memory and removes dangling pointers
  - Can free all the Items in a chain

rooms.c/rooms.h
- Models all the rooms in the world with a C struct
  - Has an inventory so that each room can contain a number of items
- Has members for name, description, items, if it's locked, and connected rooms that the player can move to
  - Utilizes an enum for directions
    - Each direction is 2 elements from its opposite to easily obtain opposites with the expression (<direction> + 3) % 6
- Has a function to free memory and removes dangling pointers
  - Utilizes the free function in items.c

Git Repository - https://github.com/vsoltan/TextAdventure/
