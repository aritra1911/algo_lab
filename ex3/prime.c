/*
 * Write a program to test whether a number n, entered through keyboard is prime
 * or not by using different algorithms you know for atleast 10 inputs and note
 * down the time complexity by step/frequency count method for each algorithm &
 * for each input. Finally make a comparision of time complexities found for
 * different inputs, plot an appropriate graph & decide which algothm is faster.
 *
 * Sl. No. Input (n)   Prime         Number        Testing       Result  Fastest
 *                     Algorithm-1   Algorithm-2   Algorithm-3
 *                     (Time by      (Time by      (Time by
 *                     frequency)    frequency)    frequency)
 * 1
 * 2
 * 3
 * 4
 * 5
 * 6
 * 7
 * 8
 * 9
 * 10
 *
 * N.B: If you can solve more than three different ways, then add more columns
 * right of Algorithm-3 column.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Algorithm {
    /* Shall contain the computed result after execution */

    char name[32];
    int input, res, step_counter;

    /* function pointer pointing to algorithm function to execute */
    int (*compute)(int, int *);
};

int algo1(int, int *);
int algo2(int, int *);
int algo3(int, int *);
void reset_counter(struct Algorithm *);
void compute_algo(struct Algorithm *);

void reset_counter(struct Algorithm *algo) {
    algo->step_counter = 0;
}

void compute_algo(struct Algorithm *algo) {
    algo->res = algo->compute(algo->input, &(algo->step_counter));
}

int algo1(int num, int *counter) {
    int n = num - 1;

    (*counter)++;
    while ( n > 1 && (num % n) ) {
        (*counter)++;
        n--;
    }

    (*counter)++;
    return (n == 1) ? 1 : 0;
}

int algo2(int num, int *counter) {
    int n = num / 2;

    (*counter)++;
    while ( n > 1 && (num % n) ) {
        (*counter)++;
        n--;
    }

    (*counter)++;
    return (n == 1) ? 1 : 0;
}

int algo3(int num, int *counter) {
    (*counter)++;

    if ( num < 2 ) {
        return 0;
    }

    if ( num == 2 ) {
        return 1;
    }

    int flag = 0;
    for (int i = 2; i <= num / 2; i++) {
        (*counter)++;

        if ( num % i == 0 ) {
            flag = 1;
            break;
        }
    }

    return flag ? 0 : 1;
}

int main(void) {
    int nums[10];
    struct Algorithm algos[3];

    printf("Enter 10 numbers:\n");

    for (int i = 0; i < 10; i++) {
        scanf("%d", &nums[i]);
    }

    putchar('\n');

    /* initialize algorithm names and function pointers */
    strcpy(algos[0].name, "Algorithm-1"); algos[0].compute = algo1;
    strcpy(algos[1].name, "Algorithm-2"); algos[1].compute = algo2;
    strcpy(algos[2].name, "Algorithm-3"); algos[2].compute = algo3;

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
            algos[j].input = nums[i];
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
