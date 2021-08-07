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
 * Sl.   Input                              GCD algorithm                   Remarks
 * No.   GCD(x, y)           Euclid's    Consecutive        Middle school
 *                           algorithm   integer checking   procedure
 *                                       algorithm.         algorithm
 * --------------------------------------------------------------------------------
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

    /* Pseudocode :
     * https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes#Pseudocode
     *
     * Time Complexity : O(n log log n)  [according to Wikipedia]
     */

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

    int n = x < y ? x : y;
    int *primes_list;

    /* Get primes uptil `n` */
    int list_size = get_primes(sqrt(n), &primes_list, counter);

    int *prime = primes_list;
    int gcd = 1;
    while ( x > 1 && y > 1 ) {
        int x_div=0, y_div=0;

        (*counter)++;

        if ( x % (*prime) == 0 ) {
            x /= *prime;
            x_div = 1;
        }

        if ( y % (*prime) == 0 ) {
            y /= *prime;
            y_div = 1;
        }

        if ( x_div && y_div ) {
            /* That's a common factor */
            gcd *= *prime;
        } else if ( !(x_div || y_div) ) {
            /* Try the next prime */
            prime++;
        }
    }

    free(primes_list);

    return gcd;
}

void reset_counter(struct Algorithm *algo)
{
    algo->step_counter = 0;
}

void compute_algo(struct Algorithm *algo)
{
    algo->res = algo->gcd(algo->x, algo->y, &(algo->step_counter));
}

/* We plan to use the below, however I'm not touching it until I've tested and
 * verified all three algorithms */
int main(void) {
    int nums[6][2];
    struct Algorithm algos[3];

    printf("Enter 6 pairs of numbers:\n");

    for (int i = 0; i < 6; i++) {
        scanf("%d %d", &nums[i][0], &nums[i][1]);
    }

    putchar('\n');

    /* initialize algorithm names and function pointers */
    strcpy(algos[0].name, "Euclid's algorithm");
    algos[0].gcd = euclid;
    strcpy(algos[1].name, "Consecutive integer checking algorithm");
    algos[1].gcd = cic;
    strcpy(algos[2].name, "Middle school procedure algorithm");
    algos[2].gcd = msp;

    /* print header */
    printf("Sl.   Input                              GCD algorithm             "
           "      Remarks\nNo.   GCD(x, y)           Euclid's    Consecutive   "
           "     Middle school\n                          algorithm   integer c"
           "hecking   procedure\n                                      algorith"
           "m.         algorithm\n---------------------------------------------"
           "-------------------------------------------------------------------"
           "------------------\n");

    /* Loop through all inputs */
    for (int i = 0; i < 6; i++) {

        /* reset all step counters */
        for (int j = 0; j < 3; j++) {
            reset_counter(&algos[j]);
        }

        /* each time, compute results from all three algorithms */
        for (int j = 0; j < 3; j++) {
            algos[j].x = nums[i][0];
            algos[j].y = nums[i][1];
            compute_algo(&algos[j]);
        }

        /* check if their results agree with each other. */
        int res = algos[0].res;
        for (int j = 1; j < 3; j++) {
            if (algos[j].res != res) {
                fprintf(stderr, "Result of %s did not match the "
                                "result of %s\n", algos[j].name, algos[0].name);
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

        char istr[32], remstr[128];;
        sprintf(istr, "GCD(%d, %d)", nums[i][0], nums[i][1]);
        sprintf(remstr, "GCD=%-5d; Fastest=%s", res, fastest_algo->name);

        printf("%-3d   %-17s   %9d   %16d   %13d   %s\n",
               i + 1,  istr, algos[0].step_counter, algos[1].step_counter,
               algos[2].step_counter, remstr);
    }

    return EXIT_SUCCESS;
}
