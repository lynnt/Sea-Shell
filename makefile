CC=gcc #C compiler
CXX=g++ #C++ compiler
CFLAGS=-g -Wall -pedantic

OBJECT = seashell.o
NAME = seashell

all: $(OBJECT)
	$(CXX) $(CFLAGS) $(OBJECT) -o $(NAME)

run:
	./$(NAME)
	
clean:
	rm foo.txt
