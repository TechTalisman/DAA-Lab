// Generates and prints 10 random integers between 20 and 80 using rand().

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int LOWER = 20;
    int UPPER = 80;

    srand(time(0));

    for (int i = 0; i < 10; i++) {
        int random_num = (rand() % (UPPER - LOWER + 1)) + LOWER;
        printf("%d\n", random_num);
    }

    return 0;
}
