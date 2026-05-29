// Reads integers from a file, counts duplicate occurrences, and identifies the most repeating element.

#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp;
    int n;

    printf("Enter how many numbers you want to read from file: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid array size.\n");
        return 1;
    }

    int arr[n], freq[n];

    fp = fopen("numbers.txt", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        if (fscanf(fp, "%d", &arr[i]) != 1) {
            printf("File does not contain enough integers.\n");
            fclose(fp);
            return 1;
        }
        freq[i] = -1;
    }
    fclose(fp);

    for (int i = 0; i < n; i++) {
        if (freq[i] != 0) {
            int count = 1;
            for (int j = i + 1; j < n; j++) {
                if (arr[i] == arr[j]) {
                    count++;
                    freq[j] = 0;
                }
            }
            freq[i] = count;
        }
    }

    printf("The content of the array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    int totalDuplicates = 0, maxCount = 0, mostRepeating = -1;
    for (int i = 0; i < n; i++) {
        if (freq[i] > 1) {
            totalDuplicates++;
            if (freq[i] > maxCount) {
                maxCount = freq[i];
                mostRepeating = arr[i];
            } 
        }
    }

    printf("Total number of duplicate values = %d\n", totalDuplicates);
    if (maxCount > 1) {
        printf("The most repeating element in the array = %d\n", mostRepeating);
    } else {
        printf("The most repeating element in the array = None\n");
    }
    return 0;
}
