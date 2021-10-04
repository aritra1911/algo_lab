/*
 * Write a program to implement the Fractional Knapsack algorithm.
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    size_t index;
    float
        profit,
        weight,
        amount;
} Item;

int compare_items(const void *item1, const void *item2)
{
    float pw_ratio_item1 = ((Item *) item1)->profit /
                           ((Item *) item1)->weight;

    float pw_ratio_item2 = ((Item *) item2)->profit /
                           ((Item *) item2)->weight;

    return pw_ratio_item1 < pw_ratio_item2 ? +1 :
           pw_ratio_item1 > pw_ratio_item2 ? -1 : 0;
}

float fractional_knapsack(float sack_size, Item *items, size_t n)
{
    /* Sort items descending order of their profit to weight ratio */
    qsort(items, n, sizeof (Item), compare_items);

    size_t i;
    float profit = 0.0;

    for (i = 0; i < n && sack_size >= items[i].weight; i++) {
        sack_size -= items[i].weight;
        profit += items[i].profit;
        items[i].amount = 1.0;
    }

    if ( i < n ) {
        items[i].amount = sack_size / items[i].weight;
        profit += items[i].amount * items[i].profit;
    }

    return profit;
}

Item *get_item_by_index(size_t idx, Item *items, size_t n)
{
    for (size_t i = 0; i < n; i++) {
        if ( idx == items[i].index ) {
            return &items[i];
        }
    }

    return NULL;
}

int main(void)
{
    int n;
    Item *items;
    float capacity, max_profit;

    printf("Enter knapsack capacity: ");
    scanf("%f", &capacity);

    printf("Enter no. of items: ");
    scanf("%i", &n);

    items = calloc(n, sizeof *items);

    putchar('\n');
    for (int i = 0; i < n; i++) {
        items[i].index = i;
        printf("-- ITEM #%i --\n", i + 1);
        printf("Enter profit: ");
        scanf("%f", &items[i].profit);
        printf("Enter weight: ");
        scanf("%f", &items[i].weight);
        putchar('\n');
    }

    max_profit = fractional_knapsack(capacity, items, n);

    printf("Maximum profit : %f\n", max_profit);
    for (int i = 0; i < n; i++) {
        Item *item = get_item_by_index(i, items, n);
        printf("Consumed %6.2f %% of item #%i.\n",
               item->amount * 100.0, i + 1);
    }

    free(items);

    return EXIT_SUCCESS;
}
