source = adventure.c items.c rooms.c
objects = adventure.o items.o rooms.o
prog = textgame

edit : $(objects)
	gcc -o edit $(objects)
items.o : items.h
rooms.o : rooms.h items.h

