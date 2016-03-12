#ifndef UTILITIES_H
#define UTILITIES_H

// Reads in the edge matrix 
// int ** is the pointer to the storage array (unallocated)
// int * is the pointer to the size variable (unset)
void init_edge_matrix(int**, int *);

// Gets a value from a row major array containing a matrix
// int * - array
// int - row size (in matrix)
// int - row
// int - column
int getValue(int*, int, int, int);

// Sets a value in a row major array containing a matrix
// int * - array
// int - row size (in matrix)
// int - row
// int - column
// int - value
void setValue(int *, int, int, int, int);

// Initializes an array and sets all elements to a specific value
// int - size
// double - default value for each element
// returns pointer to allocated array
double * init_process_rank_vector(int, double);


#endif
