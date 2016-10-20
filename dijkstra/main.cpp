#include <stdio.h>
#include <iostream>
#include <time.h>
using namespace std;

#pragma warning(disable:4996)
#define roadnet 

#include "dijkstra.h"

#ifdef roadnet
#define MAXNODE 1971277
#endif

#ifdef bike
#define MAXNODE 58227
#endif

#ifdef test
#define MAXNODE 14
#endif


#pragma warning(disable:4996)


int main()
{
#ifdef roadnet
	Dijkstra dijkstra = Dijkstra("../data/roadNet-CA.txt", MAXNODE);
#endif

#ifdef bike
	Dijkstra dijkstra = Dijkstra("../data/Brightkite_edges.txt", MAXNODE);
#endif

#ifdef test
	Dijkstra dijkstra = Dijkstra("../data/dijkstra_test.txt", MAXNODE);
#endif
	
	dijkstra.construct_index();
	dijkstra.create_query();
//	system("pause");
	return 0;
}
