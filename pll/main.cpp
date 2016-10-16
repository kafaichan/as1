#include <iostream>
#include <stdio.h>
using namespace std; 
#include "pll.h"

#define roadnet

#ifdef test
	#define MAXNODE 7
#endif 

#ifdef roadnet
	#define MAXNODE 1971277
#endif

#ifdef bike
	#define MAXNODE 58227
#endif

//#pragma warning(disable:4996)

int main() {

#ifdef test
	PLL p = PLL("./test.txt", MAXNODE);
#endif

#ifdef roadnet
	PLL p = PLL("./roadNet-CA.txt", MAXNODE);
#endif

#ifdef bike
	PLL p = PLL("./Brightkite_edges.txt", MAXNODE);
#endif
	p.construct_index();
	p.create_query();
	//system("pause");
	return 0;
}
