#inlude <stdlib.h>



double **init_edge_matrix(char* file){
	FILE *fp;
	int size,from_node,to_node;
	if ((fp = fopen(file,"r")) == NULL){
        	printf("Fail to open file. \n");
        	return null;
    	}
	fscanf(fp,"%d\n",&size);
	double edge_matrix[size][size];

	while(!feof(fp)){
        fscanf(fp, "%d\t%d\n", &from_node, &to_node);
	edge_matrix[from_node][to_node] = 1/5;
    	}

	return edge_matrix;
}
