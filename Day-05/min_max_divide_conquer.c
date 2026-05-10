// to find minimum and maximum elements in an array using divide and conquer

#include <stdio.h>
struct Result {
    int min;
    int max;
};

struct Result findMinMax(int arr[], int low, int high) {
    struct Result res, left, right;
    if (low == high) {
        res.min = res.max = arr[low];
        return res;
    }
    if (high == low + 1) {
        if (arr[low] < arr[high]) {
            res.min = arr[low];
            res.max = arr[high];
        } else {
            res.min = arr[high];
            res.max = arr[low];
        }
        return res;
    }
    int mid = (low + high) / 2;
    left = findMinMax(arr, low, mid);
    right = findMinMax(arr, mid + 1, high);

    res.min = (left.min < right.min) ? left.min : right.min;
    res.max = (left.max > right.max) ? left.max : right.max;

    return res;
}

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    struct Result ans = findMinMax(arr, 0, n - 1);

    printf("Minimum element: %d\n", ans.min);
    printf("Maximum element: %d\n", ans.max);

    return 0;
}
 
