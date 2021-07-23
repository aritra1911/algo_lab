/*
 * Write a program to store numbers into an array of n integers, where the array
 * must contain some duplicates. Find out the most repeating element in the
 * array.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *arr, *arr1, *arr2;
    int n, k=0;  /* `k` keeps count of # of elements in `arr1` */
    int most_repeating_idx;

    printf("Enter n: ");
    scanf("%d", &n);

    arr = malloc(n * sizeof *arr);
    arr1 = malloc(n * sizeof *arr1);  /* can have maximum of `n` elements */
    arr2 = malloc(n * sizeof *arr2);  /* can have maximum of `n` elements */

    for (int i = 0; i < n; i++) {
        printf("arr[%d] = ", i);
        scanf("%d", &arr[i]);
    }

    for (int i = 0; i < n; i++) {
        int flag = 0;

        /* Scan to check if we've encountered `arr[i]` before */
        for (int j = 0; j < k; j++) {
            if (arr1[j] == arr[i]) {
                arr2[j]++;  /* Increment frequency of jth element in arr1 */
                flag = 1;
                break;
            }
        }

        /* if not, add it to arr1 */
        if (!flag) {
            arr1[k] = arr[i];
            arr2[k] = 1;
            k++;
        }
    }

    free(arr);

    /* Assume the most repeating element is the first one encountered */
    most_repeating_idx = 0;

    for (int i = 0; i < k; i++) {
        if (arr2[most_repeating_idx] < arr2[i]) {
            most_repeating_idx = i;
        }
    }

    free(arr2);

    printf("Most repeating element : %d\n", arr1[most_repeating_idx]);

    free(arr1);

    return EXIT_SUCCESS;
}
