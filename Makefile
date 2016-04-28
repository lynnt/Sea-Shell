CC=gcc #C compiler
CXX=g++ #C++ compiler
CFLAGS=-g -Wall -pedantic

NAME = seashell
OBJ = ${NAME}.o
SRC = ${NAME}.c

shell:
	$(CC) $(CFLAGS) -o $(OBJ) $(SRC)

parser:
	$(CC) $(CFLAGS) -o parser.o parser.c

run: $(OBJ)
	./${OBJ}

valgrind: ${OBJ}
	valgrind ./${OBJ}

clean:
	rm *.o
