#include <stdio.h>
#include <stdlib.h>

struct Edge {
    int u, v, w;
};

int parent[100];
struct Edge edges[100];
struct Edge mst[100];

int find(int i) {
    if (parent[i] != i)
        parent[i] = find(parent[i]);
    return parent[i];
}

void unionSets(int u, int v) {
    int rootU = find(u);
    int rootV = find(v);
    parent[rootU] = rootV;
}

int cmpEdge(const void *a, const void *b) {
    struct Edge *e1 = (struct Edge *)a;
    struct Edge *e2 = (struct Edge *)b;
    if (e1->w != e2->w) return e1->w - e2->w;
    if (e1->u != e2->u) return e1->u - e2->u;
    return e1->v - e2->v;
}

int main() {
    int n, m, i, mstCount = 0, totalWeight = 0;

    printf("Enter the number of vertices and edges (n m), followed by each edge in the format u v w:\n");
    printf("Example:\n");
    printf("9 14\n1 2 4\n... and so on\n\n");

    scanf("%d %d", &n, &m);

    for (i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
    }

    for (i = 1; i <= n; i++)
        parent[i] = i;

    qsort(edges, m, sizeof(struct Edge), cmpEdge);

    for (i = 0; i < m && mstCount < n - 1; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;

        if (find(u) != find(v)) {
            unionSets(u, v);
            mst[mstCount++] = edges[i];
            totalWeight += w;
        }
    }

    printf("\nSelected edges in the Minimum Spanning Tree:\n");
    printf("Edge\t\tCost\n");
    for (i = 0; i < mstCount; i++)
        printf("%d--%d\t\t%d\n", mst[i].u, mst[i].v, mst[i].w);

    printf("Total Weight of the Spanning Tree: %d\n", totalWeight);

    return 0;
}
