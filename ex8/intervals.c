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
#include <assert.h>

typedef struct {
    size_t index;
    char name;
    int start, end;
} Interval;

int compare_intervals(const void *, const void *);
static Interval *get_interval_by_index(size_t, Interval *, size_t);

int length(const Interval *interval)
{
    int len = interval->end - interval->start;
    return len;
}

char *to_string(const Interval *interval, char *str)
{
    sprintf(str, "(%c, %i, %i)", interval->name,
            interval->start, interval->end);

    return str;
}

int compare_intervals(const void *i1, const void *i2)
{
    return ((Interval *) i1)->end - ((Interval *) i2)->end;
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

void print_subset(Interval **subset_ptrs)
{
    printf("{ ");
    for (Interval **p = subset_ptrs; *p; p++) {
        printf("%c, ", (*p)->name);
    }
    printf("}\n");
}

Interval **get_next_subset(Interval **subset_ptrs, Interval *intervals,
                           size_t n, int least_len)
{
    Interval **p = subset_ptrs;
    Interval *q, *prev;

    if ( *p == NULL ) {
        *p = &intervals[0];
        p++;
    } else {
        while ( *(p + 1) != NULL ) p++;
        *p = NULL;
        p--;
    }

    while ( subset_ptrs[0] != NULL ) {
        prev = *p == NULL ? *(p - 1) : *p;

        for ( q = prev + 1; q <= &intervals[n - 1]; q++ ) {
            if ( length(q) == least_len ) continue;

            if ( p == subset_ptrs ) {
                *p = q;
                p++;
            }

            if ( q->start >= (*(p - 1))->end ) {
                break;
            }
        }

        if ( q > &intervals[n-1] ) {
            return subset_ptrs;
        } else {
            *p = q;
            p++;
        }
    }
//    } while ( subset_ptrs[0] != NULL );
}

int main(void)
{
    size_t n;
    Interval *intervals;
    int least_length;

    printf("Enter maximum number of intervals: ");
    scanf("%lu", &n);
    getchar();  /* eat trailing '\n' */

    intervals = calloc(n, sizeof (Interval));

    printf("\nEnter name of intervals with their start and end number:\n");
    for (size_t i = 0; i < n; i++) {
        intervals[i].index = i;
        scanf("(%c,%i,%i)", &intervals[i].name,
              &intervals[i].start, &intervals[i].end);
        getchar();  /* eat trailing '\n' */
    }

    qsort(intervals, n, sizeof (Interval), compare_intervals);

    printf("\nThe intervals with their lengths sorted in ascending order "
           "with their end number.\nIntervals          Length of Intervals\n");
    least_length = length(&intervals[0]);
    for (size_t i = 0; i < n; i++) {
        char interval_str[16];
        int len = length(&intervals[i]);
        assert( len > 0 );
        printf("%-16s   %i\n", to_string(&intervals[i], interval_str),
                               length(&intervals[i]));
        if ( len < least_length )
            least_length = len;
    }

    printf("\nThe least length intervals : { ");
    for (size_t i = 0; i < n; i++) {
        if ( length(&intervals[i]) == least_length )
            printf("%c, ", intervals[i].name);
    } printf("}\n");

    printf("Excluding the least length intervals,\n"
           "the largest sub set of non-overlapping intervals : ");


    Interval **subset_ptrs = calloc(n, sizeof (Interval *));

    do {
        print_subset(get_next_subset(subset_ptrs, intervals, n, least_length));
    } while ( subset_ptrs[0] );
    /*
    print_subset(get_next_subset(subset_ptrs, intervals, n, least_length));
    print_subset(get_next_subset(subset_ptrs, intervals, n, least_length));
    print_subset(get_next_subset(subset_ptrs, intervals, n, least_length));
    print_subset(get_next_subset(subset_ptrs, intervals, n, least_length));
    print_subset(get_next_subset(subset_ptrs, intervals, n, least_length));
    print_subset(get_next_subset(subset_ptrs, intervals, n, least_length));
    print_subset(get_next_subset(subset_ptrs, intervals, n, least_length));
    */

    free(subset_ptrs);


/*
    for (size_t i = 0; i < n; i++) {
        printf("\nindex : %lu\n name : %c\nstart : %i\n  end : %i\n",
               intervals[i].index, intervals[i].name,
               intervals[i].start, intervals[i].end);
    }
*/

    free(intervals);

    return EXIT_SUCCESS;
}
