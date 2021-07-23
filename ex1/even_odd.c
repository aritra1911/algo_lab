/*
 * Write a program to rearrange the elements of an array of n integers such that
 * all even numbers are followed by all odd numbers.
 */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int* arr;
    int n, k=0, key;

    printf("Enter n: ");
    scanf("%d", &n);

    arr = malloc(n * sizeof *arr);

    for (int i = 0; i < n; i++) {
        printf("arr[%d] = ", i);
        scanf("%d", &arr[i]);
    }

    for (int i = 0; i < n; i++) {
        /* If we encounter an even number, shift all the odd numbers to the
         * right and place the number right before the sequence of odd numbers
         * start. `k` marks the start of the odd number sequence. */
        if ( (arr[i] & 1) != 1 ) {
            /* save even number as it's going to get overwritten as we shift the
             * odd numbers */
            key = arr[i];

            /* shift odd numbers */
            for (int j = i; j > k; j--) {
                arr[j] = arr[j-1];
            }

            /* place the even number in the place where the first odd number was
             * and increment the start of the odd number sequence. */
            arr[k] = key;
            k++;
        }
    }

    /* Display the result */
    printf("\nRearranged array : %d", arr[0]);
    for (int i = 1; i < n; i++) {
        printf(" %d", arr[i]);
    }

    free(arr);
    printf("\n");

    return EXIT_SUCCESS;
}
