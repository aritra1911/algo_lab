/*
 * Write a program by using an user defined function for computing ⌊ √n⌋ for any
 * positive integer n. Besides assignment and comparison, your algorithm may
 * only use the four basic arithmetical operations.
 */

#include <stdio.h>
#include <stdlib.h>

double my_sqrt(double, double, int);

double my_sqrt(double n, double guess, int iterations)
{
    while ( iterations-- ) {
        double quotient = n / guess;
        guess = (guess + quotient) / 2.0;
    }

    return guess;
}

int main(int argc, char** argv)
{
    double n, initial_guess;
    int iterations;

    if (argc < 3) {
        if (argc < 2) {
            printf("WARN : No arguments provided.\n");
        } else {
            printf("WARN : Values for initial_guess &"
                         " iterations not provided.\n");
        }
        printf("     : Usage: %s <n> <initial_guess> <iterations>\n"
               "     : We'll be assuming some safe (default) values"
                     " for demonstration purposes.\n\n", argv[0]);
    }

    if (argc > 1) {
        n = atof(argv[1]);
    } else {
        n = 2;
    }

    if (argc > 2) {
        initial_guess = atoi(argv[2]);
    } else {
        initial_guess = 1;
    }

    if (argc > 3) {
        iterations = atoi(argv[3]);
    } else {
        iterations = 49;
    }

    printf("INFO : n = %lf\n"
           "     : initial_guess = %lf\n"
           "     : iterations = %d\n\n", n, initial_guess, iterations);

    printf("INFO : sqrt(%lf) = %.15lf\n",
           n, my_sqrt(n, initial_guess, iterations));

    return EXIT_SUCCESS;
}
