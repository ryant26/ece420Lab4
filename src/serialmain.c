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


 	int k;
 	for (k = 0; k < size; k++){
 		int max_indice = find_max_indice(k, A, size);
 		swap_rows(A, k, max_indice);

 		int i;
 		int j;
		//printf("Current k value: %d \n",k);
		//printf("----------------------------\n");
 		for (i = k+1; i < size; i++){
		//printf("Current Row: %d \n",i);
			double subtrahend_coefficient = (A[i][k]/A[k][k]);
			//printf("Subtrahend Coefficient: %f \n",subtrahend_coefficient);
 			for (j = k; j < size + 1; j++){
				//printf("Current Col: %d \n",j);
 				A[i][j] = A[i][j] - (subtrahend_coefficient* A[k][j]);
 			}
 		}
 	}

 	//Lab2_saveoutput(A, size, 10, "Gauss.txt");

 	
 	for (k = size-1; k > 0; k--){
		int i;
 		for (i = 0; i < k; i++){
 			//double result = A[i][size] - ( (A[i][k] / A[k][k]) * A[k][size]);;
 			//printf("A[%d][%d] = %f \n", i, size, result);
 			A[i][size] = A[i][size] - ( (A[i][k] / A[k][k]) * A[k][size]);
 			A[i][k] = A[i][k] - ( (A[i][k] / A[k][k]) * A[k][k]);
 		}
 	}

 	//Lab2_saveoutput(A, size, 10, "Jordan.txt");


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
		printf("Storage[%d] = %f \n", i, A[i][size] / A[i][i]);
		storage[i] = A[i][size] / A[i][i];
	}
}
