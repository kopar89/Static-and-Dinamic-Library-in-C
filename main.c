#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix_operations.h"


int main() {
    int n;
    printf("Введите размерность матриц (степень двойки): ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Ошибка ввода!\n");
        return 1;
        }


    if (n <= 0 || (n & (n - 1)) != 0) {
        printf("Ошибка: размерность должна быть положительной степенью двойки.\n");
        return 1;
    }

    srand(time(NULL));

    int** A = create_matrix(n);
    int** B = create_matrix(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            A[i][j] = rand() % 10;
            B[i][j] = rand() % 10;
        }

    int** result_classic = create_matrix(n);
    matrix_multiply(result_classic, A, B, n);

    int** result_strassen = create_matrix(n);
    strassen(A, B, result_strassen, n);

    printf("\nМатрица A:\n");
    print_matrix(A, n);
    printf("\nМатрица B:\n");
    print_matrix(B, n);

    printf("\nРезультат классического умножения:\n");
    print_matrix(result_classic, n);

    printf("\nРезультат умножения по Штрассену:\n");
    print_matrix(result_strassen, n);

    free_matrix(A, n);
    free_matrix(B, n);
    free_matrix(result_classic, n);
    free_matrix(result_strassen, n);

    return 0;
}
