/* Let A be a list of n (not necessarily distinct) integers. Write a program by
 * using User Defined Function(UDF)s to test whether any item occurs more than
 * ⌈n/2⌉ times in A.
 *  i. UDF should take O(n^2) time and use no additional space.
 * ii. UDF should take O(n) time and use O(1) additional space.
 */

#include <stdio.h>
#include <stdlib.h>

int moore(int *, int);
int find_majority(int *, int);

int moore(int *arr, int n)
{
    /* Finds majority element in O(n) using
     * Boyer-Moore Majority Voting Algorithm
     * and returns index of majority element
     * or -1 if not found. */

    int m = arr[0];
    int k = 1;

    /* First loop, figures out potential majority */
    for (int i = 1; i < n; i++) {
        if ( !k ) {
            m = arr[i];
        } else if ( m != arr[i] ) {
            k--;
            continue;
        }
        k++;
    }

    /* Second loop, verifies `m` as majority and returns it's index */
    k = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == m) { k++; }

        if (k > (n + 1) / 2) {  /* equivalent to k > ceil(n/2) */
            return i;
        }
    }

    /* If majority was not verified, return C's classic -1 */
    return -1;
}

int find_majority(int *arr, int n)
{
    for (int i = 0; i < n; i++) {
        int count = 0;

        for (int j = 1; j < n; j++) {
            if ( arr[j] == arr[i] ) {
                count++;
            }
        }

        if ( count > (n + 1) / 2 ) {
            return i;
        }
    }

    return -1;
}

int main(void)
{
    int *arr, n, i;

    printf("Enter n: ");
    scanf("%d", &n);

    arr = malloc(n * sizeof *arr);

    printf("Enter items:\n");
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("\nResults using O(n^2) algorithm:\n");
    if ( (i = find_majority(arr, n)) == -1 ) {
        printf("No such item found.\n");
    } else {
        printf("Item found : %d\n", arr[i]);
    }

    printf("\nResults using Boyer-Moore Majority Voting Algorithm:\n");
    if ( (i = moore(arr, n)) == -1 ) {
        printf("No such item found.\n");
    } else {
        printf("Item found : %d\n", arr[i]);
    }

    free(arr);

    return EXIT_SUCCESS;
}
