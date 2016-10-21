all: main
main: main.o dijkstra.o
	g++ -std=c++11 main.o dijkstra.o  -o main -O3 

main.o: main.cpp dijkstra.h edge.h heap.h
	g++ -std=c++11 -c main.cpp -o main.o -g -O3 

dijkstra.o: dijkstra.cpp dijkstra.h edge.h heap.h
	g++ -std=c++11 -c dijkstra.cpp -o dijkstra.o -g -O3 


clean:
	rm *.o main

