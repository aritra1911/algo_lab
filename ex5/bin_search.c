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
#include <time.h>

int bin_search(int item, int *arr, int len, int *counter)
{
    /* This algorithm assumes that `arr` is sorted in ascending order */
    if ( counter ) (*counter)++;

    if ( len ) {
        int m = (len - 1) >> 1;

        if (arr[m] == item)
            return 0;

        if (arr[m] < item)
            return bin_search(item, arr + m + 1, len - m - 1, counter);

        return bin_search(item, arr, m, counter);
    }

    return -1;
}

int compare_asc(const void *p, const void *q)
{
    return *(int *)p - *(int *) q;
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

        if ( bin_search(item, arr, argc - 2, NULL) != -1 ) {
            printf("Found!\n");
        } else {
            printf("Not Found!\n");
        }

        free(arr);
    }

    printf("       n   Best Case   Worst Case   Average Case\n"
           "--------   ---------   ----------   ------------\n");

    for (int n = 1000000; n <= 10000000; n += 1000000) {

        struct timespec time_now;
        int average_counter = 0, best_counter = 0, worst_counter = 0;
        int x;

        /* Get the current time */
        clock_gettime(CLOCK_MONOTONIC, &time_now);

        /* Use current time's nanoseconds field to seed the RNG */
        srand((unsigned) time_now.tv_nsec);

        int *arr = malloc(n * sizeof *arr);

        /* Generate `n` random numbers and populate `arr` */
        for (int i = 0; i < n; i++) {
            arr[i] = rand();
        }

        /* Get the first element which shall land somewhere
         * else after sorting */
        x = arr[0];

        /* Using libc's standard `qsort()` sorting function */
        qsort(arr, n, sizeof *arr, compare_asc);

        /* Note: This recursive implementation of the
         * binary search algorithm is too fast to time
         * properly. At some point I gave up and did a
         * step counting approach which seems to work
         * better according to expectations. */

        /* Average case time complexity */
        if ( bin_search(x, arr, n, &average_counter) )
            fprintf(stderr, "Average case failed to find element\n");

        /* Worst case time complexity */
        x = arr[n - 1];
        if ( bin_search(x, arr, n, &worst_counter) )
            fprintf(stderr, "Worst case failed to find element\n");

        /* Best case time complexity */
        x = arr[(n - 1) >> 1];
        if ( bin_search(x, arr, n, &best_counter) )
            fprintf(stderr, "Best case failed to find element\n");

        free(arr);

        printf("%8i   %9i   %10i   %12i\n",
               n, best_counter, worst_counter, average_counter);
    }

    return EXIT_SUCCESS;
}
