//nested loops fazla

#include <stdio.h>

#define SIZE 100

int main() {

    int A[SIZE][SIZE];
    int B[SIZE][SIZE];
    int C[SIZE][SIZE];

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {

            A[i][j] = i + j;
            B[i][j] = i - j;
            C[i][j] = 0;
        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {

                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    printf("%d\n", C[0][0]);

    return 0;
}

