/*
 * Write a program to swap pair of elements of an array of n integers from
 * starting. If n is odd, then last number will be remain unchanged.
 */

#include <stdio.h>
#include <stdlib.h>

#define SWAP(x,y) swap(&x, &y)

void swap(int*, int*);

int main(void)
{
    int* arr;
    int n;

    printf("Enter n: ");
    scanf("%d", &n);

    arr = malloc(n * sizeof *arr);

    for (int i = 0; i < n; i++) {
        printf("arr[%d] = ", i);
        scanf("%d", &arr[i]);
    }

    for (int i=0; i < (n / 2); i++) {
        SWAP(arr[2 * i], arr[2*i + 1]);
    }

    /* Display the result */
    printf("\nResult : %d", arr[0]);
    for (int i = 1; i < n; i++) {
        printf(" %d", arr[i]);
    }

    free(arr);
    printf("\n");

    return EXIT_SUCCESS;
}

void swap(int* x, int* y)
{
    int z = *x;
    *x = *y;
    *y = z;
}
