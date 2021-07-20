/*
 * Write a program that takes three variable (a, b, c) as separate parameters
 * and rotates the values stored so that value a goes to be, b, b to c and c to
 * a by using SWAP(x,y) function that swaps/exchanges the numbers x & y.
 */

#include <stdio.h>
#include <stdlib.h>

#define SWAP(x,y) swap(&x, &y)

void swap(int*, int*);

int main(void)
{
    int a, b, c;

    printf("Enter value of `a`: ");
    scanf("%d", &a);
    printf("Enter value of `b`: ");
    scanf("%d", &b);
    printf("Enter value of `c`: ");
    scanf("%d", &c);

    printf("Swapping...\n");
    SWAP(a, b);
    SWAP(a, c);

    printf("Value of `a` : %d\n", a);
    printf("Value of `b` : %d\n", b);
    printf("Value of `c` : %d\n", c);

    return EXIT_SUCCESS;
}

void swap(int* x, int* y)
{
    int z = *x;
    *x = *y;
    *y = z;
}
