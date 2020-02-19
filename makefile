#compiler: 
CC = gcc 
#compiler flags:
#-g -ansi -Wall - pedantic -std=gnu99 -I
CFLAGS = -g -Wall -I -std=gnu99

all: smallsh

smallsh: input_handling.o run_shell.o built_in_cmnds.o
	$(CC) $(CFLAGS) -o smallsh input_handling.o	 run_shell.o built_in_cmnds.o

input_handling: input_handling.c
	$(CC) $(CFLAGS) -o input_handling.o input_handling.c

run_shell: run_shell.c
	$(CC) $(CFLAGS) -o run_shell.o run_shell.c

built_in_cmnds: built_in_cmnds.c
	$(CC) $(CFLAGS) -o built_in_cmnds.o built_in_cmnds.c

clean:
	$(RM) smallsh *.o *~