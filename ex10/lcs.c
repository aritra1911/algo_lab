/*
 * Write a Program to implement Longest Common Subsequence.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b) (a > b ? a : b)

/* Returns length of LCS for X[0..m-1], Y[0..n-1] */
int lcs(char *x, char *y)
{
    size_t m = strlen(x) + 1;
    size_t n = strlen(y) + 1;

    int **l = malloc(m * sizeof (int *));
    for (size_t i = 0; i < m; i++)
        l[i] = malloc(n * sizeof (int));

    /* Following steps build l[m][n] in bottom up fashion. Note
     * that l[i][j] contains length of LCS of x[0..i-1] and y[0..j-1]
     */
    for (size_t i = 0; i < m; i++) {
        for (size_t j = 0; j < n; j++) {

            if ( i == 0 || j == 0 )
                l[i][j] = 0;

            else if ( x[i-1] == y[j-1] )
                l[i][j] = l[i-1][j-1] + 1;

            else
                l[i][j] = MAX( l[i-1][j], l[i][j-1] );
        }
    }

    /* l[m-1][n-1] contains length of LCS for x[0..n-1] and y[0..m-1] */
    int retval = l[m-1][n-1];

    for (size_t i = 0; i < m; i++)
        free(l[i]);
    free(l);

    return retval;
}

int main()
{
    char x[32], y[32];

    printf("Enter two strings:\n");
    scanf("%s %s", x, y);

    printf("\nLength of LCS is %d\n", lcs(x, y));

    return 0;
}
