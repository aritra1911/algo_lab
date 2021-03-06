/*
 * Write a menu driven program as given below, to sort an array of n integers in
 * ascending order by insertion sort algorithm and determine the time required
 * (in terms of step/frequency count) to sort the elements. Repeat the
 * experiment for different values of n and different nature of data (i.e.apply
 * insertion sort algorithm on the data of array that are already sorted,
 * reversly sorted and random data). Finally plot a graph of the time taken
 * versus n for each type of data. The elements can be read from a file or can
 * be generated using the random number generator.
 *
 *                     INSERTION SORT MENU
 *
 * 0. Quit
 * 1. n Random numbers=>Array
 * 2. Display the Array
 * 3. Sort the Array in Ascending Order by using Insertion Sort
 *    Algorithm
 * 4. Sort the Array in Descending Order by using any sorting
 *    algorithm
 * 5. Time Complexity to sort ascending of random data
 * 6. Time Complexity to sort ascending of data already sorted in
 *    ascending order
 * 7. Time Complexity to sort ascending of data already sorted in
 *    descending order
 * 8. Time Complexity to sort ascending of data for all Cases (Data
 *    Ascending, Data in Descending & Random Data) in Tabular form
 *    for values n=5000 to 50000, step=5000
 * Enter your choice:
 * If the choice is option 8, the it will display the tabular form as follows:
 *
 *              Analysis of Insertion Sort Algorithm
 * Sl.   Value   Time Complexity   Time Complexity   Time Complexity
 * No.   of n       (Data in          (Data in        (Random Data)
 *                  Ascending)       Descending)
 * -----------------------------------------------------------------
 *   1    5000
 *   2   10000
 *   3   15000
 *   4   20000
 *   5   25000
 *   6   30000
 *   7   35000
 *   8   40000
 *   9   45000
 *  10   50000
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SORTED_ASC 1
#define SORTED_DESC 2
#define POPULATED 4

void insertion_sort(int *, int, int *);
int compare_desc(const void *, const void *);

void insertion_sort(int *arr, int len, int *counter)
{
    if ( counter ) (*counter)++;

    for (int i = 1; i < len; i++) {
        int key = arr[i];
        int j = i - 1;

        if ( counter ) (*counter)++;

        while ( j >= 0 && arr[j] > key ) {
            arr[j+1] = arr[j];
            j--;

            if ( counter ) (*counter)++;
        }

        arr[j+1] = key;
    }
}

int compare_desc(const void *p, const void *q)
{
    /* Compare function to sort an array in descending order using libc's
     * built-in `qsort()` function */

    int x = *((int *) p);
    int y = *((int *) q);

    return ( x < y ) ? 1 : ( x == y ) ? 0 : -1;
}

int main(void)
{
    int *arr;
    int n=0, flags=0;
    int step_counter;

    printf("--------------------------------------------------------------\n"
           "                     INSERTION SORT MENU\n"
           "0. Quit\n"
           "1. n Random numbers => Array\n"
           "2. Display the Array\n"
           "3. Sort the Array in Ascending Order by using Insertion Sort\n"
           "   Algorithm\n"
           "4. Sort the Array in Descending Order by using any sorting\n"
           "   algorithm\n"
           "5. Time Complexity to sort ascending of random data\n"
           "6. Time Complexity to sort ascending of data already sorted in\n"
           "   ascending order\n"
           "7. Time Complexity to sort ascending of data already sorted in\n"
           "   descending order\n"
           "8. Time Complexity to sort ascending of data for all Cases\n"
           "   (Data Ascending, Data in Descending & Random Data) in\n"
           "   Tabular form for values n=5000 to 50000, step=5000\n"
           "--------------------------------------------------------------\n");

    while ( 1 ) {
        printf("> ");
        switch (getchar()) {
            case '\n': break;
            case '1':
                printf("Enter n: ");
                scanf("%d", &n);
                getchar();  /* eat trailing newline */

                /* Initialize RNG seed */
                srand((unsigned) time(NULL));

                if ( flags & POPULATED ) free(arr);
                arr = malloc(n * sizeof *arr);
                flags |= POPULATED;

                for (int i = 0; i < n; i++) {
                    arr[i] = rand();
                }
                printf("Generated %d random integers and populated into array.\n", n);

                /* Clear sorted flags */
                flags &= ~(SORTED_ASC | SORTED_DESC);

                break;

            case '2':
                getchar();  /* eat trailing newline */
                if ( !(flags & POPULATED) ) {
                    printf("Array not populated yet.\n");
                    break;
                }

                printf("Array : %d", arr[0]);
                for (int i = 1; i < n; i++) {
                    printf(" %d", arr[i]);
                }
                putchar('\n');

                break;

            case '3':
                getchar();  /* eat trailing newline */
                if ( !(flags & POPULATED) ) {
                    printf("Array not populated yet.\n");
                    break;
                }

                flags &= ~SORTED_DESC;
                insertion_sort(arr, n, NULL);
                printf("Array sorted in ascending order.\n");
                flags |= SORTED_ASC;

                break;

            case '4':
                getchar();  /* eat trailing newline */
                if ( !(flags & POPULATED) ) {
                    printf("Array not populated yet.\n");
                    break;
                }

                flags &= ~SORTED_ASC;

                /* Note that despite its name, `qsort()` may or may not be a
                 * quicksort implementation. See:
                 * http://calmerthanyouare.org/2013/05/31/qsort-shootout.html */
                qsort(arr, n, sizeof *arr, compare_desc);
                printf("Array sorted in descending order"
                       " (using `qsort()`).\n");
                flags |= SORTED_DESC;

                break;

            case '5':
                getchar();  /* eat trailing newline */
                if ( !(flags & POPULATED) ) {
                    printf("Array not populated yet.\n");
                    break;
                }

                if ( flags & SORTED_ASC ) {
                    printf("Array is already sorted in ascending order.\n");
                    break;
                }

                if ( flags & SORTED_DESC ) {
                    printf("Array is already sorted in descending order.\n");
                    break;
                }

                step_counter = 0;
                insertion_sort(arr, n, &step_counter);

                flags |= SORTED_ASC;

                printf("Array sorted in ascending order.\n"
                       "Steps taken : %d\n", step_counter);

                break;

            case '6':
                getchar();  /* eat trailing newline */
                if ( !(flags & POPULATED) ) {
                    printf("Array not populated yet.\n");
                    break;
                }

                if ( !(flags & SORTED_ASC) && !(flags & SORTED_DESC) ) {
                    printf("Array isn't sorted in any order yet. "
                           "Sort it in ascending order first.\n");
                    break;
                }

                if ( flags & SORTED_DESC ) {
                    printf("Array is sorted in descending order. "
                           "Sort it in ascending order first.\n");
                    break;
                }

                step_counter = 0;
                insertion_sort(arr, n, &step_counter);

                printf("Array already sorted in ascending order, "
                       "sorted again in ascending order.\n"
                       "Steps taken : %d\n", step_counter);

                break;

            case '7':
                getchar();  /* eat trailing newline */
                if ( !(flags & POPULATED) ) {
                    printf("Array not populated yet.\n");
                    break;
                }

                if ( !(flags & SORTED_ASC) && !(flags & SORTED_DESC) ) {
                    printf("Array isn't sorted in any order yet. "
                           "Sort it in descending order first.\n");
                    break;
                }

                if ( flags & SORTED_ASC ) {
                    printf("Array is sorted in ascending order. "
                           "Sort it in descending order first.\n");
                    break;
                }

                step_counter = 0;
                insertion_sort(arr, n, &step_counter);
                flags &= ~SORTED_DESC;
                flags |= SORTED_ASC;

                printf("Array already sorted in descending order, "
                       "sorted again but in ascending order.\n"
                       "Steps taken : %d\n", step_counter);

                break;

            case '8':
                getchar();  /* eat trailing newline */

                /* print header */
                printf("             Analysis of Insertion Sort Algorithm\n"
                       "Sl.   Value   Time Complexity   Time Complexity   Time "
                       "Complexity\nNo.   of n       (Data in          (Data in"
                       "        (Random Data)\n                 Ascending)     "
                       "  Descending)\n----------------------------------------"
                       "-------------------------\n");

                int slno = 1;
                for (int n = 5000; n <= 50000; n += 5000) {
                    /* Initialize RNG seed */
                    srand((unsigned) time(NULL));

                    int *arr = malloc(n * sizeof *arr);

                    /* Generate `n` random numbers */
                    for (int i = 0; i < n; i++) {
                        arr[i] = rand();
                    }

                    /* Time sorting in ascending */
                    int rand_counter = 0;
                    insertion_sort(arr, n, &rand_counter);

                    /* Time sorting in ascending again */
                    int asc_counter = 0;
                    insertion_sort(arr, n, &asc_counter);

                    /* Sort that in descending */
                    qsort(arr, n, sizeof *arr, compare_desc);

                    /* Sort the descending back in ascending */
                    int desc_counter = 0;
                    insertion_sort(arr, n, &desc_counter);

                    printf("%3d   %5d   %15d   %15d   %15d\n",
                           slno++, n, asc_counter, desc_counter, rand_counter);

                    free(arr);
                }

                break;

            case EOF: printf("Quitting...\n");
            default: goto _exit;
        }
    }

_exit:
    if ( flags & POPULATED ) free(arr);
    return EXIT_SUCCESS;
}
