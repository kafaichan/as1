all: main
main: main.o pll.o
	g++ -std=c++11 main.o pll.o  -o main -O3

main.o: main.cpp pll.h edge.h heap.h label.h
	g++ -std=c++11 -c main.cpp -o main.o -g -O3

pll.o: pll.cpp pll.h edge.h heap.h label.h
	g++ -std=c++11 -c pll.cpp -o pll.o -g -O3


clean:
	rm *.o

