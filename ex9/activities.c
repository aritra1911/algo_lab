#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef struct {
    char name;
    int start, finish;
} Activity;

static int length(const Activity *);
static char *to_string(const Activity *, char *);
int compare_activities(const void *, const void *);
static size_t length_subset(Activity **);
static void print_subset(Activity **);
static Activity **get_next_subset(Activity **, Activity *, size_t);
static int subset_has_activity(Activity**, char);

static int length(const Activity *activity)
{
    int len = activity->finish - activity->start;
    return len;
}

static char *to_string(const Activity *activity, char *str)
{
    sprintf(str, "(%c, %i, %i)", activity->name,
            activity->start, activity->finish);

    return str;
}

int compare_activities(const void *i1, const void *i2)
{
    return ((Activity *) i1)->finish - ((Activity *) i2)->finish;
}

static size_t length_subset(Activity **subset_ptrs)
{
    size_t i;
    for (i = 0; subset_ptrs[i]; i++);
    return i;
}

static void print_subset(Activity **subset_ptrs)
{
    printf("{ ");
    for (Activity **p = subset_ptrs; *p; p++) {
        printf("%c, ", (*p)->name);
    }
    printf("}");
}

static Activity **get_next_subset(Activity **subset_ptrs, Activity *activities,
                                  size_t n)
{
    /* Pulls out the next non-overlapping subset possible in the given
     * activities array, i.e. takes subset_ptr to its next state. If
     * it's the last state, all subset_ptr is zeroed out.
     *
     * Written in one sitting while carefully maintaining array and
     * pointer diagrams. Do not expect this to make sense right away,
     * but at least it works, hence don't touch it.
     */
    Activity **p = subset_ptrs;
    Activity *q, *prev;

    if ( *p == NULL ) {
        *p = &activities[0];
        p++;
    } else {
        while ( *(p + 1) != NULL ) p++;
        *p = NULL;
        p--;
    }

    while ( subset_ptrs[0] != NULL ) {
        prev = *p == NULL ? *(p - 1) : *p;

        for ( q = prev + 1; q <= &activities[n - 1]; q++ ) {
            if ( p == subset_ptrs ) {
                *p = q;
                p++;
            }

            if ( q->start >= (*(p - 1))->finish ) {
                break;
            }
        }

        if ( q > &activities[n-1] ) {
            break;
        } else {
            *p = q;
            p++;
        }
    }

    return subset_ptrs;
}

static int subset_has_activity(Activity** subset_ptrs, char name)
{
    for (Activity **p = subset_ptrs; *p; p++) {
        if ( (*p)->name == name ) return 0;
    }

    return -1;
}

int main(void)
{
    size_t n;
    Activity *activities;
    char choice;

    printf("Enter maximum number of activities: ");
    scanf("%lu", &n);
    getchar();  /* eat trailing '\n' */

    activities = calloc(n, sizeof (Activity));

    printf("\nEnter name of activities with their start and finish time:\n");
    for (size_t i = 0; i < n; i++) {
        scanf("(%c,%i,%i)", &activities[i].name,
              &activities[i].start, &activities[i].finish);
        getchar();  /* eat trailing '\n' */
    }

    qsort(activities, n, sizeof (Activity), compare_activities);

    /* Enable in case of debugging *
    printf("\nThe activities with their lengths sorted in ascending order "
           "with their end number.\nActivitys          Length of Activitys\n");
    for (size_t i = 0; i < n; i++) {
        char activity_str[16];
        int len = length(&activities[i]);
        assert( len > 0 );
        printf("%-16s   %i\n", to_string(&activities[i], activity_str),
                               length(&activities[i]));
    }
    */

    printf("\nEnter name of activity of person's choice: ");
    choice = getchar(); getchar();  /* eat trailing newline */


    Activity **subset_ptrs = calloc(n, sizeof (Activity *));

    size_t max_len = 0;

    /* Calculate maximum number of activities */
    /* TODO: Buffer the evaluation here */
    do {
        size_t len_ss;

        get_next_subset(subset_ptrs, activities, n);
        len_ss = length_subset(subset_ptrs);

        if ( ( len_ss == max_len || max_len == 0 ) &&
               !subset_has_activity(subset_ptrs, choice) ) {

            if ( !max_len ) {
                max_len = len_ss;
                break;
            }
        }
    } while ( subset_ptrs[0] );

    printf("\nMaximum number of activities selected = %li\n", max_len);

    /* Clear everything as we're gonna start over */
    memset(subset_ptrs, 0, n * sizeof (Activity *));

    /* Start over and now actually print the activities selected! */
    /* TODO: Don't start over, use a buffer */
    printf("\nSelected Activity Set(s) : ");
    do {
        size_t len_ss;

        get_next_subset(subset_ptrs, activities, n);
        len_ss = length_subset(subset_ptrs);

        if ( len_ss == max_len && !subset_has_activity(subset_ptrs, choice) ) {

            print_subset(subset_ptrs);
            printf(", ");

        }
    } while ( subset_ptrs[0] );

    free(subset_ptrs);
    free(activities);

    putchar('\n');
    return EXIT_SUCCESS;
}
