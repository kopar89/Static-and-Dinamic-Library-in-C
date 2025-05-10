#include <stdio.h>
#include <stdlib.h>

int** create_matrix(int n) {
    int** matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
        matrix[i] = (int*)calloc(n, sizeof(int));
    return matrix;
}

void free_matrix(int** matrix, int n) {
    for (int i = 0; i < n; i++)
        free(matrix[i]);
    free(matrix);
}

void matrix_multiply(int **result, int **matrix1, int **matrix2, int N) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            result[i][j] = 0;
            for (int k = 0; k < N; k++)
                result[i][j] += matrix1[i][k] * matrix2[k][j];
        }
}

void print_matrix(int **matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%4d ", matrix[i][j]);
        printf("\n");
    }
}

void add_matrix(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void subtract_matrix(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

void strassen(int** A, int** B, int** C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;

    int **A11 = create_matrix(k), **A12 = create_matrix(k);
    int **A21 = create_matrix(k), **A22 = create_matrix(k);
    int **B11 = create_matrix(k), **B12 = create_matrix(k);
    int **B21 = create_matrix(k), **B22 = create_matrix(k);
    int **C11 = create_matrix(k), **C12 = create_matrix(k);
    int **C21 = create_matrix(k), **C22 = create_matrix(k);
    int **M1 = create_matrix(k), **M2 = create_matrix(k);
    int **M3 = create_matrix(k), **M4 = create_matrix(k);
    int **M5 = create_matrix(k), **M6 = create_matrix(k);
    int **M7 = create_matrix(k);
    int **T1 = create_matrix(k), **T2 = create_matrix(k);

    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }

    add_matrix(A11, A22, T1, k);
    add_matrix(B11, B22, T2, k);
    strassen(T1, T2, M1, k);

    add_matrix(A21, A22, T1, k);
    strassen(T1, B11, M2, k);

    subtract_matrix(B12, B22, T1, k);
    strassen(A11, T1, M3, k);

    subtract_matrix(B21, B11, T1, k);
    strassen(A22, T1, M4, k);

    add_matrix(A11, A12, T1, k);
    strassen(T1, B22, M5, k);

    subtract_matrix(A21, A11, T1, k);
    add_matrix(B11, B12, T2, k);
    strassen(T1, T2, M6, k);

    subtract_matrix(A12, A22, T1, k);
    add_matrix(B21, B22, T2, k);
    strassen(T1, T2, M7, k);

    add_matrix(M1, M4, T1, k);
    subtract_matrix(T1, M5, T2, k);
    add_matrix(T2, M7, C11, k);

    add_matrix(M3, M5, C12, k);
    add_matrix(M2, M4, C21, k);

    subtract_matrix(M1, M2, T1, k);
    add_matrix(T1, M3, T2, k);
    add_matrix(T2, M6, C22, k);

    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++) {
            C[i][j] = C11[i][j];
            C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }

    free_matrix(A11, k); free_matrix(A12, k); free_matrix(A21, k); free_matrix(A22, k);
    free_matrix(B11, k); free_matrix(B12, k); free_matrix(B21, k); free_matrix(B22, k);
    free_matrix(C11, k); free_matrix(C12, k); free_matrix(C21, k); free_matrix(C22, k);
    free_matrix(M1, k);  free_matrix(M2, k);  free_matrix(M3, k);  free_matrix(M4, k);
    free_matrix(M5, k);  free_matrix(M6, k);  free_matrix(M7, k);
    free_matrix(T1, k);  free_matrix(T2, k);
}
