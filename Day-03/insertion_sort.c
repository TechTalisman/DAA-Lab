// Menu-driven program to read ascending, descending, or random data from a file,
// sort it using Insertion Sort, count comparisons, measure execution time, 
// and store the sorted result in an output file.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

long long comparisons = 0;

// Insertion Sort
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0) {
            comparisons++;
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = key;
    }
}

// File generator
void generateFile(const char *filename, int n, int type) {
    FILE *f = fopen(filename, "w");
    if (!f) { printf("File error!\n"); return; }

    if (type == 1) { // Ascending
        for (int i = 1; i <= n; i++) fprintf(f, "%d ", i);
    } else if (type == 2) { // Descending
        for (int i = n; i >= 1; i--) fprintf(f, "%d ", i);
    } else { // Random
        for (int i = 0; i < n; i++) fprintf(f, "%d ", rand() % (n * 10));
    }
    fclose(f);
}

// Read file
int readFile(const char *filename, int arr[]) {
    FILE *f = fopen(filename, "r");
    int n = 0;
    while (fscanf(f, "%d", &arr[n]) == 1) n++;
    fclose(f);
    return n;
}

// Write file
void writeFile(const char *filename, int arr[], int n) {
    FILE *f = fopen(filename, "w");
    for (int i = 0; i < n; i++) fprintf(f, "%d ", arr[i]);
    fclose(f);
}

// Main
int main() {
    srand(time(0));
    int choice, n;
    printf("Enter number of entries (1000/3000/5000/9000/12000): ");
    scanf("%d", &n);

    do {
        printf("\nMAIN MENU (INSERTION SORT)\n");
        printf("1. Ascending Data\n2. Descending Data\n3. Random Data\n4. EXIT\n");
        printf("Enter option: ");
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 3) {
            char inFile[30], outFile[40];
            char scenario[15];

            if (choice == 1) {
                generateFile("inAsce.dat", n, 1);
                strcpy(inFile, "inAsce.dat");
                strcpy(outFile, "outInsertionAsce.dat");
                strcpy(scenario, "Best Case");
            } 
            else if (choice == 2) {
                generateFile("inDesc.dat", n, 2);
                strcpy(inFile, "inDesc.dat");
                strcpy(outFile, "outInsertionDesc.dat");
                strcpy(scenario, "Worst Case");
            } 
            else {
                generateFile("inRand.dat", n, 3);
                strcpy(inFile, "inRand.dat");
                strcpy(outFile, "outInsertionRand.dat");
                strcpy(scenario, "Average Case");
            }

            int arr[n];
            int size = readFile(inFile, arr);

            printf("\nBefore Sorting:\n");
            for (int i = 0; i < size; i++) printf("%d ", arr[i]);

            comparisons = 0;
            clock_t start = clock();
            insertionSort(arr, size);
            clock_t end = clock();

            writeFile(outFile, arr, size);

            printf("\n\nAfter Sorting:\n");
            for (int i = 0; i < size; i++) printf("%d ", arr[i]);

            double time_taken = ((double)(end - start) * 1e9) / CLOCKS_PER_SEC;
            printf("\n\nNumber of Comparisons: %lld", comparisons);
            printf("\nExecution Time: %.2f nanoseconds", time_taken);
            printf("\nScenario: %s\n", scenario);
        }

    } while (choice != 4);

    return 0;
}
