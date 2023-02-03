#include <stdio.h>
#include <stdlib.h>

#define MAX_NODOS 100

struct Grafo {
    int matriz_adyacencia[MAX_NODOS][MAX_NODOS];
    int num_nodos;
};

void inicializar_grafo(struct Grafo *grafo, int num_nodos, int adyacencia[][num_nodos]) {
    int i, j;
    printf("nodos: %d\n", num_nodos);
    grafo->num_nodos = num_nodos;
    puts("aqui");
    for(i = 0; i < num_nodos; i++) {
        for(j = 0; j < num_nodos; j++) {
            grafo->matriz_adyacencia[i][j] = 0;
        }
    }
    // Asignar pesos aleatorios a las conexiones
    for(i = 0; i < num_nodos; i++) {
        for(j = 0; j < num_nodos; j++) {
            if(adyacencia[j][i] != 0) {
                grafo->matriz_adyacencia[i][j] = adyacencia[j][i]; // Asignar peso aleatorio entre 1 y 10
                printf("val: %d\n", adyacencia[j][i]);
            }
        }
    }
}

void imprimir_grafo(struct Grafo *grafo) {
    int i, j;
    for(i = 0; i < grafo->num_nodos; i++) {
        for(j = 0; j < grafo->num_nodos; j++) {
            printf("%d ", grafo->matriz_adyacencia[i][j]);
        }
        printf("\n");
    }
}
