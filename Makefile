CC=gcc #C compiler
CFLAGS=-g -Wall -pedantic

OBJECT = seashell.o
SRC = seashell.c

shell: $(OBJECT)
	$(CXX) $(CFLAGS) $(OBJECT) -o $(SRC)

run:
	./$(OBJECT)

clean:
	rm foo.txt && rm *.o
