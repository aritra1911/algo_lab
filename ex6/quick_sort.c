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
#include <pthread.h>
#include <assert.h>

#define TEST_CASES       11
#define SIXTYFOURM       67108864
#define MIN_REQ_SSIZE    SIXTYFOURM  /* 64 MB stack */
#define NANOSECS         1000000000

typedef struct {
    int size;
    double time_ord, time_rord, time_same, time_rand, time_50;
} TestData;

int partition(int *, int);
void quick_sort(int *, int);
int is_sorted(int *, int);
void reverse(int *, int);
double timediff(struct timespec, struct timespec);
void *test_case(void *);

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

int is_sorted(int *arr, int len)
{
    for (int i = 0; i < len - 1; i++) {
        if ( arr[i] > arr[i + 1] )
            return -1;
    }

    return 0;
}

void reverse(int *arr, int len)
{
    for (int i = 0; i < len / 2; i++) {
        int temp = arr[i];
        arr[i] = arr[len - i - 1];
        arr[len - i - 1] = temp;
    }
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

void *test_case(void *__data__)
{
    struct timespec time_now, start, end;

    /* Cast void * into something more usable */
    TestData *data = (TestData *) __data__;

    /* Get the current time */
    clock_gettime(CLOCK_MONOTONIC, &time_now);

    /* Use current time's nanoseconds
     * field to seed the RNG */
    srand48(time_now.tv_nsec);

    int *arr = malloc(data->size * sizeof *arr);

    /* Generate random numbers and populate `arr` */
    for (int j = 0; j < data->size; j++)
        arr[j] = lrand48();

    assert(is_sorted(arr, data->size) != 0);

    /* Time sorting of random list of elements */
    clock_gettime(CLOCK_MONOTONIC, &start);
    quick_sort(arr, data->size);
    clock_gettime(CLOCK_MONOTONIC, &end);
    data->time_rand = timediff(start, end);

    assert(is_sorted(arr, data->size) == 0);

    /* Time sorting of ordered list of elements */
    clock_gettime(CLOCK_MONOTONIC, &start);
    quick_sort(arr, data->size);
    clock_gettime(CLOCK_MONOTONIC, &end);
    data->time_ord = timediff(start, end);

    assert(is_sorted(arr, data->size) == 0);

    /* Reverse the ordered list */
    reverse(arr, data->size);

    assert(is_sorted(arr, data->size) != 0);

    /* Time sorting of reverse ordered list of elements */
    clock_gettime(CLOCK_MONOTONIC, &start);
    quick_sort(arr, data->size);
    clock_gettime(CLOCK_MONOTONIC, &end);
    data->time_rord = timediff(start, end);

    assert(is_sorted(arr, data->size) == 0);

    /* Randomize first half of the list */
    clock_gettime(CLOCK_MONOTONIC, &time_now);
    srand48(time_now.tv_nsec);
    for (int j = 0; j < data->size / 2; j++)
        arr[j] = lrand48();

    assert(is_sorted(arr, data->size) != 0);

    /* Time sorting when 50% of the List is sorted */
    clock_gettime(CLOCK_MONOTONIC, &start);
    quick_sort(arr, data->size);
    clock_gettime(CLOCK_MONOTONIC, &end);
    data->time_50 = timediff(start, end);

    assert(is_sorted(arr, data->size) == 0);

    /* Take the first element and fill
     * the entire array with that */
    for (int j = 1; j < data->size; j++)
        arr[j] = arr[0];

    assert(is_sorted(arr, data->size) == 0);

    /* Time sorting a list containing the same value */
    clock_gettime(CLOCK_MONOTONIC, &start);
    quick_sort(arr, data->size);
    clock_gettime(CLOCK_MONOTONIC, &end);
    data->time_same = timediff(start, end);

    assert(is_sorted(arr, data->size) == 0);

    free(arr);

    return NULL;
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

    int data_sizes[] = {
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

    pthread_t threads[TEST_CASES];
    pthread_attr_t stack_size_custom_attr;
    TestData thread_data[TEST_CASES];
    struct timespec creation_time, joining_time;

    pthread_attr_init(&stack_size_custom_attr);

#ifdef _POSIX_THREAD_ATTR_STACKSIZE
    size_t default_stack_size;

    pthread_attr_getstacksize(&stack_size_custom_attr,
                              &default_stack_size);

    if ( default_stack_size < MIN_REQ_SSIZE ) {

        printf(" WARN : Current stack size is %lu bytes,\n"
               "      : but we need at least %lu bytes,\n"
               "      : so we shall auto adjust that.\n",
                        default_stack_size, (size_t) MIN_REQ_SSIZE);

        pthread_attr_setstacksize(&stack_size_custom_attr,
                                  (size_t) MIN_REQ_SSIZE);
    }
#endif

    /* Dispatch threads */
    for (int i = 0; i < TEST_CASES; i++) {
        thread_data[i].size = data_sizes[i];
        pthread_create(&threads[i], &stack_size_custom_attr,
                       test_case, (void *) &thread_data[i]);
        printf(" INFO : Thread #%i dispatched with data size of %i\n",
                                 i,                   data_sizes[i]);
    }

    clock_gettime(CLOCK_MONOTONIC, &creation_time);

    /* Wait for threads to join */
    for (int i = 0; i < TEST_CASES; i++) {
        pthread_join(threads[i], NULL);
        clock_gettime(CLOCK_MONOTONIC, &joining_time);
        printf(" INFO : Thread #%i joined after %f seconds\n", i,
               timediff(creation_time, joining_time));
    }

    pthread_attr_destroy(&stack_size_custom_attr);
    putchar('\n');

    printf("Data Size   Ordered       Reversed      Same          Random     50%% sorted\n"
           "---------   -----------   -----------   -----------   --------   -----------\n");

    for (int i = 0; i < TEST_CASES; i++) {
        printf("%9i   %11.6lf   %11.6f   %11.6f   %8.6f   %11.6f\n",
               thread_data[i].size,      thread_data[i].time_ord,
               thread_data[i].time_rord, thread_data[i].time_same,
               thread_data[i].time_rand, thread_data[i].time_50);
    }

    return EXIT_SUCCESS;
}
