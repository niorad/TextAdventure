
SRC = items.c rooms.c adventure.c avatar.c
OBJ = items.o rooms.o adventure.o avatar.o
PROG = textgame

$(PROG): $(OBJ)
	gcc $(OBJ) -o $(PROG)

$(OBJ): $(SRC)

