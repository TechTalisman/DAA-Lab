// Generates and prints 10 random numbers between 1 and 100

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    srand(time(0));
    for(int i=0; i<10;i++){
        int random_num = (rand() % 100) +1;
        printf("%d\n", random_num);
    }
    return 0;
}
