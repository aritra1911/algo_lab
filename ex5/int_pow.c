/*
 * Write a program that uses a divide-and-conquer algorithm/user defined
 * function for the exponentiation problem of computing a^n where a > 0 and n is
 * a positive integer. How does this algorithm compare with the brute-force
 * algorithm in terms of number of multiplications made by both algorithms.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX(x, y) ( x > y ? x : y )
#define MIN(x, y) ( x < y ? x : y )

int dc_int_pow(int, int, int *);
int bf_int_pow(int, int, int *);

int dc_int_pow(int a, int n, int *mul_counter)
{
    if ( n == 1 ) return a;

    if ( mul_counter ) (*mul_counter)++;

    return a * dc_int_pow(a, n - 1, mul_counter);
}

int bf_int_pow(int a, int n, int *mul_counter)
{
    int ret = 1;

    for (int i = 0; i < n; i++) {
        if ( mul_counter ) (*mul_counter)++;

        ret *= a;
    }

    return ret;
}

int main(int argc, char** argv)
{
    if ( argc > 2 ) {

        /* Handle a test via command line */

        int a = atoi(argv[1]);
        int n = atoi(argv[2]);

        printf("%i\n", dc_int_pow(a, n, NULL));

        return EXIT_SUCCESS;
    }

    printf("           Multiplications Made in\n"
           "a   n   Divide & Conquer   Brute Force\n"
           "-   -   ----------------   -----------\n");

    for (int a = 1; a < 9; a++) {

        struct timespec time_now;
        int    dc_mul_count = 0,
               bf_mul_count = 0;

        /* Get the current time */
        clock_gettime(CLOCK_MONOTONIC, &time_now);

        /* Use current time's nanoseconds field to initialize RNG seed */
        srand((unsigned) time_now.tv_nsec);

        int n = (rand() % 8) + 1;  /* any random number in interval [1, 8] */

        int res = dc_int_pow(a, n, &dc_mul_count);
        if ( bf_int_pow(a, n, &bf_mul_count) != res ) {
            fprintf(stderr, "BUG : Result from Brute Force approach didn't"
                            " match that if Divide & Conquer approach\n");
            return EXIT_FAILURE;
        }

        printf("%i   %i   %16i   %11i\n",
               a, n, dc_mul_count, bf_mul_count);
    }

    return EXIT_SUCCESS;
}
