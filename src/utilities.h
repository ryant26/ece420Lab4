#ifndef UTILITIES_H
#define UTILITIES_H

void init_edge_matrix(double**, int *);

// Temporary Until real matrix utilities
double getValue(double*, int, int, int);
void setValue(double *, int, int, int, int);
void insert_edge_counts(double **A, int size);

#endif
