#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utilities.h"
#define DEBUG 0


void init_edge_matrix(double **A, int* size){
	FILE *fp;
	int from_node,to_node;
	int * edge_counts;

	// Try open file
	if ((fp = fopen("data_input","r")) == NULL){
        	printf("Fail to open file. \n");
        	exit(1);
    	}

    //Get Matrix size
	fscanf(fp,"%d\n",size);

	//Init edge countss array
	edge_counts = calloc(*size, sizeof(int));

	if (DEBUG) printf("Mallocing Memory\n");

	// Allocate memory for array;
	*A = calloc((*size) * (*size), sizeof(double));

	if (DEBUG) printf("Importing edges into edge matrix\n");

	while(!feof(fp)){
        fscanf(fp, "%d\t%d\n", &from_node, &to_node);
		setValue(*A, *size, from_node, to_node, 1);

		if (DEBUG) printf("Updating edge count\n");
		edge_counts[from_node]++;
   	}

   	//Insert edge counts
	if (DEBUG) printf("Inserting edge counts\n");

   	int rows = -1;
   	int i;
   	for (i = 0; i < *size * *size; i++){
   		if (i % *size == 0) rows++;
   		if ((*A)[i] == 1) (*A)[i] = edge_counts[rows];
   	}

	if (DEBUG) printf("Edge import complete\n");
	fclose(fp);
	free(edge_counts);
}	


// Temporary until real matrix utilities
double getValue(double *A, int row_size, int row, int column){
	return A[(row_size*row)+column];
}

void setValue(double *A, int row_size, int row, int column, int value){
	if (DEBUG) printf("Setting value\n");
	A[(row_size*row)+column] = value;
}
