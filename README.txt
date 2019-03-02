
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
- implements game functionality and command input
- utilizes functions from items.c, rooms.c and avatar.c
- creates 9 rooms; some are empty, others contain items
- recognizes when the game is over (win condition)

avatar.c/avatar.h
- models a sprite (the player) in the game with a C struct
  - has an inventory so that each avatar can carry items
- functions implemented in avatar.c allow for the avatar to interact with the world
  - has a function which allows the avatar to:
    - move through the world
    - take items from rooms
    - use items to alter the game state
    - drop items from its inventory into the current room
- has a function to free memory and removes dangling pointers
  - utilizes the free function in items.c
  - utilizes the free function in rooms.c

items.c/items.h
- models items in the world with a C struct
- items are kept in an avatar's inventory, or a room's inventory
- has members for name, description and the next item in the inventory
  - if the item is useable it also has members for what room it can be used in, the description of it being used,
        and an enum that dictates its effect on the game state
- Has a function to free memory and removes dangling pointers
  - Can free all the Items in a chain

rooms.c/rooms.h
- models all the rooms in the world with a C struct
  - has an inventory so that each room can contain a number of items
- has members for name, description, items, if it's locked, and connected rooms that the player can move to
  - utilizes an enum to represent directions
    - each direction is 2 elements from its opposite to easily obtain opposites with the expression (<direction> + 3) % 6
- has a function to free memory and removes dangling pointers
  - utilizes the free function in items.c

 Game Requirements:
    - our game has 10 rooms (all are initialized in the init_game method)

    - all of our rooms have the potential to contain items and many do (Room.items)
        * others showcase our ability to account for the edge case of an empty room

    - avatar is represented as stated in the instructions (Avatar.backpack)

    - our look function gives the player a complete, visual representation of the
            room; including a description of their location, the objects residing inside,
            and the spacial orientation of their whereabouts (avatar.c -> look)

    - go is fully implemented and even accounts for locked doors (avatar.c -> go_to_room)

    - take item allows the player to pick up items found in the environment (avatar.c -> take)

    - use is implemented so that certain items can only be used in specific locations (use_room field)
            while other can be used universally (USELESS in effect enum). More explicitly, some items
            do not have effects (keys for example) when used in certain rooms but do in others.
            (avatar.c -> use + adventure.c -> play_game)

    - when you use the cell key in the first room, it opens up the possibility of
            going north, changing the state of the current room in relation to its
            adjacent neighbors.
            (adventure.c -> play_game)

    - drop is fully implemented (avatar.c -> drop)

    - the game ends in two different ways depending on which key the player uses
        * if its the ORNATE_KEY they die (lose)
        * if it's the CRUDDY_KEY they successfully break into the vault (win)
        (adventure.c -> play_game)

    Code Requirements:
    - C structs are used to implement avatar, items, and room
    - pointers are used to represent structures like strings, linked lists and arrays
        also used double pointers to modify structures passed as a parameter
    - items, rooms, and avatars are dynamically allocated
    - they are also freed at the end of the game


Video Link:
https://www.youtube.com/watch?v=h0Ago1K_nXw&feature=youtu.be

Git Repository:
https://github.com/vsoltan/TextAdventure/
