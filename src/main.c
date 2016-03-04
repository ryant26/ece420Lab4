#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "main.h"
#include "../sdk/Lab4_IO.h"
#include "../sdk/timer.h"
#include <mpi.h>
#include "utilities.h"

#define MASTER		0

int main(int argc, char * argv[]){
	int threads, rank;
	double ** graph;
	
	


	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &threads);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);



	if (rank == MASTER){
		printf("Hello from master, there are %d processes: \n", threads);
		
		graph = init_edge_matrix("data_input");

	} else {
		printf("Hello from: %d\n", rank);
	}
	MPI_Finalize();
	return 0;
}
