#include <stdio.h>

#define bike

void readBuffer(FILE* fin){
	char buffer[1024];
	for(int i = 0; i < 4; ++i){
		fgets(buffer, 1024, fin);
	}
}

int main()
{
	int nodenum, edgenum;
	#ifdef roadnet
		FILE* fin = fopen("./roadNet-CA.txt", "r");
		FILE* fout = fopen("./roadNet-CA_ddsg.txt", "w");
		readBuffer(fin);
		nodenum = 1971279;
		edgenum = 5533214;
		fprintf(fout, "d\n");
		fprintf(fout, "%d %d\n", nodenum, edgenum);
	#endif

	#ifdef bike
		FILE* fin = fopen("./Brightkite_edges.txt", "r");
		FILE* fout = fopen("./bike_ddsg.txt", "w");
		nodenum = 58228;
		edgenum = 428156;
		fprintf(fout, "d\n");
		fprintf(fout, "%d %d\n", nodenum, edgenum);
	#endif

	char buffer[1024];
	int fromNodeId, toNodeId;
	while(fgets(buffer, 1024, fin)){
		sscanf(buffer, "%d%d", &fromNodeId, &toNodeId);
		//printf("%d %d\n", fromNodeId, toNodeId);
	        #ifdef roadnet
        	    fprintf(fout, "%d %d 1 1\n", fromNodeId, toNodeId);
	        #else
                    if(fromNodeId < toNodeId)fprintf(fout, "%d %d 1 0\n", fromNodeId, toNodeId);
                #endif
        }
	return 0;
}
