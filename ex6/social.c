/*
 * In a social gathering, there are b boys and g girls (b > g) of different
 * ages. You have two unsorted arrays giving their ages (one for the boys, the
 * other for the girls). Write a program by devising an efficient O(b log g)
 * algorithm to find out the ages that are common between both the boys and
 * girls.
 *
 * Example:
 * If  Arrayboy = { 10, 20, 11, 89, 23, 21 } and
 *    Arraygirl = { 12, 30, 11, 20 },
 * Then Arraycommon = {11, 20}
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void merge(int *, int, int);
static void merge_sort(int *, int);
static int bin_search(int, int *, int);

static void merge(int *arr, int m, int len)
{
    int p = 0, q = m;
    int l = 0;

    int *temp_arr = malloc(len * sizeof *temp_arr);

    while ( p < m && q < len ) {
        if (arr[p] <= arr[q])
            temp_arr[l++] = arr[p++];
        else
            temp_arr[l++] = arr[q++];
    }

    while ( p < m )
        temp_arr[l++] = arr[p++];

    while ( q < len )
        temp_arr[l++] = arr[q++];

    memcpy(arr, temp_arr, len * sizeof *temp_arr);
    free(temp_arr);
}

static void merge_sort(int *arr, int len)
{
    if ( len <= 1 ) return;
    int m = len >> 1;
    merge_sort(arr, m);
    merge_sort(arr + m, len - m);
    merge(arr, m, len);
}

static int bin_search(int item, int *arr, int len)
{
    /* This algorithm assumes that `arr` is sorted in ascending order */

    if ( len ) {
        int m = (len - 1) >> 1;

        if (arr[m] == item)
            return 0;

        if (arr[m] < item)
            return bin_search(item, arr + m + 1, len - m - 1);

        return bin_search(item, arr, m);
    }

    return -1;
}

extern int main(void) {
    int *array_boy, *array_girl, *array_common;
    int len_boy, len_girl, len_common;

    /* Populate `array_boy` */
    printf("Enter length of Arrayboy: ");
    scanf("%i", &len_boy);
    array_boy = malloc(len_boy * sizeof *array_boy);
    printf("Enter their ages:\n");
    for (int i = 0; i < len_boy; i++)
        scanf("%i", &array_boy[i]);

    /* Populate `array_girl` */
    printf("\nEnter length of Arraygirl: ");
    scanf("%i", &len_girl);
    if ( len_girl >= len_boy ) {
        fprintf(stderr, "Necessary condition not met : length of Arrayboy "
                        "must be greater than the length of Arraygirl\n");
        free(array_boy);
        return EXIT_FAILURE;
    }
    array_girl = malloc(len_girl * sizeof *array_girl);
    printf("Enter their ages:\n");
    for (int i = 0; i < len_girl; i++)
        scanf("%i", &array_girl[i]);

    /* Sort `array_girl` using merge sort having a worst case of
     * O(n log n). Hence if `g` is the length of the array, the time
     * complexity shall be O(g log g). */
    merge_sort(array_girl, len_girl);

    /* Now pick each element from `array_boy` and search it in now
     * sorted `array_girl` using binary search which has an average
     * time complexity of O(log n). Replace `n` with `g` i.e. the
     * length of `array_girl` we have O(log g). Combining this with the
     * time complexity of the outer loop iterating over the ages in
     * `array_boy`, we get O(b log g). */
    array_common = malloc(len_girl * sizeof *array_common);
    len_common = 0;
    for (int i = 0; i < len_boy; i++) {
        if ( !bin_search(array_boy[i], array_girl, len_girl) )
            array_common[len_common++] = array_boy[i];
    }

    /* Looking at the above two blocks, it is clear that O(b log g) is
     * greater than O(g log g) since b > g and since the big 'O'
     * notation define the asymptotic tighter upper bound, I argue that
     * the algorithm implemented above is strictly O(b log g). */

    int ret = EXIT_SUCCESS;

    if ( len_common ) {
        printf("\nCommon ages : %i", array_common[0]);
        for (int i = 1; i < len_common; i++)
            printf(" %i", array_common[i]);
        putchar('\n');
    } else {
        fprintf(stderr, "No matches found!\n");
        ret = EXIT_FAILURE;
    }

    free(array_boy);
    free(array_girl);
    free(array_common);

    return ret;
}
