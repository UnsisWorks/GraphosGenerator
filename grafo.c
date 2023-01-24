#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Arco {
    int src, dest, peso;
};

struct Grafo {
    int V, A;
    struct Arco* arcos;
};

struct Grafo* crearGrafo(int V, int A) {
    struct Grafo* grafo = (struct Grafo*) malloc( sizeof(struct Grafo));
    grafo->V = V;
    grafo->A = A;
    grafo->arcos = (struct Arco*) malloc( grafo->A * sizeof( struct Arco ) );
    return grafo;
}
