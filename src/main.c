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
	int threads, rank, size;
	double ** graph;
	
	
	init_edge_matrix(&graph, &size);

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &threads);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == MASTER){
		printf("Hello from master, there are %d processes: \n", threads);
		
	} else {
		printf("Hello from: %d\n", rank);
	}
	MPI_Finalize();
	return 0;
}
