// to find the Longest Common Subsequence (LCS) between two strings using Dynamic Programming 

#include <stdio.h>
#include <string.h>

#define MAX 100

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    char X[MAX], Y[MAX];
    int m, n;
    int L[MAX][MAX];
    int i, j, index;
    char lcs[MAX];

    printf("Enter the first string into an array: ");
    scanf("%s", X);
    printf("Enter the second string into an array: ");
    scanf("%s", Y);

    m = strlen(X);
    n = strlen(Y);

    for (i = 0; i <= m; i++) {
        for (j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                L[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                L[i][j] = L[i - 1][j - 1] + 1; 
            else
                L[i][j] = max(L[i - 1][j], L[i][j - 1]);
        }
    }

    index = L[m][n];
    lcs[index] = '\0'; 

    i = m;
    j = n;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs[index - 1] = X[i - 1];
            i--;
            j--;
            index--;
        } else if (L[i - 1][j] > L[i][j - 1])
            i--;
        else if(L[i-1][j] < L[i][j-1])
            j--;
        else {
            if(X[i-1]<Y[j-1]) i--;
            else j--;
        }
    }

    printf("LCS: %s\n", lcs);
    printf("LCS Length: %d\n", L[m][n]);

    return 0;
}
