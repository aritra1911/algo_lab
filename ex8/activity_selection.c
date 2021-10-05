/*
 * Write a program to implement the Activity-Selection problem stated as
 * follows:
 *
 *     You are given `n` activities with their start and finish times.
 *     Select the maximum number of activities that can be performed by
 *     a single person, assuming that a person can only work on a single
 *     activity at a time.
 *
 *     Test Case:
 *
 *         Consider the following 6 activities ( 0, 1, 2, 3, 4, 5).
 *         start[]  = {1, 3, 0, 5, 8, 5};
 *         finish[] = {2, 4, 6, 7, 9, 9};
 *
 *         The maximum set of activities that can be executed by a
 *         single person is {0, 1, 3, 4}.
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t index;
    int start_time,
        finish_time;
    char done;  /* Boolean, use just a byte */
} Activity;

static int activity_selection(Activity *, size_t);
int compare_activities(const void *, const void *);
static Activity *get_activity_by_index(size_t, Activity *, size_t);

int compare_activities(const void *activity1, const void *activity2)
{
    return ((const Activity *) activity1)->finish_time -
           ((const Activity *) activity2)->finish_time;
}

static int activity_selection(Activity *activities, size_t n)
{
    int activities_done;

    /* sort according to finish times */
    qsort(activities, n, sizeof (Activity), compare_activities);

    Activity *current_activity = &activities[0];
    current_activity->done = 1;  /* Mark as done */
    activities_done = 1;

    for (size_t i = 1; i < n; i++) {
        if ( activities[i].start_time >= current_activity->finish_time ) {
            current_activity = &activities[i];
            current_activity->done = 1;  /* Mark as done */
            activities_done++;
        }
    }

    return activities_done;
}

static Activity *get_activity_by_index(size_t idx, Activity *activities,
                                       size_t n)
{
    for (size_t i = 0; i < n; i++) {
        if ( idx == activities[i].index ) {
            return &activities[i];
        }
    }

    return NULL;
}

int main(void)
{
    int n, activities_done;
    Activity *activities;

    printf("Enter number of activities: ");
    scanf("%i", &n);

    activities = calloc(n, sizeof (Activity));

    putchar('\n');
    for (int i = 0; i < n; i++) {
        activities[i].index = i;
        printf("-- ACTIVITY #%i --\n", i + 1);
        printf("Enter start time: ");
        scanf("%i", &activities[i].start_time);
        printf("Enter finish time: ");
        scanf("%i", &activities[i].finish_time);
        putchar('\n');
    }

    activities_done = activity_selection(activities, n);

    for (int i = 0; i < n; i++) {
        Activity *activity = get_activity_by_index(i, activities, n);
        printf("Activity #%i ................ %s\n", i + 1,
               activity->done ? "done" : "not done");
    }

    free(activities);

    printf("\nTotal activities performed : %i\n", activities_done);

    return EXIT_SUCCESS;
}
