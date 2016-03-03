#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "main.h"
#include "../sdk/Lab4_IO.h"
#include "../sdk/timer.h"
#include <mpi.h>

int main(int argc, char * argv[]){
	int threads;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &threads);
	MPI_Finalize();
	return 0;
}