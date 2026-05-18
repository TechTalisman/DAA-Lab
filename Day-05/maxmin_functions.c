// to find the maximum and minimum elements of an array using three different function approaches

#include <stdio.h>
#include <limits.h>

void maxmin1(int a[], int s, int e) {
    int max = INT_MIN, min = INT_MAX;
    for (int i = s; i <= e; i++) {
        if (a[i] > max) max = a[i];
        if (a[i] < min) min = a[i];
    }
    printf("maxmin1 -> Max: %d, Min: %d\n", max, min);
}

int* maxmin2(int a[], int s, int e) {
    static int result[2];
    int max = INT_MIN, min = INT_MAX;
    for (int i = s; i <= e; i++) {
        if (a[i] > max) max = a[i];
        if (a[i] < min) min = a[i];
    }
    result[0] = max;
    result[1] = min;
    return result;
}

void maxmin3(int a[], int s, int e, int *min, int *max) {
    *max = INT_MIN;
    *min = INT_MAX;
    for (int i = s; i <= e; i++) {
        if (a[i] > *max) *max = a[i];
        if (a[i] < *min) *min = a[i];
    }
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

    maxmin1(arr, 0, n - 1);

    int *res = maxmin2(arr, 0, n - 1);
    printf("maxmin2 -> Max: %d, Min: %d\n", res[0], res[1]);

    int min, max;
    maxmin3(arr, 0, n - 1, &min, &max);
    printf("maxmin3 -> Max: %d, Min: %d\n", max, min);

    return 0;
}
