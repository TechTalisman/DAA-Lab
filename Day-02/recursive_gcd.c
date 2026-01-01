// Computes the GCD of integer pairs from an input file using recursion and writes the results to an output file.

#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b); 
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <source file> <destination file>\n", argv[0]);
        return 1;
    }

    char *sourceFile = argv[1];
    char *destFile = argv[2];

    FILE *in = fopen(sourceFile, "r");
    FILE *out = fopen(destFile, "w");

    if (!in || !out) {
        printf("Error opening file.\n");
        return 1;
    }

    int a, b;
    while (fscanf(in, "%d %d", &a, &b) == 2) {
        int result = gcd(a, b);
        fprintf(out, "The GCD of %d and %d is %d\n", a, b, result);
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
