#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SORTED_ASC 1
#define SORTED_DESC 2
#define POPULATED 4

void insertion_sort(int *arr, int len)
{
    for (int i = 1; i < len; i++) {
        int key = arr[i];
        int j = i - 1;

        while ( j >= 0 && arr[j] > key ) {
            arr[j+1] = arr[j];
            j--;
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
    int *arr = NULL;
    int n=0, flags=0;
    clock_t start, end;

    printf("INSERTION SORT MENU\n"
           "0. Quit\n\n"
           "1. n Random numbers => Array\n\n"
           "2. Display the Array\n\n"
           "3. Sort the Array in Ascending Order by using Insertion Sort\n"
           "   Algorithm\n\n"
           "4. Sort the Array in Descending Order by using any sorting\n"
           "   algorithm\n\n"
           "5. Time Complexity to sort ascending of random data\n\n"
           "6. Time Complexity to sort ascending of data already sorted in\n"
           "   ascending order\n\n"
           "7. Time Complexity to sort ascending of data already sorted in\n"
           "   descending order\n\n"
           "8. Time Complexity to sort ascending of data for all Cases\n"
           "   (Data Ascending, Data in Descending & Random Data) in\n"
           "   Tabular form for values n=5000 to 50000, step=5000\n\n");

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

                /* int limit = ((unsigned int)1 << (8 * sizeof (int) - 1)) - 1; */

                if ( flags & POPULATED ) free(arr);
                arr = malloc(n * sizeof *arr);
                flags |= POPULATED;

                for (int i = 0; i < n; i++) {
                    /* Forgetting about limits for now */
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
                insertion_sort(arr, n);
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

                start = clock();
                insertion_sort(arr, n);
                end = clock();

                flags |= SORTED_ASC;

                printf("Array sorted in ascending order.\n"
                       "Time taken : %lf seconds\n",
                       ((double) (end - start)) / CLOCKS_PER_SEC);

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

                start = clock();
                insertion_sort(arr, n);
                end = clock();

                printf("Array already sorted in ascending order, "
                       "sorted again in ascending order.\n"
                       "Time taken : %lf seconds\n",
                       ((double) (end - start)) / CLOCKS_PER_SEC);

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

                start = clock();
                insertion_sort(arr, n);
                end = clock();

                printf("Array already sorted in descending order, "
                       "sorted again but in ascending order.\n"
                       "Time taken : %lf seconds\n",
                       ((double) (end - start)) / CLOCKS_PER_SEC);

                break;

            case EOF: printf("0\n");
            default: goto _exit;
        }
    }

_exit:
    if ( flags & POPULATED ) free(arr);
    return EXIT_SUCCESS;
}

/* Testing main function */
int _main(void)
{
    /* For testing only */
    int arr[] = { 5, 4, 6, 2, 9, 3 };
    clock_t start, end;

    start = clock();
    insertion_sort( arr, 6 );
    end = clock();

    for (int i = 0; i < 6; i++) {
        printf("%d ", arr[i]);
    }

    printf("\nTime taken : %lf seconds\n",
           ((double) (end - start)) / CLOCKS_PER_SEC);

    return EXIT_SUCCESS;
}
