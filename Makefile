
SRC = items.c rooms.c adventure.c
OBJ = items.o rooms.o adventure.o
PROG = fix
DEPS = $(OBJS:.o=.h)

$(PROG): $(OBJ)
	gcc $(OBJ) -o $(PROG)

$(OBJ): $(SRC)

-include $(DEPS)
