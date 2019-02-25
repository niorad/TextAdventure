source =  adventure.c items.c rooms.c
objects = adventure.o items.o rooms.o
prog = textgame

#edit : $(objects)
#	gcc -o edit $(objects)


items.o : items.h
#JSON_parser.o : JSON_objects.h
rooms.o : rooms.h items.h
#room_generator.o : JSON_objects.h

$(prog): $(objects)
	gcc $(objects) -o $(prog)

$(objects): $(source)
