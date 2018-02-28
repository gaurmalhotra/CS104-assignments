all: search

webpage.o: webpage.cpp webpage.h
	g++ -c -g -Wall -std=c++11 webpage.cpp -o webpage.o

search: search.cpp webpage.o
	g++ -g -Wall -std=c++11 search.cpp webpage.o -o search

clean:
	rm -f webpage.o search