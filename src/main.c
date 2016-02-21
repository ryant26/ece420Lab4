#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include "main.h"
#include "utilities.h"
#include "../sdk/Lab3IO.h"
#include "../sdk/timer.h"
#include <omp.h>

int main(int argc, char * argv[]){
	int threads = parse_number_threads(argc, argv);
	double **A; int size; 
    Lab3LoadInput(&A, &size);
    double storage[size];

    // Initialize Times
	double start_time;
	double end_time;
	GET_TIME(start_time);

	/*This is the Gaussian Step, it creates an upper triangle of the matrix*/
 	int k;
 	#pragma omp parallel num_threads(threads) \
	default(none) shared(A,size) private(k)
	{
	 	for (k = 0; k < size; k++){
	 		#pragma omp single 
	 		{
	 			int max_indice = find_max_indice(k, A, size);
	 			swap_rows(A, k, max_indice);
	 		}
	 		int i;
	 		int j;;
			#pragma omp for schedule(dynamic,1) private(i,j)
	 		for (i = k+1; i < size; i++){
				double subtrahend_coefficient = (A[i][k]/A[k][k]);;
	 			for (j = k; j < size + 1; j++){
	 				A[i][j] = A[i][j] - (subtrahend_coefficient* A[k][j]);
	 			}
	 		}
	 	}

	 	#pragma omp barrier

		/*Jordan Elimination Step*/
		int i;
	 	for (k = size-1; k > 0; k--){
			#pragma omp for schedule(dynamic,1) private(i)
	 		for (i = 0; i < k; i++){
	 			A[i][size] = A[i][size] - ( (A[i][k] / A[k][k]) * A[k][size]);
	 			A[i][k] = A[i][k] - ( (A[i][k] / A[k][k]) * A[k][k]);
	 		}
	 	}
	}



 	// Retrieve elapsed time
	GET_TIME(end_time);

	get_result(storage, A, size);
	printf("Total Time: %f \n",end_time-start_time);
 	Lab3SaveOutput(storage, size, end_time - start_time);

	return 0;
}

int find_max_indice(int k, double **A, int size){
	int i;
	double current_max = fabs(A[k][k]);
	int current_max_indice = k;
	for (i = k; i < size; i++){
		if (fabs(A[i][k]) > current_max){
			current_max_indice = i;
			current_max = fabs(A[i][k]);
		}
	}
	return current_max_indice;
}

void swap_rows(double **A, int from, int to){
	double * temp;
	temp = A[to];
	A[to] = A[from];
	A[from] = temp;
}

void get_result(double *storage, double **A, int size){
	int i;
	for (i = 0; i < size; i++){
		storage[i] = A[i][size] / A[i][i];
	}
}
