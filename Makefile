# makefile for test environment

all: avl_tree

OBJ= $(wildcard *.cpp)

CFLAGS = -std=c++11

avl_tree: avl.h $(OBJ)
	g++ $(CFLAGS) -o $@ $(OBJ)

.PHONY: clean
clean:
	rm -f sim_main $(OBJ_GIVEN) $(OBJ_CORE)
