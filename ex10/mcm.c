/*
 * Write a Program to implement Matrix Chain Multiplication.
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* Matrix Ai has dimension p[i-1] x p[i] for i = 1..n */
static int min_mults(int *p, size_t n)
{
    int **m = malloc(n * sizeof (int *));
    for (size_t i = 0; i < n; i++)
        m[i] = malloc(n * sizeof (int));

    /* For simplicity of the program, one extra row and one
     * extra column are allocated in m[][]. 0th row and 0th
     * column of m[][] are not used */

    /* m[i, j] = Minimum number of scalar multiplications needed
     * to compute the matrix A[i]A[i+1]...A[j] = A[i..j] where
     * dimension of A[i] is p[i-1] x p[i] */

    /* cost is zero when multiplying one matrix */
    for (size_t i = 1; i < n; i++)
        m[i][i] = 0;

    /* l is chain length */
    for (size_t l = 2; l < n; l++) {
        for (size_t i = 1; i < n - l + 1; i++) {

            size_t j = i + l - 1;
            m[i][j] = INT_MAX;

            for (size_t k = i; k <= j - 1; k++) {
                /* q = cost / scalar multiplications */
                int q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];

                if ( q < m[i][j] )
                    m[i][j] = q;
            }
        }
    }

    int ret = m[1][n - 1];

    for (size_t i = 0; i < n; i++)
        free(m[i]);
    free(m);

    return ret;
}

int main(void)
{
    int *arr;
    size_t n;

    printf("Enter number of matrices: ");
    scanf("%lu", &n);

    /* We're storing only the column count of each matrix. However the
     * row count of the first matrix cannot be determined using the
     * column count of the previous matrix, so we'll also need to store
     * that. */
    n++;
    arr = malloc(n * sizeof *arr);

    printf("\nEnter row count of the first matrix and\n"
            "the column counts of each matrix:\n");
    for (size_t i = 0; i < n; i++)
        scanf("%i", &arr[i]);

    printf("\nMinimum number of multiplications is %d\n",
            min_mults(arr, n));

    free(arr);

    return 0;
}
