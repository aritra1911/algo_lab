/*
 * Refer the following new sort algorithm for sorting an array A of n numbers.
 * The algorithm is described below:
 *
 *     (  i) If there is only one number, return.
 *
 *     ( ii) If there are two numbers, perform a single comparison to determine
 *           the order.
 *
 *     (iii) If there are more than two numbers, then first sort the top
 *           two-thirds of the elements recursively. Follow this by sorting the
 *           bottom two-thirds of the elements recursively and then sorting the
 *           top two-thirds of the elements again.
 *
 * a) Write a program that uses a recursive algorithm to implement the above
 *    strategy.
 *
 * b) What is the comparison complexity of this new-sort algorithm? Formulate a
 *    recurrence relation and solve the same to justify your answer.
 */

/* Looks like part (b) has nothing to do with programming, so we shall
 * procrastinate, i.e. handle it in post-programming phase. */

#include <stdio.h>
#include <stdlib.h>

static void new_sort(int *, int);

static void new_sort(int *arr, int len)
{
    if ( len <= 1 ) return;

    if ( len == 2 ) {
        if ( arr[0] > arr[1] ) {
            int temp = arr[0];
            arr[0] = arr[1];
            arr[1] = temp;
        }
        return;
    }

    int one_third = len / 3;
    int two_thirds = len - one_third;

    new_sort(arr, two_thirds);
    new_sort(arr + one_third, len - one_third);
    new_sort(arr, two_thirds);
}

extern int main(int argc, char** argv)
{
    if ( argc > 1 ) {

        /* Handle a test via command line */

        int *arr = malloc((argc - 1) * sizeof *arr);

        for (int i = 1; i < argc; i++) {
            arr[i - 1] = atoi(argv[i]);
        }

        new_sort(arr, argc - 1);

        printf("%i", arr[0]);
        for (int i = 1; i < argc - 1; i++)
            printf(" %i", arr[i]);

        free(arr);

        putchar('\n');
    }

    return EXIT_SUCCESS;
}
