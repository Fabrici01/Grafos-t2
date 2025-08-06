#include <stdio.h>
#include <stdlib.h>

#define INFINITO 99999999

int minimaDistancia(int distancia[], int vertices, int visitado[]);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }

    FILE *arquivo = fopen(argv[1], "r");
    if (arquivo == NULL) {
        return 1;
    }

    int vertices = 0, arestas = 0;
    fscanf(arquivo, "%d %d", &vertices, &arestas);

    int **grafo = malloc(vertices * sizeof(int *));
    for (int i = 0; i < vertices; i++) {
        grafo[i] = calloc(vertices, sizeof(int));
    }

    for (int i = 0; i < arestas; i++) {
        int u, v, w;
        fscanf(arquivo, "%d %d %d", &u, &v, &w);
        grafo[u - 1][v - 1] = w;
        grafo[v - 1][u - 1] = w;
    }

    int origem, destino, num_proibido;
    fscanf(arquivo, "%d %d %d", &origem, &destino, &num_proibido);
    
    fclose(arquivo);

    int predecessor[vertices], distancia[vertices], visitado[vertices];

    for (int i = 0; i < vertices; i++) {
        predecessor[i] = -1;
        distancia[i] = INFINITO;
        visitado[i] = 0;
    }

    for (int i = 0; i < vertices; i++) {
        if ((i + 1 > vertices - num_proibido) && (i + 1 != destino) && (i + 1 != origem)) {
            visitado[i] = 1;
        }
    }

    distancia[origem - 1] = 0;

    for (int i = 0; i < vertices; i++) {
        int u = minimaDistancia(distancia, vertices, visitado);

        if (u == -1) {
            break;
        }

        visitado[u] = 1;
        
        for (int v = 0; v < vertices; v++) {
            if (!visitado[v] && grafo[u][v] && distancia[u] != INFINITO && distancia[u] + grafo[u][v] < distancia[v]) {
                distancia[v] = distancia[u] + grafo[u][v];
                predecessor[v] = u;
            }
        }
    }
    
    if (distancia[destino - 1] == INFINITO) {
        printf("YL nao podera realizar esta viagem\n");
    } else {
        printf("%d\n", distancia[destino - 1]);
    }

    for (int i = 0; i < vertices; i++) {
        free(grafo[i]);
    }
    free(grafo);

    return 0;
}

int minimaDistancia(int distancia[], int vertices, int visitado[]) {
    int min = INFINITO;
    int i = -1;

    for (int j = 0; j < vertices; j++) {
        if (visitado[j] == 0 && distancia[j] <= min) {
            min = distancia[j];
            i = j;
        }
    }
    return i;
}