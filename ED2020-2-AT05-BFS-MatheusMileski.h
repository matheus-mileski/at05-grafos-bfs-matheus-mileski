#ifndef AT05_GRAFOS_BFS_MATHEUS_MILESKI_ED2020_2_AT05_BFS_MATHEUSMILESKI_H
#define AT05_GRAFOS_BFS_MATHEUS_MILESKI_ED2020_2_AT05_BFS_MATHEUSMILESKI_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Constantes
#define MAXTAM 20
#define MAXTAMSTR 1024
#define BRANCO 0
#define CINZA 1
#define PRETO 2
#define INFINITO 999

// Estrutura do Vértice para BFS
typedef struct {
	int cor;
	int tempo_d;
	int pai;
} Vertice;

// Estrutura Fila Dinamica
typedef struct NoFila *PtrNoFila;

typedef struct NoFila {
	int vertice;
	PtrNoFila proximo;
} NoFila;

typedef struct {
	PtrNoFila inicio;
	PtrNoFila fim;
	int tamanho;
} FilaDinamica;

// Estrutura GrafoLista Matriz de Adjacencia
typedef struct {
	int maior_aresta;
	int **matriz;
} GrafoMatriz;

// Estrutura GrafoLista Lista de Adjacencia
struct AdjListNode {
	int vertice;
	struct AdjListNode *proximo;
};

struct ListaAdj {
	struct AdjListNode *inicio;
};

struct GrafoLista {
	int vertice;
	struct ListaAdj *array;
};

// Funcoes Fila Dinamica
void iniciaFila(FilaDinamica *fila);
void imprimeFila(FilaDinamica *fila);
void enfileira(int x, FilaDinamica *fila);
int desenfileira(FilaDinamica *fila);
bool estaVaziaFila(FilaDinamica *fila);

// Funcoes GrafoLista Matriz
void iniciaGrafoMatriz(GrafoMatriz *grafo, int tam);
void imprimeGrafoMatriz(GrafoMatriz *grafo);
bool insereGrafoMatriz(GrafoMatriz *grafo, int v1, int v2);
void destroiGrafoMatriz(GrafoMatriz *grafo);
void bfsMatriz(GrafoMatriz *grafo, int vBusca, FILE *saida);

// Funcoes GrafoLista Lista
struct AdjListNode* adicionaNoLista(int dest);
struct GrafoLista* iniciaGrafo(int V);
bool adicionaAresta(struct GrafoLista* grafo, int src, int dest);
void imprimeGrafoLista(struct GrafoLista* grafo);
void destroiGrafoLista(struct GrafoLista* grafo);
void bfsLista(struct GrafoLista* grafo, int vBusca, FILE *saida);

// Funcoes Arquivo
bool checar_arquivo(char *arquivo);

#endif //AT05_GRAFOS_BFS_MATHEUS_MILESKI_ED2020_2_AT05_BFS_MATHEUSMILESKI_H
