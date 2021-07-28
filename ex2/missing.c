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

    arr = malloc( (n-1) * sizeof *arr );

    for (int i = 0; i < (n - 1); i++) {
        printf("arr[%d] = ", i);
        scanf("%d", &arr[i]);
    }

    /* TODO: XOR? */
    for (int i = 1; i <= n ; i++) {
        int flag = 0;
        for (int j = 0; j < (n - 1); j++) {
            if (arr[j] == i) {
                flag = 1;
                break;
            }
        }

        if (!flag) {
            printf("Missing Element : %d\n", i);
            break;
        }
    }

    free(arr);

    return EXIT_SUCCESS;
}
