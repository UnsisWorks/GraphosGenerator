#include <limits.h>
#include <stdbool.h>
#include "grafo.c"

int V = 0;

int minDistance(int dist[], bool sptSet[])
{
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

void printSolution(int dist[], int n, int parent[])
{
    int *stack = malloc(n * sizeof(int));
    int top = -1;
    printf("Vertex Distance from Source\n");
    for (int i = 0; i < V; i++)
    {
        printf("%d \t\t %d\n", i, dist[i]);
    }

    printf("\nPath\n");
    for (int i = n; i != -1; i = parent[i]) {
        printf("%d <- ", i + 1);
    }
    printf("\n");
    for (int i = n; i != -1; i = parent[i]) {
        stack[++top] = i + 1;
    }

     printf("Path:\n");
    while (top >= 0) {
        printf("%d <- ", stack[top--]);
    }
    printf("\n");

    free(stack);
}

void dijkstra(struct Grafo* grafo, int src, int dest, int parent[])
{
    V = grafo->num_nodos;
    int dist[grafo->num_nodos];
    bool sptSet[grafo->num_nodos];
    // int parent[grafo->num_nodos];

    for (int i = 0; i < V; i++) {
        parent[i] = -1;
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++)
    {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;

        for (int v = 0; v < V; v++)
            if (!sptSet[v] && grafo->matriz_adyacencia[u][v] &&
                dist[u] + grafo->matriz_adyacencia[u][v] < dist[v])
            {
                parent[v] = u;
                dist[v] = dist[u] + grafo->matriz_adyacencia[u][v];
            }
    }

    printSolution(dist, dest, parent);
}
