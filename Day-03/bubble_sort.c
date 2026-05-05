#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


long long comparisons = 0;

// Bubble Sort
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// File generator
void generateFile(const char *filename, int n, int type) {
    FILE *f = fopen(filename, "w");
    if (!f) { printf("File error!\n"); return; }

    if (type == 1) { 
        for (int i = 1; i <= n; i++) fprintf(f, "%d ", i); 
    }
    else if (type == 2) { 
        for (int i = n; i >= 1; i--) fprintf(f, "%d ", i); 
    }
    else { 
        for (int i = 0; i < n; i++) fprintf(f, "%d ", rand() % (n * 10)); 
    }
    fclose(f);
}

int readFile(const char *filename, int arr[]) {
    FILE *f = fopen(filename, "r");
    int n = 0;
    while (fscanf(f, "%d", &arr[n]) == 1) n++;
    fclose(f);
    return n;
}

void writeFile(const char *filename, int arr[], int n) {
    FILE *f = fopen(filename, "w");
    for (int i = 0; i < n; i++) fprintf(f, "%d ", arr[i]);
    fclose(f);
}

// Detect Scenario
const char* detectScenario(int choice) {
    if (choice == 1) return "Best Case";
    if (choice == 2) return "Worst Case";
    return "Average Case";
}

// Main
int main() {
    srand(time(0));
    int choice, n;
    printf("Enter number of entries (1000/3000/5000/9000/12000): ");
    scanf("%d", &n);

    do {
        printf("\nMAIN MENU (BUBBLE SORT)\n");
        printf("1. Ascending Data\n2. Descending Data\n3. Random Data\n4. EXIT\n");
        printf("Enter option: ");
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 3) {
            char inFile[25], outFile[30];
            if (choice == 1) { 
                generateFile("inAsce.dat", n, 1); 
                strcpy(inFile, "inAsce.dat"); 
                strcpy(outFile, "outBubbleAsce.dat"); 
            }
            else if (choice == 2) { 
                generateFile("inDesc.dat", n, 2); 
                strcpy(inFile, "inDesc.dat"); 
                strcpy(outFile, "outBubbleDesc.dat"); 
            }
            else { 
                generateFile("inRand.dat", n, 3); 
                strcpy(inFile, "inRand.dat"); 
                strcpy(outFile, "outBubbleRand.dat"); 
            }

            int arr[n];
            int size = readFile(inFile, arr);

            printf("\nBefore Sorting:\n");
            for (int i = 0; i < size; i++) printf("%d ", arr[i]);

            comparisons = 0;
            clock_t start = clock();
            bubbleSort(arr, size);
            clock_t end = clock();

            writeFile(outFile, arr, size);

            printf("\n\nAfter Sorting:\n");
            for (int i = 0; i < size; i++) printf("%d ", arr[i]);

            double time_taken = ((double)(end - start) * 1e9) / CLOCKS_PER_SEC;
            printf("\n\nNumber of Comparisons: %lld", comparisons);
            printf("\nExecution Time: %.2f nanoseconds", time_taken);
            printf("\nScenario: %s\n", detectScenario(choice));
        }

    } while (choice != 4);

    return 0;
}
