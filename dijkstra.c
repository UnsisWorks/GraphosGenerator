#include <limits.h>
#include <stdbool.h>
#include "grafo.c"

int minimo(int distancia[], bool visitados[], int n) {
    // Inicializar el índice del vértice con la distancia mínima
    int min = INT_MAX, min_index;
 
    for (int v = 0; v < n; v++)
        if (visitados[v] == false && distancia[v] <= min)
            min = distancia[v], min_index = v;
 
    return min_index;
}

void dijkstra(struct Grafo *grafo, int inicio) {
    int distancia[grafo->num_nodos]; // Almacena la distancia mínima desde el origen a cada vértice
    bool visitados[grafo->num_nodos]; // Almacena si un vértice ha sido visitado o no
 
    // Inicializar todas las distancias como infinito y todos los vértices como no visitados
    for (int i = 0; i < grafo->num_nodos; i++) {
        distancia[i] = INT_MAX;
        visitados[i] = false;
    }
 
    // La distancia desde el origen a si mismo es siempre cero
    distancia[inicio] = 0;
 
    // Encontrar la distancia mínima para todos los vértices
    for (int i = 0; i < grafo->num_nodos - 1; i++) {
        int u = minimo(distancia, visitados, grafo->num_nodos);
 
        visitados[u] = true;
 
        // Actualizar la distancia de los vértices adyacentes a u
        for (int v = 0; v < grafo->num_nodos; v++) {
            if (!visitados[v] && grafo->matriz_adyacencia[u][v] &&
                distancia[u] != INT_MAX && distancia[u] + grafo->matriz_adyacencia[u][v] < distancia[v])
                distancia[v] = distancia[u] + grafo->matriz_adyacencia[u][v];
        }
    }
 
    // Imprimir las distancias mínimas
    printf("Vértice\tDistancia mínima desde el origen\n");
    for (int i = 0; i < grafo->num_nodos; i++)
        printf("%d\t\t%d\n", i, distancia[i]);
}
