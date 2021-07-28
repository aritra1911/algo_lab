/*
 * Let A be n*n square matrix matay. WAP by using appropriate user defined
 * functions for the following:
 *   i. Find the number of nonzero elements in A
 *  ii. Find the sum of the elements above the leading diagonal.
 * iii. Display the elements below the minor diagonal.
 *  iv. Find the product of the diagonal elements.
 */

int main(void)
{
    int **mat;

    printf("Enter n: ");
    scanf("%d", &n);

    mat = (int**) malloc(n * sizeof *mat);
    for (int i = 0; i < n; i++) {
        mat[i] = malloc(n * sizeof **mat);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &mat[i][j]);
        }
    }

    /* Non-zero elements */
    int nz = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (mat[i][j] != 0) {
                nz++;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        free(mat[i]);
    }
    free(mat);

    return EXIT_SUCCESS;
}
