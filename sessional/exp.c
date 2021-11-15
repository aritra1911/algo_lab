/*
 * Write a program that uses a divide-and-conquer algorithm/user defined
 * function for the exponentiation problem of computing a^n where a > 0 and n is
 * a positive integer. How does this algorithm compare with the brute-force
 * algorithm in terms of number of multiplications made by both algorithms.
 */

#include <stdio.h>
#include <stdlib.h>

int dc_int_pow(int, int, int *);
int bf_int_pow(int, int, int *);

int dc_int_pow(int a, int n, int *mul_counter)
{
    if ( !n )
        return 1;

    if ( mul_counter ) (*mul_counter)++;

    if ( !(n & 1) ) {
        return dc_int_pow(a * a, n >> 1, mul_counter);
    }

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

        int a = atoi(argv[1]);
        int n = atoi(argv[2]);

        int mul_count = 0;
        printf("Solution by Divide and Conquer:\n");
        printf("Answer : %i\n", dc_int_pow(a, n, &mul_count));
        printf("No. of Multiplications : %i\n", mul_count);

        mul_count = 0;
        printf("\nSolution by Brute Force:\n");
        printf("Answer : %i\n", bf_int_pow(a, n, &mul_count));
        printf("No. of Multiplications : %i\n", mul_count);

        return EXIT_SUCCESS;
    }

    fprintf(stderr, "Usage : %s <a> <n>\n", argv[0]);

    return EXIT_FAILURE;
}
