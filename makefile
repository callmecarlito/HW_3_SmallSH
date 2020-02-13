#compiler: 
CC = gcc 
#compiler flags:
#-g -ansi -Wall - pedantic -std=gnu99 -I
CFLAGS = -g -Wall -I -std=gnu99

all: smallsh

smallsh: input_handling.o
	$(CC) $(CFLAGS) -o smallsh input_handling.o	

input_handling: input_handling.c
	$(CC) $(CFLAGS) -o input_handling.o input_handling.c

clean:
	$(RM) smallsh *.o *~