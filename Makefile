# makefile for test environment

OUTPUT=avl_tree

all: $(OUTPUT)

OBJ= avl.h oasis.cpp clan.cpp player.cpp

CFLAGS = -std=c++11 -g

$(OUTPUT): main.cpp $(OBJ)
	g++ $(CFLAGS) -o $@ $^

test: $(OBJ)
	g++ $(CFLAGS) -o test_avl $^ avl_test.cpp
	g++ $(CFLAGS) -o test_oasis $^ oasis_test.cpp

.PHONY: clean
clean:
	rm -f $(OUTPUT) test.o
