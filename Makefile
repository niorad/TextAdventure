source =  adventure.c items.c JSON_parser.c rooms.c room_generator.c
objects = adventure.o items.o JSON_parser.o rooms.o room_generator.o
prog = textgame

edit : $(objects)
	gcc -o edit $(objects)
items.o : items.h
JSON_parser.o : JSON_objects.h
rooms.o : rooms.h items.h
room_generator.o : JSON_objects.h
