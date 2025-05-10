#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H

int** create_matrix(int n);
void free_matrix(int** matrix, int n);
void matrix_multiply(int** result, int** matrix1, int** matrix2, int N);
void strassen(int** A, int** B, int** C, int n);
void print_matrix(int** matrix, int n);

#endif
