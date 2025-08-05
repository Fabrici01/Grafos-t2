#include <stdio.h>
#include <stdlib.h>
#define INFINITO 99999999

typedef struct noLista{
    int info;
    struct noLista *prox;
}NoLista;

void criarLista(NoLista** l);
int estaVazia(NoLista** l);
void inserirElemento(NoLista** l, int v);
void removerElemento(NoLista** l, int v);
void liberarLista(NoLista** l);
int numeroElementos(NoLista** l);

int main() {
    int vertices = 0, arestas = 0;
    scanf("%d %d", &vertices, &arestas);
    int grafo[vertices][vertices];
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            grafo[i][j] = 0;
        }
    }
    for (int i = 0; i < arestas; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        grafo[u-1][v-1] = w;
        grafo[v-1][u-1] = w;
    }
    int origem, destino, proibido;
    scanf("%d %d %d", &origem, &destino, &proibido);
    //Algoritmo de Dijkstra
    NoLista* lista;
    criarLista(&lista);
    for (int i = 0; i < vertices; i++)
    {
        if (i+1 != origem) {
            if (i+1 == destino)
            {
                inserirElemento(&lista, i+1);
            }
            else if (i+1 != vertices-proibido+i)
            {
                inserirElemento(&lista, i+1);
            }
        }
    }
    int predecessor[vertices], distancia[vertices];
    for (int i = 0; i < vertices; i++)
    {
        distancia[i] = INFINITO;
        predecessor[i] = -1;
    }
    distancia[origem-1] = 0;
    while (!estaVazia(&lista)) {
        int v = minimo(&distancia, vertices);
    }
    return 0;
}

void criarLista(NoLista** l){
    *l = NULL;
}

int estaVazia(NoLista** l){
    return (*l == NULL);
}

void inserirElemento(NoLista** l, int v){
    NoLista* novo=(NoLista*)malloc(sizeof(NoLista));
    if(novo!=NULL){
        novo->info=v;
        novo->prox=*l;
        *l = novo;
    }
    else{
        printf("Nao foi possivel alocar espaço!\n");
        exit(1);
    }
}

void removerElemento(NoLista** l, int v){
    NoLista *ant=NULL, *p;
    if(!estaVazia(l)){
        for(p=*l; p!=NULL && p->info!=v; p=p->prox){
            ant=p;
        }
        if(p==NULL)
            printf("Elemento nao encontrado!\n");
        else{
            if(ant==NULL)
                *l=p->prox;
            else
                ant->prox = p->prox;
            free(p);
        }
    }
}

void liberarLista(NoLista** l){
    NoLista *p, *temp;
    for(p=*l; p!=NULL; p=temp){
        temp = p->prox;
        free(p);
    }
}

int numeroElementos(NoLista** l){
    NoLista *p;
    int i=0;
    for(p=*l; p!=NULL; p=p->prox){
        i++;
    }
    return i;
}

int minimo (int *vetor, int tamanho) {
    int min = INFINITO;
    for (int i = 0; i < tamanho; i++) {
        if (vetor[i] < min && vetor[i] != 0) {
            min = vetor[i];
        }
    }
    return min;
}