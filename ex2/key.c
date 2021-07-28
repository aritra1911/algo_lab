/*
 * Given key in a sorted array A with distinct values. Write a program to find
 * i, j, k such that A[i] + A[j] + A[k] == key.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int* arr;
    int n, key;

    printf("Enter size of A: ");
    scanf("%d", &n);

    arr = malloc( n * sizeof *arr );

    printf("Enter elements of A in ascending order:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter key: ");
    scanf("%d", &key);

    int flag = 0, i, j, k;
    for (i = 0; i < n - 2; i++) {
        for (j = i + 1; j < n - 1; j++) {
            for (k = j + 1; k < n; k++) {
                if ( arr[i] + arr[j] + arr[k] == key ) {
                    flag = 1;
                    goto done;
                }
            }
        }
    }

done:
    if (flag) {
        printf("\ni = %d, j = %d, k = %d\n", i, j, k);
    } else {
        printf("\nNo unique values of i, j, k satisfied\n"
               "    A[i] + A[j] + A[k] == key\n");
    }

    free(arr);

    return EXIT_SUCCESS;
}
