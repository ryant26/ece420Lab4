#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define DEBUG 1

void init_edge_matrix(double ***A, int* size){
	FILE *fp;
	int from_node,to_node;
	double **edge_matrix;

	if ((fp = fopen("data_input","r")) == NULL){
        	printf("Fail to open file. \n");
        	exit(1);
    	}
	fscanf(fp,"%d\n",size);
	if (DEBUG) printf("Mallocing Memory\n");
	edge_matrix = malloc((*size)* sizeof(double*));
	int i;
	for (i=0;i<*size;i++){
		edge_matrix[i] = malloc((*size) * sizeof(double));
	}
	memset(edge_matrix[0],0,(*size)*(*size)*sizeof(double));

	if (DEBUG) printf("Malloc Complete\n");
	if (DEBUG) printf("Importing edges into edge matrix\n");
	while(!feof(fp)){
        fscanf(fp, "%d\t%d\n", &from_node, &to_node);
	edge_matrix[from_node][to_node] = (double)1/(*size);
    	}
	if (DEBUG) printf("Edge import complete\n");
	fclose(fp);

	*A = edge_matrix;
}
