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

int bin_search(int, int *, int);
int compare_asc(const void *, const void *);

int bin_search(int item, int *arr, int len)
{
    /* This algorithm assumes that `arr` is sorted in ascending order */

    if ( len ) {
        int m = (len - 1) >> 1;

        if (arr[m] == item)
            return 0;

        if (arr[m] < item)
            return bin_search(item, arr + m + 1, len - m - 1);

        return bin_search(item, arr, m);
    }

    return -1;
}

int compare_asc(const void *p, const void *q)
{
    return *(int *)p - *(int *) q;
}

long timediff( struct timespec start_time,
               struct timespec end_time )
{

    struct timespec temp;
    long s, n;

    if ( ( end_time.tv_nsec - start_time.tv_nsec ) < 0 ) {
        /* make a full second adjustment to tv_sec */
        temp.tv_sec = end_time.tv_sec - start_time.tv_sec - 1;
        /* we have to add a full second to temp.tv_nsec */
        temp.tv_nsec = 1000000000
                     + end_time.tv_nsec - start_time.tv_nsec;

    } else {

        temp.tv_sec = end_time.tv_sec - start_time.tv_sec;
        temp.tv_nsec = end_time.tv_nsec - start_time.tv_nsec;

    }
    s = (long) temp.tv_sec;
    n = (long) temp.tv_nsec;
    return ( s * (long)1000000000 + n );
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
        return EXIT_SUCCESS;
    }

    printf("      n   Best Case   Worst Case   Average Case\n"
           "-------   ---------   ----------   ------------\n");

    for (int n = 1000000; n <= 10000000; n += 1000000) {

        struct timespec time_now;
        struct timespec start, end;
        long best_time, worst_time, average_time;
        int x;

        /* Get the current time */
        clock_gettime(CLOCK_MONOTONIC, &time_now);

        /* Use current time's nanoseconds field to seed the RNG */
        srand((unsigned int) time_now.tv_nsec);

        int *arr = malloc(n * sizeof *arr);

        /* Generate `n` unique random numbers and populate `arr` */
        for (int i = 0; i < n; i++) {
            arr[i] = rand();
        }

        /* Get the first element which shall land somewhere
         * else after sorting */
        x = arr[0];

        /* We shall use libc's standard `qsort()` sorting function */
        qsort(arr, n, sizeof *arr, compare_asc);

        /* Average case time complexity */
        clock_gettime(CLOCK_MONOTONIC, &start);
        if ( bin_search(x, arr, n) ) {
            fprintf(stderr, "Average case failed to find element\n");
        }
        clock_gettime(CLOCK_MONOTONIC, &end);
        average_time = timediff(start, end);

        /* Worst case time complexity */
        x = arr[n - 1];
        clock_gettime(CLOCK_MONOTONIC, &start);
        if ( bin_search(x, arr, n) ) {
            fprintf(stderr, "Worst case failed to find element\n");
        }
        clock_gettime(CLOCK_MONOTONIC, &end);
        worst_time = timediff(start, end);

        /* Best case time complexity */
        x = arr[(n - 1) >> 1];  /* The middle element */
        clock_gettime(CLOCK_MONOTONIC, &start);
        if ( bin_search(x, arr, n) ) {
            fprintf(stderr, "Best case failed to find element\n");
        }
        clock_gettime(CLOCK_MONOTONIC, &end);
        best_time = timediff(start, end);

        free(arr);

        printf("%8i   %9li   %10li   %12li\n", n,
               best_time, worst_time, average_time);
    }

    return EXIT_SUCCESS;
}
