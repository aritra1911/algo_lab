/*
 * The quick sort algorithm is an efficient and popular sorting technique that
 * sorts a list of keys recursively by choosing a pivot key. A pivot may be
 * chosen as the first or last or mean or median or any random element of the
 * list. Write a program to implement this sorting algorithm and execute the
 * sorting programs for the following sets of data.
 *       i. Ordered List
 *      ii. Reverse order List
 *     iii. A list containing the same value through out
 *      iv. Random List
 *       v. 50% of the List sorted
 * Also measure CPU time, number of partitions and number of comparisons for
 * data sizes 1K, 50K, 1L, 1.5L, 2L, 2.5L, 3L, 3.5L, 4L, 4.5L and 1M. Present
 * your results using tables and graphs.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int partition(int *arr, int len)
{
    int ret = 0;

    /* Taking the last element as pivot */
    int pivot = arr[len - 1];

    for (int i = 0; i < len - 1; i++) {

        /* Bring elements smaller than pivot
         * to the front of the array. */

        if ( arr[i] <= pivot ) {
            int temp = arr[i];
            arr[i] = arr[ret];
            arr[ret] = temp;
            ret++;
        }
    }

    /* Place the pivot at the juction of elements smaller
     * than pivot and elements greater than pivot */
    arr[len - 1] = arr[ret];
    arr[ret] = pivot;

    /* Return index of pivot */
    return ret;
}

void quick_sort(int *arr, int len)
{
    if ( len <= 1 ) return;
    int pi = partition(arr, len);
    quick_sort(arr, pi);
    quick_sort(arr + pi + 1, len - pi - 1);
}

void reverse(int *arr, int len)
{
    for (int i = 0; i < len / 2; i++) {
        int temp = arr[i];
        arr[i] = arr[len - i - 1];
        arr[len - i - 1] = temp;
    }
}

int main(int argc, char **argv)
{
    if ( argc > 1 ) {

        /* Handle a test via command line */

        int *arr = malloc((argc - 1) * sizeof *arr);

        for (int i = 1; i < argc; i++) {
            arr[i - 1] = atoi(argv[i]);
        }

        quick_sort(arr, argc - 1);

        printf("%i", arr[0]);
        for (int i = 1; i < argc - 1; i++)
            printf(" %i", arr[i]);

        free(arr);

        putchar('\n');
        return EXIT_SUCCESS;
    }

    int data_sizes[11] = {
        1000,     /* 1K   */
        50000,    /* 50K  */
        100000,   /* 1L   */
        150000,   /* 1.5L */
        200000,   /* 2L   */
        250000,   /* 2.5L */
        300000,   /* 3L   */
        350000,   /* 3.5L */
        400000,   /* 4L   */
        450000,   /* 4.5L */
        1000000,  /* 1M   */
    };

    printf("Data Size   Ordered       Reversed      Same          Random     50%% sorted\n"
           "---------   -----------   -----------   -----------   --------   -----------\n");

    for (int i = 0; i < 11; i++) {
        struct timespec time_now;
        double time_ord, time_rord, time_same, time_rand, time_50;
        clock_t start, end;

        /* Get the current time */
        clock_gettime(CLOCK_MONOTONIC, &time_now);

        /* Use current time's nanoseconds
         * field to initialize RNG seed */
        srand((unsigned) time_now.tv_nsec);

        int *arr = malloc(data_sizes[i] * sizeof *arr);

        /* Generate random numbers and populate `arr` */
        for (int j = 0; j < data_sizes[i]; j++)
            arr[j] = rand();

        /* Time sorting of random list of elements */
        start = clock();
        quick_sort(arr, data_sizes[i]);
        end = clock();
        time_rand = ((double) (end - start)) / CLOCKS_PER_SEC;

        /* Time sorting of ordered list of elements */
        start = clock();
        quick_sort(arr, data_sizes[i]);
        end = clock();
        time_ord = ((double) (end - start)) / CLOCKS_PER_SEC;

        /* Reverse the ordered list */
        reverse(arr, data_sizes[i]);

        /* Time sorting of reverse ordered list of elements */
        start = clock();
        quick_sort(arr, data_sizes[i]);
        end = clock();
        time_rord = ((double) (end - start)) / CLOCKS_PER_SEC;

        /* Randomize first half of the list */
        clock_gettime(CLOCK_MONOTONIC, &time_now);
        srand((unsigned) time_now.tv_nsec);
        for (int j = 0; j < data_sizes[i] / 2; j++)
            arr[j] = rand();

        /* Time sorting when 50% of the List is sorted */
        start = clock();
        quick_sort(arr, data_sizes[i]);
        end = clock();
        time_50 = ((double) (end - start)) / CLOCKS_PER_SEC;

        /* Take the first element and fill
         * the entire array with that */
        for (int j = 1; j < data_sizes[i]; j++)
            arr[j] = arr[0];

        /* Time sorting a list containing the same value */
        start = clock();
        quick_sort(arr, data_sizes[i]);
        end = clock();
        time_same = ((double) (end - start)) / CLOCKS_PER_SEC;

        free(arr);

        printf("%9i   %11.6lf   %11.6f   %11.6f   %8.6f   %11.6f\n",
               data_sizes[i], time_ord, time_rord,
               time_same, time_rand, time_50);
    }

    return EXIT_SUCCESS;
}
