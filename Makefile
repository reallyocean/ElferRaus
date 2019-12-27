.PHONY: all
all : main

main : main.o Card.o inputValidation.o
	g++ main.o Card.o inputValidation.o -o main

main.o : main.cpp Card.hpp
	g++ -std=c++11 -c main.cpp

Card.o : Card.cpp
	g++ -std=c++11 -c Card.cpp

inputValidation.o : inputValidation.cpp
	g++ -std=c++11 -c inputValidation.cpp

.PHONY: clean
clean :
	@rm -f *.o main
