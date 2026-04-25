#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

long long comparisons = 0;

// --------- Cross-platform High Resolution Timer ---------
#ifdef _WIN32
#include <windows.h>
long long get_time_ns() {
    LARGE_INTEGER freq, counter;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&counter);
    return (long long)(counter.QuadPart * 1e9 / freq.QuadPart);
}
#else
long long get_time_ns() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (long long)ts.tv_sec * 1e9 + ts.tv_nsec;
}
#endif

// --------- Partition Function ---------
int partition(int arr[], int low, int high) {
    int pivot = arr[high], i = low - 1;
    for (int j = low; j < high; j++) {
        comparisons++;
        if (arr[j] <= pivot) {
            i++;
            int temp = arr[i]; arr[i] = arr[j]; arr[j] = temp;
        }
    }
    int temp = arr[i + 1]; arr[i + 1] = arr[high]; arr[high] = temp;
    return i + 1;
}
 
// --------- Quick Sort ---------
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// --------- File Handling ---------
void generateFile(const char *filename, int n, int type) {
    FILE *f = fopen(filename, "w");
    if (!f) { printf("File error!\n"); return; }

    if (type == 1) { for (int i = 1; i <= n; i++) fprintf(f, "%d ", i); }
    else if (type == 2) { for (int i = n; i >= 1; i--) fprintf(f, "%d ", i); }
    else { for (int i = 0; i < n; i++) fprintf(f, "%d ", rand() % (n * 10)); }

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

// --------- Scenario Detector ---------
const char* detectScenario(int type) {
    if (type == 1) return "Worst Case";   // Already sorted ascending
    else if (type == 2) return "Worst Case"; // Descending, still unbalanced
    else return "Average Case";           // Random
}

// --------- Main ---------
int main() {
    srand(time(0));
    int choice, n;
    printf("Enter number of entries (1000/3000/5000/9000/12000): ");
    scanf("%d", &n);

    do {
        printf("\nMAIN MENU (QUICK SORT)\n");
        printf("1. Ascending Data\n2. Descending Data\n3. Random Data\n4. EXIT\n");
        printf("Enter option: ");
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 3) {
            char inFile[30], outFile[30];
            if (choice == 1) { generateFile("inAsce.dat", n, 1); strcpy(inFile, "inAsce.dat"); strcpy(outFile, "outQuickAsce.dat"); }
            else if (choice == 2) { generateFile("inDesc.dat", n, 2); strcpy(inFile, "inDesc.dat"); strcpy(outFile, "outQuickDesc.dat"); }
            else { generateFile("inRand.dat", n, 3); strcpy(inFile, "inRand.dat"); strcpy(outFile, "outQuickRand.dat"); }

            int *arr = (int *)malloc(n * sizeof(int));
            int size = readFile(inFile, arr);

            printf("\nBefore Sorting:\n");
            for (int i = 0; i < size; i++) printf("%d ", arr[i]);

            comparisons = 0;
            long long start = get_time_ns();
            quickSort(arr, 0, size - 1);
            long long end = get_time_ns();

            writeFile(outFile, arr, size);

            printf("\n\nAfter Sorting:\n");
            for (int i = 0; i < size; i++) printf("%d ", arr[i]);

            printf("\n\nNumber of Comparisons: %lld", comparisons);
            printf("\nExecution Time: %lld nanoseconds", end - start);
            printf("\nScenario: %s\n", detectScenario(choice));

            free(arr);
        }
    } while (choice != 4);

    return 0;
}
