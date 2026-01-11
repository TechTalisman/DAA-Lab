// Implements Dijkstra’s algorithm using an adjacency matrix read from a file

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100
#define INF 1000000000

int cost[MAX][MAX];
int n;
 
void dijkstra(int src) {
    int dist[MAX], visited[MAX], parent[MAX];

    for (int i = 0; i < n; i++) {
        dist[i] = INF;
        visited[i] = 0;
        parent[i] = -1;
    }
    dist[src] = 0;

    for (int iter = 0; iter < n; iter++) {
        int u = -1, best = INF;
        for (int v = 0; v < n; v++) {
            if (!visited[v] && dist[v] < best) {
                best = dist[v];
                u = v;
            }
        }
        if (u == -1) break;       // no more reachable vertices
        visited[u] = 1;

        for (int v = 0; v < n; v++) {
            // treat 0 as NO EDGE (except diagonal entries are permitted as 0)
            if (!visited[v] && cost[u][v] > 0 && dist[u] + cost[u][v] < dist[v]) {
                dist[v] = dist[u] + cost[u][v];
                parent[v] = u;
            }
        }
    }

    printf("Source\tDestination\tCost\tPath\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t", src + 1, i + 1);

        if (dist[i] == INF) {
            printf("INF\t-\n");
            continue;
        }

        printf("%d\t", dist[i]);

        if (i == src) {
            printf("-\n");
            continue;
        }

        int path[MAX], idx = 0, cur = i;
        while (cur != -1) {
            path[idx++] = cur;
            cur = parent[cur];
        }
        for (int k = idx - 1; k >= 0; k--) {
            printf("%d", path[k] + 1);
            if (k > 0) printf("->");
        }
        printf("\n");
    }
}

int main() {
    FILE *fp;
    int src;

    printf("Enter the Number of Vertices: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX) {
        printf("Invalid number of vertices.\n");
        return 1;
    }
 
    fp = fopen("inDiAdjMat1.dat", "r");
    if (fp == NULL) {
        printf("Error: Could not open input file 'inDiAdjMat1.dat'.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (fscanf(fp, "%d", &cost[i][j]) != 1) {
                printf("Error: input file does not contain a %d x %d matrix.\n", n, n);
                fclose(fp);
                return 1;
            }
        }
    }
    fclose(fp);

    printf("Enter the Source Vertex: ");
    if (scanf("%d", &src) != 1 || src < 1 || src > n) {
        printf("Invalid source vertex.\n");
        return 1;
    }
    src--; // convert to 0-based index

    dijkstra(src);

    return 0;
}
