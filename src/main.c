#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "main.h"
#include "../sdk/Lab4_IO.h"
#include "../sdk/timer.h"
#include <mpi.h>
#include "utilities.h"

#define E 0.00001
#define D 0.85
#define MASTER		0

#define DEBUG_MAIN  1

int main(int argc, char * argv[]){
	int threads, rank, size, rows_per_thread, *graph;
	double* rank_vector;

	// Read graph data into memory
	// Will be distributed across processes
	init_edge_matrix(&graph, &size);
	rank_vector = init_rank_vector(size);

	MPI_Init(&argc, &argv);

	// Get MPI meta_data
	MPI_Comm_size(MPI_COMM_WORLD, &threads);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	//Initialize looping variables
	int above_threshold = 1;
	rows_per_thread = size / threads;
	double *prevous_rank_vector = init_previous_rank_vector(rank, rows_per_thread, 1/size);

	int j;

	while ( above_threshold ){
		// Reset the continue condition
		above_threshold = 0;

		// Iterate over the nodes (Columns) in the matrix this process is responsible for
		for(j = rank * rows_per_thread; j < (rank+1) * rows_per_thread; j++){
			
			int normalized_j = j % (rows_per_thread);
			
			// Check the stopping threshold
			if ( (fabs(rank_vector[j] - prevous_rank_vector[normalized_j]) 
				/ fabs(prevous_rank_vector[normalized_j])) > E){

				// Set continue condition
				above_threshold = 1;

				double rank_sum = 0;
				int i;
				int outgoing_edges = 0;

				// Move down the column and add nodes which have an edge to us
				// rank_sum = sum(rank(i)/L(i))
				for (i = 0; i < size; i++){
					if ( (outgoing_edges = getValue(graph, size, i, j)) ){
						rank_sum += rank_vector[i]/outgoing_edges;
					}
				}

				// Update previouse rank
				prevous_rank_vector[normalized_j] = rank_vector[j];
				
				// Calculate new rank
				rank_sum *= D;
				rank_sum += (1-D) * 1/size;
				rank_vector[j] = rank_sum;
			}
		}

		long pointer_offset = rank * rows_per_thread * sizeof(double);
		
		// Sync results
		MPI_Allgather(rank_vector + pointer_offset, rows_per_thread, MPI_DOUBLE,
						rank_vector, rows_per_thread, MPI_DOUBLE, MPI_COMM_WORLD);
	}

	return 0;
}

double * init_rank_vector(int size){
	double * vect = malloc(size * sizeof(double));
	double default_value = 1/size;
	int i;
	for (i =0; i < size; i++){
		vect[i] = default_value;
	}
	return vect;
}

double * init_previous_rank_vector(int process_rank, int nodes_proc, double value){
	double * vect = malloc(nodes_proc * sizeof(double));
	int i;
	for (i =0; i < nodes_proc; i++){
		vect[i] = value;
	}
	return vect;
}
