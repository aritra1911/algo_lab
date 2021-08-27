/*
 * Write a program to use divide and conquer method to determine the time
 * required to find the maximum and minimum element in a list of n elements. The
 * data for the list can be generated randomly. Compare this time with the time
 * taken by straight forward algorithm or brute force algorithm for finding the
 * maximum and minimum element for the same list of n elements. Show the
 * comparison by plotting a required graph for this problem.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX(x, y) ( x > y ? x : y )
#define MIN(x, y) ( x < y ? x : y )

int dc_max(int *, int);
int dc_min(int *, int);
int bf_max(int *, int);
int bf_min(int *, int);

int dc_max(int *arr, int len)
{
    if ( len == 1 )
        return arr[0];

    int         m = len >> 1;
    int  left_max = dc_max(arr, m);
    int right_max = dc_max(arr + m, len - m);

    return MAX(left_max, right_max);
}

int dc_min(int *arr, int len)
{
    if ( len == 1 )
        return arr[0];

    int         m = len >> 1;
    int  left_min = dc_min(arr, m);
    int right_min = dc_min(arr + m, len - m);

    return MIN(left_min, right_min);
}

int bf_max(int *arr, int len)
{
    int max_item = arr[0];

    for (int i = 1; i < len; i++) {
        if (arr[i] > max_item)
            max_item = arr[i];
    }

    return max_item;
}

int bf_min(int *arr, int len)
{
    int min_item = arr[0];

    for (int i = 1; i < len; i++) {
        if (arr[i] < min_item)
            min_item = arr[i];
    }

    return min_item;
}

int main(int argc, char** argv)
{
    if ( argc > 2 ) {

        /* Handle a test via command line */

        int *arr = malloc((argc - 2) * sizeof *arr);

        for (int i = 2; i < argc; i++) {
            arr[i - 2] = atoi(argv[i]);
        }

        if ( !strcmp(argv[1], "max") )
            printf("%i\n", dc_max(arr, argc - 2));
        else
            printf("%i\n", dc_min(arr, argc - 2));

        free(arr);

        return EXIT_SUCCESS;
    }

    printf("     n   Divide & Conquer   Brute Force\n"
           "------   ----------------   -----------\n");

    for (int n = 100000; n <= 500000; n += 50000) {

        struct timespec time_now;
        clock_t start, end;
        double dc_time, bf_time;

        /* Get the current time */
        clock_gettime(CLOCK_MONOTONIC, &time_now);

        /* Use current time's nanoseconds field to initialize RNG seed */
        srand((unsigned) time_now.tv_nsec);

        int *arr = malloc(n * sizeof *arr);

        /* Generate `n` random numbers and populate `arr` */
        for (int i = 0; i < n; i++)
            arr[i] = rand();

        start = clock();
        dc_max(arr, n); dc_min(arr, n);
        end = clock();
        dc_time = ((double) (end - start)) / CLOCKS_PER_SEC;

        start = clock();
        bf_max(arr, n); bf_min(arr, n);
        end = clock();
        bf_time = ((double) (end - start)) / CLOCKS_PER_SEC;

        free(arr);

        printf("%6i   %16lf   %11lf\n",
               n, dc_time, bf_time);
    }

    return EXIT_SUCCESS;
}
