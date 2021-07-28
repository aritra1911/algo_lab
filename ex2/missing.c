/*
 * Given an array of n unique integers where each element in the array is in the
 * range [1, n]. The array has all distinct elements and the size of the array
 * is (n-1). Hence One number from the range is missing from this array. Find
 * that missing number.
 * Sample Test Case:
 * Input : 1, 3, 4, 5
 * Output : 2
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int* arr;
    int n;

    printf("Enter n: ");
    scanf("%d", &n);

    arr = malloc( (n - 1) * sizeof *arr );

    for (int i = 0; i < (n - 1); i++) {
        printf("arr[%d] = ", i);
        scanf("%d", &arr[i]);
    }

    /* Compute XOR of integers from 1 to n */
    int xor_acc;
    switch ( n & 3 ) {  /* `n & 3` is same as `n % 4` */
        case 1:  xor_acc = 1;     break;
        case 2:  xor_acc = n + 2; break;
        case 3:  xor_acc = 0;     break;
        default: xor_acc = n;
    }

    /* Compute XOR of integers in the array */
    int xor_arr = 0;
    for (int i = 0; i < (n - 1); i++) {
        xor_arr ^= arr[i];
    }

    free(arr);

    printf("Missing Element : %d\n", xor_arr ^ xor_acc);

    return EXIT_SUCCESS;
}
