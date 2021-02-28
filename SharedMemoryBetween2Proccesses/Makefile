CC = g++ -c -g -Wall -ansi -pedantic 
LN = g++

all: Royal Subject

Royal: Royal.o
	$(LN) -o Royal Royal.o

Subject: Subject.o
	$(LN) -o Subject Subject.o
	
Royal.o: Royal.cpp
	$(CC) Royal.cpp
	
Subject.o: Subject.cpp
	$(CC) Subject.cpp
	
clean:
	/bin/rm -f *.o Royal Subject
