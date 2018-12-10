CC =gcc
CFLAGS =-Wall
OBJECTS =  main.c functions1.c functions2.c functions3.c

archiver: $(OBJECTS)
        $(CC) $(CFLAGS) $(OBJECTS) -o archiver

main.o: main.c
        $(CC) $(CFLAGS) -c main.c

%.o: %.c
        $(CC) $(CFLAGS) -c $<

