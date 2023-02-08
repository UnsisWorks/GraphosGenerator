#include <limits.h>
#include <stdbool.h>
#include "grafo.c"

#define MAX_NODOS 100

int dijkstra(struct Grafo *grafo, int nodo_inicial, int nodo_final) {
    int distancias[MAX_NODOS];
    bool visitados[MAX_NODOS];
    int cantidad_nodos = grafo->num_nodos;
    int i, j;

    // Inicializar distancias y visitados
    for (i = 0; i < cantidad_nodos; i++) {
        distancias[i] = INT_MAX;
        visitados[i] = false;
    }
    distancias[nodo_inicial] = 0;

    // Algoritmo de Dijkstra
    for (i = 0; i < cantidad_nodos - 1; i++) {
        int nodo_actual = INT_MAX;
        int distancia_minima = INT_MAX;
        for (j = 0; j < cantidad_nodos; j++) {
            if (!visitados[j] && distancias[j] <= distancia_minima) {
                nodo_actual = j;
                distancia_minima = distancias[j];
            }
        }

        visitados[nodo_actual] = true;

        for (j = 0; j < cantidad_nodos; j++) {
            int peso = grafo->matriz_adyacencia[nodo_actual][j];
            if (!visitados[j] && peso && distancias[nodo_actual] != INT_MAX && distancias[nodo_actual] + peso < distancias[j])
                distancias[j] = distancias[nodo_actual] + peso;
       
        }
    }
        return distancias[nodo_final];
}
