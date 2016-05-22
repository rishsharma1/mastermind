#Makefile: Project 2 Computer Systems 
#Name: Rishabh Sharma 
#Username: rishabhs
#Student number: 694739

## CC  = Compiler.
## CFLAGS = Compiler flags.

CC	= gcc
CFLAGS 	=  -Wall

all: server client connect.o

connect.o:
	$(CC) $(CFLAGS) -c connect.c

server: connect.o
	$(CC) $(CFLAGS) -o server server.c connect.o -pthread


client: connect.o
	$(CC) $(CFLAGS) -o client client.c connect.o


## Clean: Remove object files and core dump files.
clean:
		/bin/rm $(OBJ)

## Clobber: Performs Clean and removes executable file.

clobber: clean
		/bin/rm $(EXE)