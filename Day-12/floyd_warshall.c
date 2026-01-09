// Implements Floyd–Warshall algorithm to compute all-pairs shortest paths and display the shortest path between a given source and destination.

#include <stdio.h>
#define INF 9999
#define MAX 10

int n;
int dist[MAX][MAX], next[MAX][MAX];

void printPath(int u, int v) {
    if (next[u][v] == -1) {
        printf("No path\n");
        return;
    }
    printf("%d", u + 1);
    while (u != v) {
        u = next[u][v];
        printf("-->%d", u + 1);
    }
    printf("\n");
}

void floydWarshall() {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }
}

int main() {
    FILE *fp;
    fp = fopen("inDiAdjMat2.dat", "r");
    if (fp == NULL) {
        printf("Error: Cannot open file.\n");
        return 0;
    }

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(fp, "%d", &dist[i][j]);
            if (dist[i][j] == 0 && i != j)
                dist[i][j] = INF;
            if (i == j)
                dist[i][j] = 0;
            if (dist[i][j] != INF)
                next[i][j] = j;
            else
                next[i][j] = -1;
        }
    }
    fclose(fp);

    floydWarshall();

    printf("\nShortest Path Weight Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INF)
                printf("INF ");
            else
                printf("%d ", dist[i][j]);
        }
        printf("\n");
    }

    int u, v;
    printf("\nEnter the source and destination vertex: ");
    scanf("%d %d", &u, &v);
    u--; v--;

    printf("Shortest Path from vertex %d to vertex %d: ", u + 1, v + 1);
    printPath(u, v);
 
    printf("Path weight: %d\n", dist[u][v]);
    return 0;
}
