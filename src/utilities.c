#include <stdlib.h>
#include <stdio.h>
#include <string.h>

double** init_edge_matrix(char* file){
	FILE *fp;
	double size;
	int from_node,to_node;
	double ** edge_matrix;

	if ((fp = fopen(file,"r")) == NULL){
        	printf("Fail to open file. \n");
        	exit(1);
    	}
	fscanf(fp,"%lf\n",&size);
	printf("Mallocing Memory\n");
	edge_matrix = malloc(size* sizeof(double*));
	int i;
	for (i=0;i<size;i++){
		edge_matrix[i] = malloc(size * sizeof(double));
	}
	memset(edge_matrix[0],0,size*size*sizeof(double));

	printf("Malloc Complete\n");
	printf("Importing edges into edge matrix\n");
	while(!feof(fp)){
        fscanf(fp, "%d\t%d\n", &from_node, &to_node);
	edge_matrix[from_node][to_node] = (double)1/(size);
    	}
	printf("Edge import complete\n");
	fclose(fp);
	return edge_matrix;
}
