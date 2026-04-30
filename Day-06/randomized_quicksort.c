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

// --------- Partition Function with Random Pivot ---------
int partition(int arr[], int low, int high) {
    int pivotIndex = low + rand() % (high - low + 1);

    int temp = arr[pivotIndex];
    arr[pivotIndex] = arr[high];
    arr[high] = temp;

    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        comparisons++;
        if (arr[j] <= pivot) {
            i++;
            int t = arr[i]; arr[i] = arr[j]; arr[j] = t;
        } 
    }
    int t = arr[i + 1]; arr[i + 1] = arr[high]; arr[high] = t;
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
    if (type == 1) return "Ascending Input";
    else if (type == 2) return "Descending Input";
    else return "Random Input";
}

// --------- Run Quick Sort for given n and case ---------
void runCase(int n, int type) {
    char inFile[30], outFile[30];
    if (type == 1) { generateFile("inAsce.dat", n, 1); strcpy(inFile, "inAsce.dat"); strcpy(outFile, "outQuickAsce.dat"); }
    else if (type == 2) { generateFile("inDesc.dat", n, 2); strcpy(inFile, "inDesc.dat"); strcpy(outFile, "outQuickDesc.dat"); }
    else { generateFile("inRand.dat", n, 3); strcpy(inFile, "inRand.dat"); strcpy(outFile, "outQuickRand.dat"); }

    int *arr = (int *)malloc(n * sizeof(int));
    int size = readFile(inFile, arr);

    comparisons = 0;
    long long start = get_time_ns();
    quickSort(arr, 0, size - 1);
    long long end = get_time_ns();

    writeFile(outFile, arr, size);

    printf("\nArray Size: %d | Case: %s", n, detectScenario(type));
    printf("\nComparisons: %lld", comparisons);
    printf("\nExecution Time: %lld ns\n", end - start);

    free(arr);
}

// --------- Main ---------
int main() {
    srand(time(0));
    int sizes[] = {1000, 3000, 5000, 9000, 12000};
    int totalSizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int i = 0; i < totalSizes; i++) {
        int n = sizes[i];
        printf("\n==============================");
        printf("\nRunning Quick Sort for n = %d", n);
        printf("\n==============================\n");

        runCase(n, 1); // Ascending
        runCase(n, 2); // Descending
        runCase(n, 3); // Random
    }

    return 0;
}
