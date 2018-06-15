# makefile for test environment
#

OUTPUT=oasis

all: $(OUTPUT)

OBJ= avl.h oasis.cpp clan.cpp player.cpp hash.h \
     linked_list.h min_heap.h
	

CFLAGS = -std=c++11 -g

$(OUTPUT): main1.cpp $(OBJ)
	g++ $(CFLAGS) -o $@ $^

test: $(OBJ)
	g++ $(CFLAGS) -o test_avl $^ avl_test.cpp

.PHONY: clean
clean:
	rm -f $(OUTPUT) test_avl test_oasis test.o
	rm -f gab_test
