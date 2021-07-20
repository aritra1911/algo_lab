/*
 * Write a program to store numbers into an array of n integers and then find out the smallest and largest number stored
 * in it. n is the user input.
 */
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int* arr;
    int n, largest, smallest;

    printf("Enter n: ");
    scanf("%d", &n);

    arr = malloc(n * sizeof *arr);

    for (int i = 0; i < n; i++) {
        printf("arr[%d] = ", i);
        scanf("%d", &arr[i]);
    }

    /* Assume the first element is the largest and the smallest. */
    largest = arr[0];
    smallest = arr[0];

    for (int i = 0; i < n; i++) {
        if (arr[i] < smallest) {
            smallest = arr[i];
        }

        if (arr[i] > largest) {
            largest = arr[i];
        }
    }

    free(arr);

    printf("Smallest : %d\n", smallest);
    printf("Largest : %d\n", largest);

    return EXIT_SUCCESS;
}
