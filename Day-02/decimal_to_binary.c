// Converts decimal numbers from an input file to 16-bit binary using recursion and file handling.

#include <stdio.h>
#include <stdlib.h>

void decToBin(int num, char *binary, int index) {
    if (index < 0)
        return;
    binary[index] = (num % 2) + '0';
    decToBin(num / 2, binary, index - 1);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <n> <source file> <destination file>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    char *sourceFile = argv[2];
    char *destFile = argv[3];

    FILE *in = fopen(sourceFile, "r");
    FILE *out = fopen(destFile, "w");

    if (!in || !out) {
        printf("Error opening file.\n");
        return 1;
    }

    int num, count = 0;
    while (count < n && fscanf(in, "%d", &num) == 1) {
        char binary[17] = {0}; 
        decToBin(num, binary, 15);
        fprintf(out, "The binary equivalent of %d is %s\n", num, binary);
        count++;
    }

    fclose(in);
    fclose(out);

    out = fopen(destFile, "r");
    char line[100];
    while (fgets(line, sizeof(line), out)) {
        printf("%s", line);
    }
    fclose(out);

    return 0;
}
