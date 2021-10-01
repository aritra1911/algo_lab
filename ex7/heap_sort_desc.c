/*
 * Similar to above program no.7.1, write a menu driven program to sort
 * an array of n integers in descending order by heap sort algorithm.
 * Hints: Use min heap and accordingly change the menu options.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define NANOSECS    1000000000

#define SORTED_ASC  ( 1 << 0 )
#define SORTED_DESC ( 1 << 1 )
#define POPULATED   ( 1 << 2 )

#define PARENT(i)      floor((i-1) / 2)
#define LEFT_CHILD(i)  2*i + 1
#define RIGHT_CHILD(i) 2*i + 2

void sift_down(int *, int, int);
void heapify(int *, int);
void heap_sort(int *, int);
int compare_asc(const void *, const void *);
double timediff(struct timespec, struct timespec);

/* Repair the heap whose root element is at index 'start',
 * assuming the heaps rooted at its children are valid */
void sift_down(int *a, int start, int end)
{
    int root = start;

    /* While the root has at least one child */
    while ( LEFT_CHILD(root) <= end ) {
        int
            child = LEFT_CHILD(root),  /* Left child of root */
            swap = root;  /* Keeps track of child to swap with */

        if ( a[swap] > a[child] )
            swap = child;

        /* If there is a right child and that child is lesser */
        if ( child+1 <= end && a[swap] > a[child+1] )
            swap = child + 1;

        if ( swap == root )
            /* The root holds the largest element. Since we assume the
             * heaps rooted at the children are valid, this means that
             * we are done. */
            return;
        else {
            int temp = a[root];
            a[root] = a[swap];
            a[swap] = temp;

            /* repeat to continue sifting down the child now */
            root = swap;
        }
    }
}

/* Put elements of 'a' in heap order, in-place */
void heapify(int *a, int count)
{
    /* start is assigned the index in 'a' of the last parent node
     *
     * the last element in a 0-based array is at index count-1;
     * find the parent of that element */
    int start = PARENT(count - 1);

    while ( start >= 0 ) {
        /* sift down the node at index 'start' to the proper place such
         * that all nodes below the start index are in heap order */
        sift_down(a, start, count - 1);

        /* go to the next parent node */
        start--;
    }
    /* after sifting down the root all nodes/elements are in heap order */
}

void heap_sort(int *a, int count)
{
    /* Build the heap in array a so that largest value is at the root */
    heapify(a, count);

    /* The following loop maintains the invariants
     * that a[0:end] is a heap and every element
     * beyond end is greater than everything before
     * it (so a[end:count] is in sorted order) */
    int end = count - 1;
    while ( end > 0 ) {
        /* a[0] is the root and largest value.
         * The swap moves it in front of the sorted elements. */
        int temp = a[end];
        a[end] = a[0];
        a[0] = temp;

        /* the heap size is reduced by one */
        end--;

        /* the swap ruined the heap property, so restore it */
        sift_down(a, 0, end);
    }
}

int compare_asc(const void *p, const void *q)
{
    /* Compare function to sort an array in descending
     * order using libc's built-in `qsort()` function */

    int x = *((int *) p);
    int y = *((int *) q);

    return ( x < y ) ? -1 : ( x == y ) ? 0 : 1;
}

double timediff(struct timespec start, struct timespec end)
{
    /*
     * Shamelessly copied from :
     * https://git.sr.ht/~blastwave/bw/tree/bw/item/time_and_date/timediff.c
     */

    struct timespec delta;

    if ( (end.tv_nsec - start.tv_nsec) < 0 ) {
        /* make a full second adjustment to tv_sec */
        delta.tv_sec = end.tv_sec - start.tv_sec - 1;
        /* we have to add a full second to delta.tv_nsec */
        delta.tv_nsec = NANOSECS + end.tv_nsec - start.tv_nsec;

    } else {
        delta.tv_sec = end.tv_sec - start.tv_sec;
        delta.tv_nsec = end.tv_nsec - start.tv_nsec;
    }

    return delta.tv_sec + (double) delta.tv_nsec / NANOSECS;
}

int main(void)
{
    int *arr = NULL;
    int n, capacity=0, flags=0;

    printf(
        "------------------------------------------------------------------\n"
        "                MIN-HEAP & PRIORITY QUEUE MENU\n"
        " 0. Quit\n"
        " 1. n Random numbers => Array\n"
        " 2. Display the Array\n"
        " 3. Sort the Array in Descending Order by using Min-Heap Sort\n"
        "    technique\n"
        " 4. Sort the Array in Ascending Order by using any algorithm\n"
        " 5. Time Complexity to sort descending of random data\n"
        " 6. Time Complexity to sort descending of data already sorted in\n"
        "    descending order\n"
        " 7. Time Complexity to sort descending of data already sorted in\n"
        "    ascending order\n"
        " 8. Time Complexity to sort descending all Cases (Data Descending,\n"
        "    Data in Ascending & Random Data) in Tabular form for\n"
        "    values n=5000 to 50000, step=5000\n"
        " 9. Extract largest element\n"
        "10. Replace value at a node with new value\n"
        "11. Insert a new element\n"
        "12. Delete an element\n"
        "------------------------------------------------------------------\n"
    );

    while ( 1 ) {
        printf("> ");
        switch (getchar()) {
            case '\n': break;
            case '1':
                switch (getchar()) {
                    case '\n': {
                        printf("Enter n: ");
                        scanf("%d", &n);
                        getchar();  /* eat trailing newline */

                        if ( !n ) break;

                        /* Seed RNG with current time's nanoseconds field */
                        struct timespec time_now;
                        clock_gettime(CLOCK_MONOTONIC, &time_now);
                        srand48(time_now.tv_nsec);

                        if ( flags & POPULATED ) {
                            if ( capacity < n ) {
                                capacity = n;
                                arr = realloc(arr, capacity * sizeof *arr);
                            }
                        } else {
                            capacity = n;
                            arr = malloc(capacity * sizeof *arr);
                        }

                        for (int i = 0; i < n; i++) {
                            arr[i] = lrand48();
                        }
                        printf("Generated %d random integers and populated into array.\n", n);
                        flags |= POPULATED;

                        /* Clear sorted flags */
                        flags &= ~(SORTED_ASC | SORTED_DESC);
                    } break;

                    case '0': {
                        getchar();  /* eat trailing newline */
                        if ( !(flags & POPULATED) ) {
                            printf("Array not populated yet.\n");
                            break;
                        }

                        int i;
                        printf("Enter node index: ");
                        scanf("%d", &i);
                        getchar();  /* eat trailing newline */

                        if ( i >= n ) {
                            printf("No such node exists!\n");
                            break;
                        }

                        printf("Enter new value: ");
                        scanf("%d", &arr[i]);
                        getchar();  /* eat trailing newline */

                        flags &= ~(SORTED_ASC | SORTED_DESC);
                    } break;

                    case '1':
                        if ( !(flags & POPULATED) ) {
                            capacity = 1;
                            n = 0;
                            arr = malloc(sizeof *arr);
                            flags |= POPULATED;
                        } else {
                            if ( capacity == n ) {
                                capacity *= 2;
                                arr = realloc(arr, capacity * sizeof *arr);
                            }
                        }

                        printf("Enter new number: ");
                        scanf("%i", &arr[n++]);
                        getchar();  /* eat trailing newline */

                        if ( n == 1 ) {
                            flags |= SORTED_ASC | SORTED_DESC;
                        } else {
                            flags &= ~(SORTED_ASC | SORTED_DESC);
                        }
                        break;

                    case '2': {
                        getchar();  /* eat trailing newline */

                        if ( !(flags & POPULATED) ) {
                            printf("Array not populated yet.\n");
                            break;
                        }

                        if ( !n ) {
                            printf("Error: Empty array\n");
                            break;
                        }

                        int i;
                        printf("Enter node index: ");
                        scanf("%d", &i);
                        getchar();  /* eat trailing newline */

                        if ( i >= n ) {
                            printf("No such node exists!\n");
                            break;
                        }

                        for (int j = i; j < n - 1; j++)
                            arr[j] = arr[j + 1];
                        n--;
                    } break;

                    default: goto _exit;
                } break;

            case '2':
                getchar();  /* eat trailing newline */
                if ( !(flags & POPULATED) ) {
                    printf("Array not populated yet.\n");
                    break;
                }

                if ( !n ) {
                    printf("Error: Empty array\n");
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

                if ( !n ) {
                    printf("Error: Empty array\n");
                    break;
                }

                flags &= ~SORTED_ASC;
                heap_sort(arr, n);
                printf("Array sorted in descending order.\n");
                flags |= SORTED_DESC;

                break;

            case '4':
                getchar();  /* eat trailing newline */
                if ( !(flags & POPULATED) ) {
                    printf("Array not populated yet.\n");
                    break;
                }

                if ( !n ) {
                    printf("Error: Empty array\n");
                    break;
                }

                flags &= ~SORTED_DESC;

                /* Note that despite its name, `qsort()` may or may not be a
                 * direct quicksort implementation. See:
                 * http://calmerthanyouare.org/2013/05/31/qsort-shootout.html */
                qsort(arr, n, sizeof *arr, compare_asc);
                printf("Array sorted in ascending order"
                       " (using `qsort()`).\n");
                flags |= SORTED_ASC;

                break;

            case '5': {
                getchar();  /* eat trailing newline */
                if ( !(flags & POPULATED) ) {
                    printf("Array not populated yet.\n");
                    break;
                }

                if ( !n ) {
                    printf("Error: Empty array\n");
                    break;
                }

                if ( flags & SORTED_DESC ) {
                    printf("Array is already sorted in descending order.\n");
                    break;
                }

                if ( flags & SORTED_ASC ) {
                    printf("Array is already sorted in ascending order.\n");
                    break;
                }

                struct timespec start, end;

                clock_gettime(CLOCK_MONOTONIC, &start);
                heap_sort(arr, n);
                clock_gettime(CLOCK_MONOTONIC, &end);

                flags |= SORTED_DESC;

                printf("Array sorted in ascending order.\n"
                       "Time taken : %lf seconds\n", timediff(start, end));

            } break;

            case '6': {
                getchar();  /* eat trailing newline */
                if ( !(flags & POPULATED) ) {
                    printf("Array not populated yet.\n");
                    break;
                }

                if ( !n ) {
                    printf("Error: Empty array\n");
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

                struct timespec start, end;

                clock_gettime(CLOCK_MONOTONIC, &start);
                heap_sort(arr, n);
                clock_gettime(CLOCK_MONOTONIC, &end);

                printf("Array already sorted in descending order, "
                       "sorted again in descending order.\n"
                       "Time taken : %lf seconds\n", timediff(start, end));

            } break;

            case '7': {
                getchar();  /* eat trailing newline */
                if ( !(flags & POPULATED) ) {
                    printf("Array not populated yet.\n");
                    break;
                }

                if ( !n ) {
                    printf("Error: Empty array\n");
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

                struct timespec start, end;

                clock_gettime(CLOCK_MONOTONIC, &start);
                heap_sort(arr, n);
                clock_gettime(CLOCK_MONOTONIC, &end);

                flags &= ~SORTED_ASC;
                flags |= SORTED_DESC;

                printf("Array already sorted in ascending order, "
                       "sorted again but in descending order.\n"
                       "Time taken : %lf seconds\n", timediff(start, end));

            } break;

            case '8':
                getchar();  /* eat trailing newline */

                /* print header */
                printf("             Analysis of Heap Sort Algorithm\n"
                       "Sl.   Value   Time Complexity   Time Complexity   Time "
                       "Complexity\nNo.   of n       (Data in          (Data in"
                       "        (Random Data)\n                Descending)     "
                       "   Ascending)\n----------------------------------------"
                       "-------------------------\n");

                int slno = 1;
                for (int n = 5000; n <= 50000; n += 5000) {

                    struct timespec time_now, start, end;
                    double rand_time, asc_time, desc_time;

                    /* Seed RNG using current time's nanoseconds field */
                    clock_gettime(CLOCK_MONOTONIC, &time_now);
                    srand48(time_now.tv_nsec);

                    int *arr = malloc(n * sizeof *arr);

                    /* Generate `n` random numbers */
                    for (int i = 0; i < n; i++) {
                        arr[i] = lrand48();
                    }

                    /* Time sorting in ascending */
                    clock_gettime(CLOCK_MONOTONIC, &start);
                    heap_sort(arr, n);
                    clock_gettime(CLOCK_MONOTONIC, &end);
                    rand_time = timediff(start, end);

                    /* Time sorting in ascending again */
                    clock_gettime(CLOCK_MONOTONIC, &start);
                    heap_sort(arr, n);
                    clock_gettime(CLOCK_MONOTONIC, &end);
                    desc_time = timediff(start, end);

                    /* Sort that in descending */
                    qsort(arr, n, sizeof *arr, compare_asc);

                    /* Sort the descending back in ascending */
                    clock_gettime(CLOCK_MONOTONIC, &start);
                    heap_sort(arr, n);
                    clock_gettime(CLOCK_MONOTONIC, &end);
                    asc_time = timediff(start, end);

                    printf("%3d   %5d   %15lf   %15lf   %15lf\n",
                           slno++, n, desc_time, asc_time, rand_time);

                    free(arr);
                }

                break;

            case '9':
                getchar();  /* eat trailing newline */

                if ( !(flags & POPULATED) ) {
                    printf("Array not populated yet.\n");
                    break;
                }

                if ( !n ) {
                    printf("Error: Empty array\n");
                    break;
                }

                if ( !(flags & SORTED_ASC) && !(flags & SORTED_DESC) ) {
                    printf("Array isn't sorted in any order yet. "
                           "Sort it in ascending order first.\n");
                    break;
                }

                if ( flags & SORTED_ASC ) {
                    printf("Largest element : %i\n", arr[--n]);
                    break;
                }

                if ( flags & SORTED_DESC ) {
                    printf("Warning: Since the array is sorted in descending, "
                           "this operation is rather expensive.\n");
                    printf("Largest element : %i\n", arr[0]);

                    for (int i = 1; i < n; i++)
                        arr[i - 1] = arr[i];
                    n--;
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
