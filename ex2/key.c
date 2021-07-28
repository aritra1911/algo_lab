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
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            for (k = 0; k < n; k++) {
                if ( arr[i] + arr[j] + arr[k] == key ) {
                    flag = 1;
                    goto done;
                }
            }
        }
    }

done:
    if (flag) {
        printf("i = %d, j = %d, k = %d\n", i, j, k);
    } else {
        printf("No values of i, j, k satisfied A[i] + A[j] + A[k] == key\n");
    }

    free(arr);

    return EXIT_SUCCESS;
}
