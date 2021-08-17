CC = g++ -g -c -Wall -ansi -pedantic -std=c++17
LN = g++

OBJS = main.o Token.o RDP.o SpaceUse.o

proj2: $(OBJS)
	$(LN) -o proj2 $(OBJS)

main.o: main.cpp RDP.hpp Token.hpp SpaceUse.hpp
	$(CC) main.cpp
	
RDP.o: RDP.cpp RDP.hpp Token.hpp SpaceUse.hpp
	$(CC) RDP.cpp

Token.o: Token.cpp Token.hpp
	$(CC) Token.cpp

SpaceUse.o: SpaceUse.cpp SpaceUse.hpp
	$(CC) SpaceUse.cpp
	
clean:
	/bin/rm -f $(OBJS) proj2
