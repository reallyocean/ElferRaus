.PHONY: all
all : main

main : main.o Deck.o Card.o
	g++ main.o Deck.o Card.o -o main

main.o : main.cpp Deck.hpp Card.hpp
	g++ -std=c++11 -c main.cpp

Deck.o : Deck.cpp
	g++ -std=c++11 -c Deck.cpp

Card.o : Card.cpp
	g++ -std=c++11 -c Card.cpp

.PHONY: clean
clean :
	@rm -f *.o main
