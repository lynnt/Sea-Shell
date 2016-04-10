CC=gcc #C compiler
CXX=g++ #C++ compiler
CFLAGS=-g -Wall -pedantic

NAME = seaShell
OBJECT = $(NAME).o
FILE = $(NAME).c

shell:
	$(CC) $(CFLAGS) -o $(OBJECT) $(FILE)

parser:
	$(CC) $(CFLAGS) -o parser.o parser.c

run:
	./$(NAME)

clean:
	rm foo.txt
