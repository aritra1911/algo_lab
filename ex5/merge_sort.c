/*
 * Write a program to sort a list of n elements using the Merge Sort method and
 * determine the time required to sort the elements. Repeat the experiment for
 * different values of n and different nature of data (random data, sorted data,
 * reversely sorted data) in the list. n is the user input and n integers can be
 * generated randomly. Finally plot a graph of the time taken versus n.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void merge(int *, int, int);
void merge_sort(int *, int);

void merge(int *arr, int m, int len)
{
    int p = 0, q = m;
    int l = 0;

    int *temp_arr = malloc(len * sizeof *temp_arr);

    while ( p < m && q < len ) {
        if (arr[p] <= arr[q])
            temp_arr[l++] = arr[p++];
        else
            temp_arr[l++] = arr[q++];
    }

    while ( p < m )
        temp_arr[l++] = arr[p++];

    while ( q < len )
        temp_arr[l++] = arr[q++];

    memcpy(arr, temp_arr, len * sizeof *temp_arr);
    free(temp_arr);
}

void merge_sort(int *arr, int len)
{
    if ( len <= 1 ) return;
    int m = len >> 1;
    merge_sort(arr, m);
    merge_sort(arr + m, len - m);
    merge(arr, m, len);
}

int main(int argc, char** argv)
{
    if ( argc > 1 ) {

        /* Handle a test via command line */

        int *arr = malloc((argc - 1) * sizeof *arr);

        for (int i = 1; i < argc; i++) {
            arr[i - 1] = atoi(argv[i]);
        }

        merge_sort(arr, argc - 1);

        printf("%i", arr[0]);
        for (int i = 1; i < argc - 1; i++)
            printf(" %i", arr[i]);

        free(arr);

        putchar('\n');
        return EXIT_SUCCESS;
    }

    printf("     n   Time taken\n"
           "------   ----------\n");

    for (int n = 100000; n <= 500000; n += 50000) {

        struct timespec time_now;

        /* Get the current time */
        clock_gettime(CLOCK_MONOTONIC, &time_now);

        /* Use current time's nanoseconds field to initialize RNG seed */
        srand((unsigned) time_now.tv_nsec);

        int *arr = malloc(n * sizeof *arr);

        /* Generate `n` random numbers and populate `arr` */
        for (int i = 0; i < n; i++)
            arr[i] = rand();

        clock_t start = clock();
        merge_sort(arr, n);
        clock_t end = clock();

        free(arr);

        printf("%6i   %10lf\n", n,
               ((double) (end - start)) / CLOCKS_PER_SEC);
    }

    return EXIT_SUCCESS;
}
