# makefile for test environment

OUTPUT=oasis

all: $(OUTPUT)

OBJ= avl.h oasis.cpp clan.cpp player.cpp \
     library1.cpp

CFLAGS = -std=c++11 -g

$(OUTPUT): main1.cpp $(OBJ)
	g++ $(CFLAGS) -o $@ $^

test: $(OBJ)
	g++ $(CFLAGS) -o test_avl $^ avl_test.cpp
	g++ $(CFLAGS) -o test_oasis $^ oasis_test.cpp

.PHONY: clean
clean:
	rm -f $(OUTPUT) test_avl test_oasis test.o
