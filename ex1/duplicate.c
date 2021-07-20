/*
 * Write a program to store numbers into an array of n integers, where the array
 * must contain some duplicates. Find out the total number of duplicate
 * elements.
 */
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *arr, *arr1;
    int n, k=0;  /* `k` keeps count of # of elements in `arr1` */
    int dups=0;  /* keeps count of # of duplicate entries encountered */

    printf("Enter n: ");
    scanf("%d", &n);

    arr = malloc(n * sizeof *arr);
    arr1 = malloc(n * sizeof *arr1);  /* can have maximum of `n` elements */

    for (int i = 0; i < n; i++) {
        printf("arr[%d] = ", i);
        scanf("%d", &arr[i]);
    }

    for (int i = 0; i < n; i++) {
        int flag = 0;

        /* Scan to check if we've encountered `arr[i]` before */
        for (int j = 0; j < k; j++) {
            if (arr1[j] == arr[i]) {
                dups++;
                flag = 1;
                break;
            }
        }

        /* if not, add it to arr1 */
        if (!flag) {
            arr1[k++] = arr[i];
        }
    }

    free(arr);
    free(arr1);

    printf("Duplicate elements : %d\n", dups);

    return EXIT_SUCCESS;
}
