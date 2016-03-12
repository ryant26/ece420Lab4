#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utilities.h"

// Reads in the edge matrix
// Handles the allocation of memory
void init_edge_matrix(int **A, int* size){
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

	// Allocate memory for array;
	*A = calloc((*size) * (*size), sizeof(int));

	while(!feof(fp)){
        fscanf(fp, "%d\t%d\n", &from_node, &to_node);
		setValue(*A, *size, to_node, from_node, 1);

		edge_counts[from_node]++;
   	}

   	//Insert edge counts
   	int i;
   	for (i = 0; i < *size * *size; i++){
   		if ((*A)[i] == 1) (*A)[i] = edge_counts[i % *size];
   	}

   	//Clean up
	fclose(fp);
	free(edge_counts);
}	

// gets a value from a row major array representing a matrix
int getValue(int *A, int row_size, int row, int column){
	return A[(row_size*row)+column];
}

// sets a value in a row major array representing a matrix
void setValue(int *A, int row_size, int row, int column, int value){
	A[(row_size*row)+column] = value;
}

// Initializes an array and sets all elements to a specific value
double * init_process_rank_vector(int size, double value){
	double * vect = malloc(size * sizeof(double));
	int i;
	for (i =0; i < size; i++){
		vect[i] = value;
	}
	return vect;
}