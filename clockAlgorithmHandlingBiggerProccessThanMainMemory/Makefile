DEBUG = -g
OPTS = $(DEBUG) -Wall -ansi -pedantic -std=c++17

CC=g++ $(OPTS) -c
LN=g++

OBJS = main.o Page.o 

proj1: $(OBJS)
	$(LN) -o proj1 $(OBJS)

main.o: main.cpp Page.hpp 
	$(CC) main.cpp

page.o: Page.cpp Page.hpp 
	$(CC) Page.cpp



clean:
	/bin/rm -rf $(OBJS) proj1



