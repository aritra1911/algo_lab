/*
 * Write a program to search an element x in an array of n integers using Binary
 * Search algorithm that uses divide and conquer technique. Find out the best
 * case, worst case and average case time complexities for different values of n
 * and plot a graph of the time taken versus n. The n integers can be generated
 * randomly and x can be choosen randomly, or any element of the array or middle
 * or last element of the array depending on type of time complexity analysis.
 */

#include <stdio.h>
#include <stdlib.h>

int bin_search(int item, int *arr, int len)
{
    /* This algorithm assumes that `arr` is sorted in ascending order */

    if ( len ) {
        int m = (len - 1) >> 1;

        if (arr[m] == item)
            return 0;

        if (arr[m] < item)
            return bin_search(item, arr + m + 1, len - m - 1);

        return bin_search(item, arr, len - m - 1);
    }

    return -1;
}

int main(int argc, char** argv)
{
    if ( argc > 2 ) {

        /* Handle a test via command line */

        int item = atoi(argv[1]);
        int *arr = malloc((argc - 2) * sizeof *arr);

        for (int i = 2; i < argc; i++) {
            arr[i - 2] = atoi(argv[i]);
        }

        if ( bin_search(item, arr, argc - 2) != -1 ) {
            printf("Found!\n");
        } else {
            printf("Not Found!\n");
        }

        free(arr);
    }

    return EXIT_SUCCESS;
}
