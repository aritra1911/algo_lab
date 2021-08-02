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

#define MIN(x, y, z) ((x < y) ? x : ((y < z) ? y : z))

struct step_counters {
    int algo1, algo2, algo3;
};

int algo1(int, int *);
int algo2(int, int *);
int algo3(int, int *);

void reset_counters(struct step_counters *counters) {
    counters->algo1 = 0;
    counters->algo2 = 0;
    counters->algo3 = 0;
}

int algo1(int num, int *counter) {
    int n = num - 1;

    *counter++;
    while ( n > 1 && (num % n) ) {
        *counter++;
        n--;
    }

    *counter++;
    return (n == 1) ? 1 : 0;
}

int algo2(int num, int *counter) {
    int n = num / 2;

    *counter++;
    while ( n > 1 && (num % n) ) {
        *counter++;
        n--;
    }

    *counter++;
    return (n == 1) ? 1 : 0;
}

int algo3(int num, int *counter) {

    if ( num < 2 ) {
        *counter++;
        return 0;
    }

    if ( num == 2 ) {
        *counter++;
        return 1;
    }

    int flag = 0;
    for (int i = 2; i <= num / 2; i++) {
        *counter++;

        if ( num % i == 0 ) {
            flag = 1;
            break;
        }
    }

    return flag ? 0 : 1;
}

int main(void) {
    int nums[10];
    struct step_counters counters;

    printf("Enter 10 numbers:\n");

    for (int i = 0; i < 10; i++) {
        scanf("%d", &nums[i]);
    }

    putchar('\n');

    reset_counters(&counters);
    for (int i = 0; i < 10; i++) {

        printf("%02d   %8d   %16s   %16s   %16s\n",
               i + 1,  nums[i],
               algo1(nums[i], &counters.algo1) ? "is prime" : "not prime",
               algo2(nums[i], &counters.algo2) ? "is prime" : "not prime",
               algo3(nums[i], &counters.algo3) ? "is prime" : "not prime"
        );
    }

    return EXIT_SUCCESS;
}
