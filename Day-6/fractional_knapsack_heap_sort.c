// to solve the Fractional Knapsack problem by sorting items using Heap Sort based on profit-to-weight ratio.

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int item_id;
    float profit;
    float weight;
    float pw_ratio;
} ITEM;

void swap(ITEM *a, ITEM *b) {
    ITEM temp = *a;
    *a = *b;
    *b = temp; 
}

void heapify(ITEM arr[], int n, int i) {
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if (l < n && arr[l].pw_ratio > arr[largest].pw_ratio)
        largest = l;
    if (r < n && arr[r].pw_ratio > arr[largest].pw_ratio)
        largest = r;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(ITEM arr[], int n) {
    for (int i = n/2 - 1; i >= 0; i--)
        heapify(arr, n, i);
 
    for (int i = n - 1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

float fractionalKnapsack(ITEM items[], int n, float capacity) {
    float total_profit = 0.0;

    printf("\nItem No\tProfit\t\tWeight\t\tAmount to be taken\n");

    for (int i = 0; i < n; i++) {
        float fraction = 0.0;

        if (capacity > 0) {
            if (items[i].weight <= capacity) {
                fraction = 1.0;
                capacity -= items[i].weight;
                total_profit += items[i].profit;
            } else {
                fraction = capacity / items[i].weight;
                total_profit += items[i].profit * fraction;
                capacity = 0;
            }
        }

        printf("%d\t%.6f\t%.6f\t%.6f\n", items[i].item_id, items[i].profit, items[i].weight, fraction);
    }

    return total_profit;
}

int main() {
    int n;
    float capacity;

    printf("Enter the number of items: ");
    scanf("%d", &n);

    ITEM *items = (ITEM*) malloc(n * sizeof(ITEM));

    for (int i = 0; i < n; i++) {
        printf("Enter the profit and weight of item no %d: ", i+1);
        scanf("%f %f", &items[i].profit, &items[i].weight);
        items[i].item_id = i + 1;
        items[i].pw_ratio = items[i].profit / items[i].weight;
    }

    printf("Enter the capacity of knapsack: ");
    scanf("%f", &capacity);

    heapSort(items, n);

    for (int i = 0; i < n/2; i++) {
        swap(&items[i], &items[n - i - 1]);
    }

    float max_profit = fractionalKnapsack(items, n, capacity);
    printf("Maximum profit: %.6f\n", max_profit);

    free(items);
    return 0;
}
