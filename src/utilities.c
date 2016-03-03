#include <stdlib.h>
#include <stdio.h>



void init_edge_matrix(char* file, double *** edge_matrix){
	FILE *fp;
	int size,from_node,to_node;
	if ((fp = fopen(file,"r")) == NULL){
        	printf("Fail to open file. \n");
        	exit(1);
    	}
	fscanf(fp,"%d\n",&size);

	while(!feof(fp)){
        fscanf(fp, "%d\t%d\n", &from_node, &to_node);
	*edge_matrix[from_node][to_node] = 1/5;
    	}
}
