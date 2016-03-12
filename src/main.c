#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "main.h"
#include "../sdk/Lab4_IO.h"
#include "../sdk/timer.h"
#include <mpi.h>
#include "utilities.h"

#define MASTER		0
#define DEBUG_MAIN  1

int main(int argc, char * argv[]){
	int threads, rank, size, rows_per_thread;
	double * graph;
	
	init_edge_matrix(&graph, &size);

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &threads);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	double ** row_buffer;
	rows_per_thread = size / threads;
	init_row_buffer(&row_buffer, size, rows_per_thread);

	MPI_Scatter(graph, rows_per_thread, MPI_DOUBLE,
		&row_buffer, rows_per_thread, MPI_DOUBLE, 0, MPI_COMM_WORLD);


	if (rank == MASTER){
				
	} else {

	}
	MPI_Finalize();
	return 0;
}

void init_row_buffer(double ***A, int row_size, int rows){
	if (DEBUG_MAIN)printf("Mallocing space\n");
	if ((*A = malloc(rows * sizeof(double*))) == NULL){
		printf("MALLOC ERROR!\n");
		exit(1);
	}
	int i;
	for (i = 0; i < rows; i++){
		(*A)[i] = malloc(row_size * sizeof(double));
	}
	if (DEBUG_MAIN) printf("finished initing row buffer\n");
}