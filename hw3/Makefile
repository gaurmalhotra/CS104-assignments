all: stringparser

stringparser: stringparser.cpp stackstr.o lliststr.o
	g++ -g -Wall -std=c++11 stringparser.cpp stackstr.o lliststr.o -o stringparser
stringparser.o: stringparser.cpp
	g++ -g -Wall -c -std=c+11 stringparser.cpp -o stringparser.o
stackstr.o: stackstr.h lliststr.o stackstr.cpp
	g++ -g -Wall -c -std=c++11 stackstr.cpp -o stackstr.o
lliststr.o: lliststr.h lliststr.cpp
	g++ -g -Wall -c -std=c++11 lliststr.cpp -o lliststr.o