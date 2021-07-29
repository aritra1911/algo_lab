/*
 * Write a program to find out the largest difference between two elements A[i]
 * and A[j] (A[j]- A[i]) of the array of integers A in O(n) time such that j>i.
 *
 * For example: Let A is an array of integers:
 * Sample Test Case:
 * if i=1, j=3, then diff = a[j] – a[i] = 8 – 3 = 5
 * if i=4, j=6, then diff = a[j] – a[i] = 3 – 9 = -6
 * ..........
 * ..........
 * if i=1, j=4, then diff = a[j] – a[i] = 9 – 3 = 6
 * ..........
 * ..........
 * 6 is the largest number between all the differences, that is the answer.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int* arr;
    int n, i, j, next_i;

    printf("Enter size of A: ");
    scanf("%d", &n);

    arr = malloc( n * sizeof *arr );

    printf("Enter elements of A in ascending order:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    next_i = i = 0;
    j = 1;  /* since always `j > i` */
    for (int k = 1; k < n; k++) {

        if ( arr[k] < arr[next_i] )  {
            /* save potential next value of `i` but don't change `i` itself yet
             * since that will violate the condition `j > i` */
            next_i = k;

        } else if ( arr[k] > arr[j] ) {
            /* we found a new value of `j` so it's now safe to transfer `next_i`
             * to `i` since it's still guaranteed to be less than `j`. */
            i = next_i;
            j = k;
        }
    }

    printf("\nLargest Difference : %d\n", arr[j] - arr[i]);

    free(arr);

    return EXIT_SUCCESS;
}
