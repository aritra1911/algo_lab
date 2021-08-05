/*
 * Write a program to find out GCD (greatest common divisor) using the following
 * three algorithms.
 *  a) Euclid’s algorithm
 *  b) Consecutive integer checking algorithm.
 *  c) Middle school procedure which makes use of common prime factors. For
 *     finding list of primes implement sieve of Eratosthenes algorithm.
 *
 * Find out which algorithm is faster for the following data. Estimate how many
 * times it willbe faster than the other two by step/frequency count method in
 * each case.
 *
 *   i. Find GCD of two numbers when both are very large i.e.GCD(31415, 14142)
 *      by applying each of the above algorithms.
 *
 *  ii. Find GCD of two numbers when one of them can be very large i.e.GCD(56,
 *      32566) or GCD(34218, 56) by applying each of the above algorithms.
 *
 * iii. Find GCD of two numbers when both are very small i.e.GCD(12,15) by
 *      applying each of the above algorithms.
 *
 *  iv. Find GCD of two numbers when both are same i.e.GCD(31415, 31415) or
 *      GCD(12, 12) by applying each of the above algorithms.
 *
 * Write the above data in the following format and decide which algorithm is
 * faster for the particular data.
 *
 * Sl.   Input                             GCD algorithm                   Remarks
 * No.   GCD(x, y)          Euclid’s    Consecutive        Middle school
 *                          algorithm   integer checking   procedure
 *                                      algorithm.         algorithm
 * -------------------------------------------------------------------------------
 *   1   GCD(31415, 14142)
 *   2   GCD(56, 32566)
 *   3   GCD(34218, 56)
 *   4   GCD(12,15)
 *   5   GCD(31415, 31415)
 *   6   GCD(12, 12)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MIN(x, y) ( (x < y) ? x : y )

struct Algorithm
{
    /* Shall contain the computed result after execution */

    char name[64];
    int x, y, res, step_counter;

    /* function pointer pointing to algorithm function to execute */
    int (*gcd)(int, int, int *);
};

int get_primes(int, int **, int *);
int euclid(int, int, int *);
int cic(int, int, int *);
int msp(int, int, int *);
void reset_counter(struct Algorithm *);
void compute_algo(struct Algorithm *);

int get_primes(int n, int **primes, int *counter)
{
    /* Sieve of Eratosthenes */

    char *a = calloc(n - 1, sizeof *a);
    *primes = malloc((n - 1) * sizeof *primes);

    (*counter)++;

    int limit = sqrt(n);
    for (int i = 2; i <= limit; i++) {
        (*counter)++;
        if ( !a[i - 2] ) {
            for (int j = i * i; j <= n; j += i) {
                (*counter)++;
                a[j - 2] = 1;
            }
        }
    }

    int p = 0;
    for (int i = 0; i < (n - 1); i++) {
        (*counter)++;
        if ( !a[i] ) {
            (*primes)[p++] = i + 2;
        }
    }

    free(a);
    return p;
}

int euclid(int x, int y, int *counter)
{
    /* Euclid’s algorithm */
    (*counter)++;
    return y ? euclid(y, x % y, counter) : x;
}

int cic(int x, int y, int *counter)
{
    /* Consecutive integer checking algorithm */
    int t = x < y ? x : y;

    (*counter)++;
    while (x % t || y % t) {
        t--;
        (*counter)++;
    }

    return t;
}

int msp(int x, int y, int *counter)
{
    /* Middle school procedure algorithm */
    (*counter)++;

    int n = x > y ? x : y;
    int *primes_list;

    /* Get primes uptil `n` */
    int list_size = get_primes(n, &primes_list, counter);

    /* Populate exponent arrays which carries information about the prime
     * factors of `x` & `y`. */
    int *x_factors = calloc(list_size, sizeof *x_factors);
    for (int i = 0; x > 1; i++) {
        (*counter)++;
        while ( x % primes_list[i] == 0 && x > 1 ) {
            (*counter)++;
            x_factors[i]++;
            x /= primes_list[i];
        }
    }

    int *y_factors = calloc(list_size, sizeof *y_factors);
    for (int i = 0; y > 1; i++) {
        (*counter)++;
        while ( y % primes_list[i] == 0 && y > 1 ) {
            (*counter)++;
            y_factors[i]++;
            y /= primes_list[i];
        }
    }

    /* Now just get the minumum of each pair of element after zipping
     * `x_factors` & `y_factors` together. Those will be the common factors. */
    int *common_factors = malloc(list_size * sizeof *y_factors);
    for (int i = 0; i < list_size; i++) {
        (*counter)++;
        common_factors[i] = MIN(x_factors[i], y_factors[i]);
    }

    free(x_factors);
    free(y_factors);

    /* Go through the `primes_list` and raise each element to the power of
     * `common_factors` at that index and take the product of them all. That's
     * the GCD. */
    int gcd = 1;
    for (int i = 0; i < list_size; i++) {
        (*counter)++;
        while ( common_factors[i]-- ) {
            (*counter)++;
            gcd *= primes_list[i];
        }
    }

    free(common_factors);
    free(primes_list);

    return gcd;

    return 0;
}

void reset_counter(struct Algorithm *algo)
{
    algo->step_counter = 0;
}

void compute_algo(struct Algorithm *algo)
{
    algo->res = algo->gcd(algo->x, algo->y, &(algo->step_counter));
}

int main(void)
{
    int pair[][2] = { { 31415, 14142 },
                      { 56, 32566 },
                      { 34218, 56 },
                      { 12,15 },
                      { 31415, 31415 },
                      { 12, 12 } };

    printf("Euclid\n");
    for (int i = 0; i < 6; i++) {
        int counts = 0;
        printf("%d ", euclid(pair[i][0], pair[i][1], &counts));
        printf("%d\n", counts);
    }

    printf("\nConsecutive integer checking algorithm\n");
    for (int i = 0; i < 6; i++) {
        int counts = 0;
        printf("%d ", cic(pair[i][0], pair[i][1], &counts));
        printf("%d\n", counts);
    }

    printf("\nMiddle school procedure algorithm\n");
    for (int i = 0; i < 6; i++) {
        int counts = 0;
        printf("%d ", msp(pair[i][0], pair[i][1], &counts));
        printf("%d\n", counts);
    }

    return EXIT_SUCCESS;
}

/* We plan to use the below, however I'm not touching it until I've tested and
 * verified all three algorithms */
int _main(void) {
    int nums[10];
    struct Algorithm algos[3];

    printf("Enter 10 numbers:\n");

    for (int i = 0; i < 10; i++) {
        scanf("%d", &nums[i]);
    }

    putchar('\n');

    /* initialize algorithm names and function pointers */
    strcpy(algos[0].name, "Euclid’s algorithm");
    algos[0].gcd = euclid;
    strcpy(algos[1].name, "Consecutive integer checking algorithm");
    algos[1].gcd = cic;
    /*
    strcpy(algos[2].name, "Algorithm-3"); algos[2].compute = algo3;
    */

    /* print header */
    printf("Sl.   Input               Steps Taken By                   Result "
           "  Fastest\nNo.           Algorithm-1   Algorithm-2   Algorithm-3\n"
           "------------------------------------------------------------------"
           "-------------\n");

    /* Loop through all inputs */
    for (int i = 0; i < 10; i++) {

        /* reset all step counters */
        for (int j = 0; j < 3; j++) {
            reset_counter(&algos[j]);
        }

        /* each time, compute results from all three algorithms */
        for (int j = 0; j < 3; j++) {
            /* TODO: algos[j].input = nums[i]; */
            compute_algo(&algos[j]);
        }

        /* check if their results agree with each other. */
        int res = algos[0].res;
        for (int j = 1; j < 3; j++) {
            if (algos[j].res != res) {
                fprintf(stderr, "Result of Algorithm-%d did not match the "
                                "result of Algorithm-1\n", j + 1);
                return EXIT_FAILURE;
            }
        }

        /* Identify the fastest algorithm */
        struct Algorithm *fastest_algo = &algos[0];
        for (int j = 1; j < 3; j++) {
            if (algos[j].step_counter < fastest_algo->step_counter) {
                fastest_algo = &algos[j];
            }
        }

        printf("%3d   %5d   %11d   %11d   %11d   %9s   %s\n",
               i + 1,  nums[i], algos[0].step_counter,
               algos[1].step_counter, algos[2].step_counter,
               res ? "is prime" : "not prime", fastest_algo->name
        );
    }

    return EXIT_SUCCESS;
}
