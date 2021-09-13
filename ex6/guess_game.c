/*
 * A and B are playing a guessing game where B first thinks up an integer X
 * (positive, negative or zero, and could be of arbitrarily large magnitude) and
 * A tries to guess it. In response to A’s guess, B gives exactly one of the
 * following three replies:
 *
 *     a) Try a bigger number
 *     b) Try a smaller number or
 *     c) You got it.
 *
 * Write a program by designing an efficient algorithm to minimize the number of
 * guesses A has to make. An example (not necessarily an efficient one) below:
 *
 *     Let B thinks up the number 35
 *
 *     A’s guess   B’s response
 *     ---------   ------------
 *     10          Try a bigger number
 *     20          Try a bigger number
 *     30          Try a bigger number
 *     40          Try a smaller number
 *     35          You got it
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <errno.h>
#include <limits.h>

static int guess(int cost)
{
    static int current_guess;
    static long lower_bound, upper_bound;

    /*
     * `cost` is a feedback to this function to generate something
     *     > `current_guess` if cost > 0, or to generate something
     *     < `current_guess` if cost < 0, or to generate an
     *      arbitrary guess  if cost = 0.
     */

    /* Unless `cost` is zero, `upper_bound` must be
     * greater than or equal to `lower_bound`. */
    assert( !cost || lower_bound <= upper_bound );

    if ( !cost ) {
        /* We shall (re)initialize everything when `cost = 0` */
        current_guess = mrand48();
        lower_bound = INT_MIN;
        upper_bound = INT_MAX;

        return current_guess;
    }

    if ( cost > 0 ) {
        lower_bound = current_guess + 1;
    } else {
        upper_bound = current_guess - 1;
    }

    /* Guess the mid point */
    current_guess = (upper_bound + lower_bound) / 2;

    return current_guess;
}

extern int main(void)
{
    struct timespec time_now;

    /* Attempt to get the current time */
    if ( clock_gettime(CLOCK_REALTIME, &time_now) != 0 ) {
        fprintf(stderr,"ERROR : could not attain CLOCK_REALTIME\n"
                       "      : clock_gettime: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    /* Use current time's nanoseconds field to seed RNG */
    srand48(time_now.tv_nsec);

    printf(" * B thinks of a number\n");
    int b_number = mrand48();

    int a_guess = 0;
    int feedback = 0;

    while ( (a_guess = guess(feedback)) != b_number ) {
        printf("<A> %i\n", a_guess);

        feedback = b_number - a_guess;

        if ( feedback > 0 ) {
            printf("<B> Try a bigger number\n");
        } else {
            printf("<B> Try a smaller number\n");
        }
    }

    printf("<A> %i\n", a_guess);
    printf("<B> You got it\n");

    return EXIT_SUCCESS;
}
