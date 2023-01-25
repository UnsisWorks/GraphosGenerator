#include <stdio.h>
#include <stdlib.h>

struct Nodo {
    int id;
    struct Nodo *siguiente;
};

int main() {
    int *vector = (int *) malloc(sizeof(int)); //Asigna memoria al vector antes de llamar a realloc()
    int tamanio = 0; //Variable para llevar el registro del tamaño del vector
    int valor;
    char caracter;
    FILE *archivo;

    archivo = fopen("matriz.txt", "r"); //Abre el archivo en modo lectura
    while((caracter = fgetc(archivo)) != EOF) { //Lee caracter por caracter hasta el fin del archivo
        if(caracter != '-') { //Compara si el caracter es diferente de "-"
            valor = caracter - '0'; //Convierte el caracter a un número
            tamanio++;
            vector = (int *) realloc(vector, tamanio * sizeof(int)); //Aumenta el tamaño del vector
            // puts("Abierto");
            vector[tamanio-1] = valor; //Agrega el valor al vector
        }
    }

    fclose(archivo); //Cierra el archivo

    //Imprime el vector
    for(int i = 0; i < tamanio; i++) {
        printf("%d ", vector[i]);
        if (vector[i] == 0-38) {
            puts("");
        }
        
    }
    struct Nodo *grafo[100];
    int num_nodos = 0;

    free(vector); //Libera la memoria asignada al vector

    return 0;
}
