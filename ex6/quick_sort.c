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

    return EXIT_SUCCESS;
}
