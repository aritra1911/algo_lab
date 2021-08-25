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

        return bin_search(item, arr, len - m - 1);
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

        if ( bin_search(item, arr, argc - 2) != -1 ) {
            printf("Found!\n");
        } else {
            printf("Not Found!\n");
        }

        free(arr);
        return EXIT_SUCCESS;
    }

    printf("       n   Best Case   Worst Case   Average Case\n"
           "--------   ---------   ----------   ------------\n");

    for (int n = 100000000; n <= 500000000; n += 50000000) {

        struct timespec time_now;
        clock_t start, end;
        double best_time, worst_time, average_time;

        /* Get the current time */
        clock_gettime(CLOCK_MONOTONIC, &time_now);

        /* Use current time's nanoseconds field to seed the RNG */
        srand((unsigned) time_now.tv_nsec);

        int *arr = malloc(n * sizeof *arr);

        /* Generate `n` unique random numbers and populate `arr` */
        for (int i = 0; i < n; i++) {
            /*
            int rand_elem = rand();

            * Perform a linear search *
            for (int j = 0; j < i; j++) {
                if (arr[j] == rand_elem) {
                    * If same element found, generate a new one *
                    rand_elem = rand();
                    j = -1;  * and reperform search *
                }
            }
            arr[i] = rand_elem;
            */
            arr[i] = rand();
        }

        /* We shall use libc's standard `qsort()` sorting function */
        qsort(arr, n, sizeof *arr, compare_asc);

        /* Best case time complexity */
        start = clock();
        if ( bin_search(arr[(n - 1) >> 1], arr, n) ) {
            fprintf(stderr, "Best case failed to find element\n");
        }
        end = clock();
        best_time = ((double) (end - start)) / CLOCKS_PER_SEC;

        /* Worst case time complexity */
        start = clock();
        if ( bin_search(arr[0], arr, n) ) {
            fprintf(stderr, "Worst case failed to find element\n");
        }
        end = clock();
        worst_time = ((double) (end - start)) / CLOCKS_PER_SEC;

        /* Average case time complexity */
        start = clock();
        if ( bin_search(arr[rand() % n], arr, n) ) {
            fprintf(stderr, "Average case failed to find element\n");
        }
        end = clock();
        average_time = ((double) (end - start)) / CLOCKS_PER_SEC;

        free(arr);
/*
    printf("     n   Best Case   Worst Case   Average Case\n"
           "------   ---------   ----------   ------------\n");
*/

        printf("%9i   %.15lf   %.15lf   %.15lf\n", n,
               best_time, worst_time, average_time);
    }

    return EXIT_SUCCESS;
}
