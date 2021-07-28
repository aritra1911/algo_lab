/*
 * Write a program to find union and intersection of two sorted arrays.
 */

#include <stdio.h>
#include <stdlib.h>

#define MIN(x, y) ((x < y) ? x : y)

int main(void)
{
    int *arr1, *arr2, *union_arr, *intersection_arr;
    int m, n;

    printf("Enter size of first array: ");
    scanf("%d", &m);
    printf("Enter size of second array: ");
    scanf("%d", &n);

    arr1 = malloc(m * sizeof *arr1);
    arr2 = malloc(n * sizeof *arr2);

    union_arr = malloc( (m + n) * sizeof *union_arr );
    intersection_arr = malloc(MIN(m, n) * sizeof *intersection_arr);

    printf("Enter elements of first array (in sorted order):\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &arr1[i]);
    }

    printf("Enter elements of second array (in sorted order):\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr2[i]);
    }

    int i=0, j=0, k=0, l=0;

    while ( i < m && j < n ) {

        if ( arr1[i] < arr2[j] ) {
            union_arr[k++] = arr1[i++];

        } else if (arr2[j] < arr1[i]) {
            union_arr[k++] = arr2[j++];

        } else {
            union_arr[k++] = arr1[i];
            intersection_arr[l++] = arr1[i];
            i++;
            j++;  /* skip */
        }
    }

    if ( i == m  && j < n ) {
        while (j < n) {
            union_arr[k++] = arr2[j++];
        }
    } else if ( j == n  && i < m ) {
        while (i < m) {
            union_arr[k++] = arr1[i++];
        }
    }

    free(arr1);
    free(arr2);

    printf("Union : { %d", union_arr[0]);
    for (i = 1; i < k; i++) {
        printf(", %d", union_arr[i]);
    }
    printf(" }\n");

    free(union_arr);

    printf("Intersection : { %d", intersection_arr[0]);
    for (i = 1; i < l; i++) {
        printf(", %d", intersection_arr[i]);
    }
    printf(" }\n");

    free(intersection_arr);

    return EXIT_SUCCESS;
}
