/*
 * Given a set of n intervals, input through keyboard,
 *
 *     R = { I1, 12, I3, ... , In }
 *
 * where each Ij = [aj, bj] is an interval from the real line having
 * length bj - aj and bj>aj. The objective is to find all possible
 * largest sub set of intervals S ⊆ R, excluding all intervals of least
 * length, such that no two intervals in S overlap each other.
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t index;
    char name;
    int start, end;
} Interval;

int compare_intervals(const void *, const void *);
static Interval *get_interval_by_index(size_t, Interval *, size_t);

int compare_intervals(const void *i1, const void *i2)
{
    int len_i1 = ((Interval *) i1)->end - ((Interval *) i1)->start;
    int len_i2 = ((Interval *) i2)->end - ((Interval *) i2)->start;
    return len_i1 < len_i2 ? -1 : len_i1 > len_i2 ? 1 : 0;
}

static Interval *get_interval_by_index(size_t idx, Interval *intervals,
                                                   size_t n)
{
    for (size_t i = 0; i < n; i++) {
        if ( idx == intervals[i].index ) {
            return &intervals[i];
        }
    }

    return NULL;
}

int main(void)
{
    size_t n;
    Interval *intervals;

    printf("Enter number of intervals: ");
    scanf("%lu", &n);
    getchar();  /* eat trailing '\n' */

    intervals = calloc(n, sizeof (Interval));

    printf("\nEnter intervals:\n");
    for (size_t i = 0; i < n; i++) {
        intervals[i].index = i;
        scanf("(%c,%i,%i)", &intervals[i].name,
              &intervals[i].start, &intervals[i].end);
        getchar();  /* eat trailing '\n' */
    }

    for (size_t i = 0; i < n; i++) {
        printf("\nindex : %lu\n name : %c\nstart : %i\n  end : %i\n",
               intervals[i].index, intervals[i].name,
               intervals[i].start, intervals[i].end);
    }

    free(intervals);

    return EXIT_SUCCESS;
}
