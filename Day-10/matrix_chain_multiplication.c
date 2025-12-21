// to compute the minimum number of scalar multiplications and the optimal parenthesization for Matrix Chain Multiplication uses dynamic programming 

#include <stdio.h>
#include <limits.h>

#define MAX 20   

int M[MAX][MAX], S[MAX][MAX]; 

void printOptimalParens(int i, int j, int n) {
    if (i == j) {
        printf("A%d", i);
    } else {
        printf("(");
        printOptimalParens(i, S[i][j], n);
        printf(" ");
        printOptimalParens(S[i][j] + 1, j, n);
        printf(")");
    }
}

int main() {
    int n, i, j, k, L, q;
    int p[MAX];  
    
    printf("Enter number of matrices: ");
    scanf("%d", &n);

    int rows[MAX], cols[MAX];
    
    for (i = 1; i <= n; i++) {
        printf("Enter row and col size of A%d: ", i);
        scanf("%d %d", &rows[i], &cols[i]);

        if (i > 1 && rows[i] != cols[i-1]) {
            printf("Error: Incompatible dimensions between A%d and A%d\n", i-1, i);
            return 1;
        }
    }

    p[0] = rows[1];
    for (i = 1; i <= n; i++) {
        p[i] = cols[i];
    }

    for (i = 1; i <= n; i++) {
        M[i][i] = 0;
    }

    for (L = 2; L <= n; L++) {  // L is chain length
        for (i = 1; i <= n - L + 1; i++) {
            j = i + L - 1;
            M[i][j] = INT_MAX;
            for (k = i; k <= j - 1; k++) {
                q = M[i][k] + M[k+1][j] + p[i-1] * p[k] * p[j];
                if (q < M[i][j]) {
                    M[i][j] = q;
                    S[i][j] = k;
                }
            }
        }
    }

    printf("\nM Table:\n");
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (j < i)
                printf("0\t");
            else
                printf("%d\t", M[i][j]);
        }
        printf("\n");
    }

    printf("\nS Table:\n");
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            if (j < i)
                printf("0\t");
            else
                printf("%d\t", S[i][j]);
        }
        printf("\n");
    }

    printf("\nOptimal parenthesization: ");
    printOptimalParens(1, n, n);
    printf("\n");
 
    printf("The optimal ordering of the given matrices requires %d scalar multiplications.\n", M[1][n]);

    return 0;
}
