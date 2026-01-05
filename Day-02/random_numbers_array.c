// Generates and displays 500 random integers between 20 and 80 using rand().

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 500
#define LOWER 20
#define UPPER 80

int main() {
    int numbers[SIZE];
    
    srand(time(0));

    for (int i = 0; i < SIZE; i++) {
        numbers[i] = (rand() % (UPPER - LOWER + 1)) + LOWER;
    }
    printf("Generated Random Numbers:\n");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", numbers[i]);
    }

    return 0;
}
