CC=gcc #C compiler
CXX=g++ #C++ compiler
CFLAGS=-g -Wall -pedantic

NAME = seashell
OBJ = $(NAME).o
FILE = $(NAME).c

shell:
	$(CC) $(CFLAGS) -o $(OBJ) $(FILE)

parser:
	$(CC) $(CFLAGS) -o parser.o parser.c

run:
	./$(OBJ)

clean:
	rm *.o
