.PHONY: all
all : main

main : main.o Deck.o Card.o inputValidation.o
	g++ main.o Deck.o Card.o inputValidation.o -o main

main.o : main.cpp Deck.hpp Card.hpp
	g++ -std=c++11 -c main.cpp

Deck.o : Deck.cpp
	g++ -std=c++11 -c Deck.cpp

Card.o : Card.cpp
	g++ -std=c++11 -c Card.cpp

inputValidation.o : inputValidation.cpp
	g++ -std=c++11 -c inputValidation.cpp

.PHONY: clean
clean :
	@rm -f *.o main
