/*
 * Write a program to display an array of n integers (n>1), where at every index
 * of the array should contain the product of all elements in the array except
 * the element at the given index. Solve this problem by taking single loop and
 * without an additional array.
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int* arr;
    int n, product;

    printf("Enter n: ");
    scanf("%d", &n);

    arr = malloc(n * sizeof *arr);

    for (int i = 0; i < n; i++) {
        printf("arr[%d] = ", i);
        scanf("%d", &arr[i]);
    }

    /* Calculate product of all elements in the array */
    product = 1;
    for (int i = 0; i < n; i++) {
        product *= arr[i];
    }

    /* Divide product by each element and store the result in place of that
     * element. */
    for (int i = 0; i < n; i++) {
        arr[i] = product / arr[i];
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
