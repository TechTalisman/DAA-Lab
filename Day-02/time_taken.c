// Generates 500 random numbers within a fixed range and measures the program’s execution time.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 500
#define LOWER 20
#define UPPER 80

int main() {
    int numbers[SIZE];
    clock_t start_time, end_time;
    double cpu_time_used;

    srand(time(0));
    start_time = clock();

    for (int i = 0; i < SIZE; i++) {
        numbers[i] = (rand() % (UPPER - LOWER + 1)) + LOWER;
    }

    printf("Generated Random Numbers:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    end_time = clock();
    //converting in sec as 1 sec has 10 pow 6 teaks and clock_t generates time in teaks.
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("\nTime taken to execute: %f seconds\n", cpu_time_used);

    return 0;
}
