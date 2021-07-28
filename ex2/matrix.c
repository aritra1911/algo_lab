/*
 * Let A be n*n square matrix matay. WAP by using appropriate user defined
 * functions for the following:
 *   i. Find the number of nonzero elements in A
 *  ii. Find the sum of the elements above the leading diagonal.
 * iii. Display the elements below the minor diagonal.
 *  iv. Find the product of the diagonal elements.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int **mat;
    int n;

    printf("Enter n: ");
    scanf("%d", &n);

    /* allocate memory for matrix */
    mat = (int **) malloc(n * sizeof *mat);
    for (int i = 0; i < n; i++) {
        mat[i] = malloc(n * sizeof **mat);
    }

    /* input matrix */
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &mat[i][j]);
        }
    }

    /* count non-zero elements */
    int nz = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (mat[i][j] != 0) {
                nz++;
            }
        }
    }
    printf("\n# of non-zero elements : %d\n", nz);

    /* calculate sum of the elements above the leading diagonal */
    int sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            sum += mat[i][j];
        }
    }
    printf("sum of the elements above the leading diagonal : %d\n", sum);

    /* print elements below the minor diagonal */
    printf("Elements below the minor diagonal : ");
    for (int i = 0; i < n; i++) {
        for (int j = n - i; j < n; j++) {
            printf("%d ", mat[i][j]);
        }
    }

    /* calculate the product of the diagonal elements */
    int product = 1;
    for (int i = 0; i < n; i++) {
        product *= (n-i-1 != i) ? mat[i][i] * mat[i][n-i-1]
                                : mat[i][i];
    }
    printf("\nproduct of the diagonal elements : %d\n", product);

    /* Free memory allocated for matrix */
    for (int i = 0; i < n; i++) free(mat[i]);
    free(mat);

    return EXIT_SUCCESS;
}
