#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "main.h"
#include "../sdk/Lab4_IO.h"
#include "../sdk/timer.h"
#include <mpi.h>
#include "utilities.h"

// Contants
#define E 0.00001
#define D 0.85

#define MASTER		0
#define DEBUG_MAIN  0

int main(int argc, char * argv[]){
	int threads, rank, size, rows_per_thread, *graph;
	double* rank_vector;

	MPI_Init(&argc, &argv);

	// Get MPI meta_data
	MPI_Comm_size(MPI_COMM_WORLD, &threads);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	// ========================== Initialization and matrix read in ========================
	if (rank == MASTER) init_edge_matrix(&graph, &size); 

	//Broadcast the size to all processes
	MPI_Bcast(&size, 1, MPI_INT, MASTER, MPI_COMM_WORLD);

	// All processes init a rank_vector size = # nodes
	rank_vector = init_process_rank_vector(size, 1/size);	
	rows_per_thread = size / threads;

	// Only the master holds the entire matrix (representing the graph)
	// Thus all other processes init a matrix, size = total rows / threads = rows_per_thread
	if (rank != MASTER) graph = malloc(size * rows_per_thread * sizeof(int));

	// Now we scatter the original matrix (Representing the graph)
	// to all processes
	int send_count = size * rows_per_thread;

	if (rank == MASTER){
		MPI_Scatter(graph, send_count, MPI_INT,
				MPI_IN_PLACE, send_count, MPI_INT, MASTER, MPI_COMM_WORLD);	
	} else {
		MPI_Scatter(MPI_IN_PLACE, send_count, MPI_INT,
				graph, send_count, MPI_INT, MASTER, MPI_COMM_WORLD);	
	}


	// ============================== Page Rank Implementation ================================

	//Initialize looping variables
	int above_threshold = 1;
	
	double *prevous_rank_vector = init_process_rank_vector(rows_per_thread, 1);
	double *iteration_rank_results = init_process_rank_vector(rows_per_thread, 1);

	int i;

	while ( above_threshold ){
		// Reset the continue condition
		above_threshold = 0;

		// Iterate over the nodes (Rows) in the matrix this process is responsible for
		for(i = 0; i < rows_per_thread; i++){
						
			// Check the stopping threshold
			if ( (fabs(rank_vector[(rank * rows_per_thread) + i] - prevous_rank_vector[i]) 
				/ fabs(prevous_rank_vector[i])) > E){

				// Set continue condition
				above_threshold = 1;

				double rank_sum = 0;
				int j;
				int outgoing_edges = 0;

				// Move down the column and add nodes which have an edge to us
				// rank_sum = sum(rank(i)/L(i))
				for (j = 0; j < size; j++){
					if ( (outgoing_edges = graph[(i * size) + j]) ){
						rank_sum += rank_vector[j] / outgoing_edges;
					}
				}

				// Update previouse rank
				prevous_rank_vector[i] = rank_vector[(rank * rows_per_thread) + i];
				
				// Calculate new rank
				rank_sum *= D;
				rank_sum += (1-D) * 1/size;
				iteration_rank_results[i] = rank_sum;
			}
		}
		
		// Sync results
		MPI_Allgather(iteration_rank_results, rows_per_thread, MPI_DOUBLE,
						rank_vector, rows_per_thread, MPI_DOUBLE, MPI_COMM_WORLD);
	}

	// Output results
	if(rank == MASTER){
		Lab4_saveoutput(rank_vector, size, 10);
	}

	// Cleanup
	MPI_Finalize();
	free(rank_vector);
	free(graph);
	free(iteration_rank_results);
	free(prevous_rank_vector);

	return 0;
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
