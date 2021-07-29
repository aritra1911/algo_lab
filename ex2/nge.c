/*
 * Write a program to replace every element in the array with the next greatest
 * element present in the same array.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *arr;
    int n, max;

    printf("Enter size of array: ");
    scanf("%d", &n);

    arr = malloc( n * sizeof *arr );

    printf("Enter elements of array:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    max = arr[n - 1];  /* second last element has only the last element after
                        * it, so it's the max */

    for (int i = n - 2; i >= 0; i--) {

        /* walk the array in reverse starting from the second last element,
         * replacing every element by max and also updating max as we walk. */

        int temp = arr[i];
        arr[i] = max;

        if ( temp > max )
            max = temp;
    }

    printf("Resultant array : %d", arr[0]);
    for (int i = 1; i < n; i++) {
        printf(" %d", arr[i]);
    }
    putchar('\n');

    free(arr);

    return EXIT_SUCCESS;
}
