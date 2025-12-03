// Program to read 'n' integers from input.txt and display the second smallest
// and second largest element in the array.

#include <stdio.h>
#include <limits.h>

int main() {
    int n;
    FILE *fp = fopen("input.txt", "r");

    if (fp == NULL) {
        printf("Error: Could not open file.\n");
        return 1;
    }

    if (fscanf(fp, "%d", &n) != 1 || n < 2) {
        printf("Invalid array size in file.\n");
        fclose(fp);
        return 1;
    }

    int arr[n];
    for (int i = 0; i < n; i++) {
        if (fscanf(fp, "%d", &arr[i]) != 1) {
            printf("File does not contain enough integers.\n");
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);

    int smallest = INT_MAX, second_smallest = INT_MAX;
    int largest = INT_MIN, second_largest = INT_MIN;

    for (int i = 0; i < n; i++) {
        if (arr[i] < smallest) {
            second_smallest = smallest;
            smallest = arr[i];
        } else if (arr[i] < second_smallest && arr[i] != smallest) {
            second_smallest = arr[i];
        }

        if (arr[i] > largest) {
            second_largest = largest;
            largest = arr[i];
        } else if (arr[i] > second_largest && arr[i] != largest) {
            second_largest = arr[i];
        }
    }

    if (second_smallest == INT_MAX)
        printf("Second Smallest = Not found (no unique second smallest value)\n");
    else
        printf("Second Smallest = %d\n", second_smallest);

    if (second_largest == INT_MIN)
        printf("Second Largest = Not found (no unique second largest value)\n");
    else
        printf("Second Largest = %d\n", second_largest);

    return 0;
}
