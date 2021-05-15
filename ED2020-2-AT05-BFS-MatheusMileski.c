#include "ED2020-2-AT05-BFS-MatheusMileski.h"

bool checar_arquivo(char *arquivo) {
	
	if (arquivo[strlen(arquivo) - 4] == '.' &&
	    arquivo[strlen(arquivo) - 3] == 't' &&
	    arquivo[strlen(arquivo) - 2] == 'x' &&
	    arquivo[strlen(arquivo) - 1] == 't') {
		return true;
	}
	
	return false;
}

void iniciaFila(FilaDinamica *fila) {
	fila->inicio = NULL;
	fila->fim = NULL;
	fila->tamanho = 0;
}

bool estaVaziaFila(FilaDinamica *fila) {
	return (fila->tamanho == 0);
}

void enfileira(int x, FilaDinamica *fila) {
	// verifica se essa aresta ja foi inserida pra essa palavra
	if (!estaVaziaFila(fila)) {
		if (fila->fim->vertice == x)
			return;
	}
	
	PtrNoFila aux;
	aux = (PtrNoFila) malloc(sizeof(PtrNoFila));
	aux->vertice = x;
	if (estaVaziaFila(fila)) {
		fila->inicio = aux;
		fila->fim = aux;
		aux->proximo = NULL;
	} else {
		aux->proximo = NULL;
		fila->fim->proximo = aux;
		fila->fim = aux;
	}
	fila->tamanho++;
}

int desenfileira(FilaDinamica *fila) {
	int v = -1;
	if (!estaVaziaFila(fila)) {
		PtrNoFila aux;
		aux = fila->inicio;
		fila->inicio = fila->inicio->proximo;
		v = aux->vertice;
		free(aux);
		fila->tamanho--;
		
		return v;
	}
	return -1;
}

void imprimeFila(FilaDinamica *fila) {
	PtrNoFila aux;
	
	for (aux = fila->inicio; aux != NULL; aux = aux->proximo) {
		printf("%d", aux->vertice);
		if (aux->proximo != NULL) {
			printf(",");
		}
	}
	printf("\n");
}

void iniciaGrafoMatriz(GrafoMatriz *grafo, int tam) {
	grafo->matriz = malloc(tam * sizeof(int *));
	grafo->maior_aresta = tam;
	
	for (int i = 0; i < tam; i++) {
		grafo->matriz[i] = malloc(tam * sizeof(int));
		for (int j = 0; j < tam; j++) {
			grafo->matriz[i][j] = 0;
		}
	}
}

void imprimeGrafoMatriz(GrafoMatriz *grafo) {
	
	printf("\t  ");
	for (int i = 0; i < grafo->maior_aresta; i++) {
		printf("%2i ", i + 1);
	}
	printf("\n");
	
	for (int i = 0; i < grafo->maior_aresta; i++) {
		printf("%2i: | ", i + 1);
		for (int j = 0; j < grafo->maior_aresta; j++) {
			printf("%2d ", grafo->matriz[i][j]);
		}
		printf("\n");
	}
}

bool insereGrafoMatriz(GrafoMatriz *grafo, int v1, int v2) {
	
	if (v1 >= 1 && v1 <= MAXTAM && v2 >= 1 && v2 <= MAXTAM) {
		grafo->matriz[v1 - 1][v2 - 1] = 1;
		return true;
	}
	
	return false;
}

void destroiGrafoMatriz(GrafoMatriz *grafo) {
	for (int i = 0; i < grafo->maior_aresta; i++) {
		free(grafo->matriz[i]);
	}
	free(grafo->matriz);
}

void bfsMatriz(GrafoMatriz *grafo, int vBusca, FILE *saida) {
	
	Vertice *array = malloc(grafo->maior_aresta * sizeof(Vertice));
	
	int u;
	
	FilaDinamica fila;
	iniciaFila(&fila);
	
	for (int i = 0; i < grafo->maior_aresta; i++) {
		//inicializa os vertices
		array[i].cor = BRANCO;
		array[i].tempo_d = INFINITO;
		array[i].pai = -1;
	}
	
	array[vBusca].cor = CINZA;
	array[vBusca].tempo_d = 0;
	array[vBusca].pai = -1;
	
	enfileira(vBusca, &fila);
	
	while (!estaVaziaFila(&fila)) {
		// imprimeFila(&fila);
		u = desenfileira(&fila);
		
		for (int i = 0; i < grafo->maior_aresta; i++) {
			if (grafo->matriz[u][i] == 1 && array[i].cor == BRANCO) {
				array[i].cor = CINZA;
				array[i].tempo_d = 1 + array[u].tempo_d;
				array[i].pai = u;
				enfileira(i, &fila);
			}
		}
		
		array[u].cor = PRETO;
		
	}
	
	// Imprimir tabela BFS
	printf("\nV \t C \t  T  \t P\n");
	for (int i = 0; i < grafo->maior_aresta; i++) {
		printf("%i \t %i \t %3i \t %i \n", i + 1, array[i].cor, array[i].tempo_d, array[i].pai + 1);
	}
	
	printf("\n");
	
	//Imprimir Vertices e tempo
	// loop para verificar os vertices com menor tempo, indo de 0 - ultima aresta (pior caso)
	for (int i = 0; i <= grafo->maior_aresta; i++) {
		if (i == grafo->maior_aresta)
			i = INFINITO;
		// loop para imprimir os vertices com tempo i
		for (int j = 0; j < grafo->maior_aresta; ++j) {
			if (i == array[j].tempo_d){
				printf("%i[d=%i]\n",j+1,i);
				fprintf(saida, "%i[d=%i]\n", j+1, i);
			}
		}
	}
	free(array);
}

struct AdjListNode* adicionaNoLista(int dest)
{
	struct AdjListNode* newNode = (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
	newNode->vertice = dest;
	newNode->proximo = NULL;
	return newNode;
}

struct GrafoLista* iniciaGrafo(int V)
{
	struct GrafoLista* grafo = (struct GrafoLista*) malloc(sizeof(struct GrafoLista));
	grafo->vertice = V;

	grafo->array = (struct ListaAdj*) malloc(V * sizeof(struct ListaAdj));

	int i;
	for (i = 0; i < V; ++i)
		grafo->array[i].inicio = NULL;
	
	return grafo;
}

bool adicionaAresta(struct GrafoLista* grafo, int src, int dest)
{
	if (src >= 0 && src <= MAXTAM && dest >= 0 && dest <= MAXTAM) {
		struct AdjListNode *novoNo = adicionaNoLista(dest);
		novoNo->proximo = grafo->array[src].inicio;
		grafo->array[src].inicio = novoNo;
		return true;
	}
	
	return false;
}

void imprimeGrafoLista(struct GrafoLista* grafo)
{
	for (int i = 0; i < grafo->vertice; i++)
	{
		struct AdjListNode* aux = grafo->array[i].inicio;
		printf("%i [",i+1);
		while (aux)
		{
			printf(" -> %i", aux->vertice+1);
			aux = aux->proximo;
		}
		printf("]\n");
	}
}

void destroiGrafoLista(struct GrafoLista* grafo)
{
	struct AdjListNode* atual;
	struct AdjListNode* proximo;
	
	for (int i = 0; i < grafo->vertice; i++)
	{
		atual = grafo->array[i].inicio;
		while (atual != NULL)
		{
			proximo = atual->proximo;
			free(atual);
			atual = proximo;;
		}
	}
	free(grafo->array);
	free(grafo);
	
}

void bfsLista(struct GrafoLista* grafo, int vBusca, FILE *saida) {
	
	Vertice *array = malloc(grafo->vertice * sizeof(Vertice));
	
	int u;
	
	FilaDinamica fila;
	iniciaFila(&fila);
	
	for (int i = 0; i < grafo->vertice; i++) {
		//inicializa os vertices
		array[i].cor = BRANCO;
		array[i].tempo_d = INFINITO;
		array[i].pai = -1;
	}
	
	array[vBusca].cor = CINZA;
	array[vBusca].tempo_d = 0;
	array[vBusca].pai = -1;
	
	enfileira(vBusca, &fila);
	
	while (!estaVaziaFila(&fila)) {
		u = desenfileira(&fila);
		
		struct AdjListNode *aux = grafo->array[u].inicio;
		
		while (aux != NULL){
			if (array[aux->vertice].cor  == BRANCO){
				array[aux->vertice].cor = CINZA;
				array[aux->vertice].tempo_d = 1 + array[u].tempo_d;
				array[aux->vertice].pai = u;
				enfileira(aux->vertice, &fila);
			}
			aux = aux->proximo;
		}
		
		array[u].cor = PRETO;
		
	}
	
	// Imprimir tabela BFS
	printf("\nV \t C \t  T  \t P\n");
	for (int i = 0; i < grafo->vertice; i++) {
		printf("%i \t %i \t %3i \t %i \n", i + 1, array[i].cor, array[i].tempo_d, array[i].pai + 1);
	}
	
	printf("\n");
	
	//Imprimir Vertices e tempo
	// loop para verificar os vertices com menor tempo, indo de 0 - ultima aresta (pior caso)
	for (int i = 0; i <= grafo->vertice; i++) {
		if (i == grafo->vertice)
			i = INFINITO;
		// loop para imprimir os vertices com tempo i
		for (int j = 0; j < grafo->vertice; ++j) {
			if (i == array[j].tempo_d){
				printf("%i[d=%i]\n",j+1,i);
				fprintf(saida, "%i[d=%i]\n", j+1, i);
			}
		}
	}
	free(array);
}

int main(int argc, char *argv[]) {
	FILE *entrada;
	FILE *saida;
	char str[MAXTAMSTR];
	char aux[MAXTAMSTR];
	char *pch;
	char *ach;
	char delimitadores[] = " ,.:;<>()\n\t\r\f\v\0";
	int tam = 0;
	int tam_aux = 0;
	int vBusca = 0;
	
	// checar se os argumentos foram inseridos
	if (argc == 3) {
		printf("Arquivo de Entrada: %s\n", argv[1]);
		printf("Arquivo de Saida: %s\n", argv[2]);
	} else {
		printf("\nERRO!\nArgumentos Invalidos.\nEncerrando Execucao.\n");
		exit(1);
	}
	
	// checar se o arquivo de entrada e saida são .txt
	if (!checar_arquivo(argv[1])) {
		printf("\nERRO!\nArquivo de entrada nao e do tipo .txt.\nEncerrando Execucao.\n");
		exit(1);
	}
	if (!checar_arquivo(argv[2])) {
		printf("\nERRO!\nArquivo de saida nao e do tipo .txt.\nEncerrando Execucao.\n");
		exit(1);
	}
	
	// abrindo arquivos
	entrada = fopen(argv[1], "r");
	saida = fopen(argv[2], "w");
	
	if (entrada == NULL) {
		printf("\nERRO!\nArquivo de entrada nao pode ser aberto.\nEncerrando Execucao.\n");
		exit(1);
	}
	if (saida == NULL) {
		printf("\nERRO!\nArquivo de saida nao pode ser aberto.\nEncerrando Execucao.\n");
		exit(1);
	}
	
	// checar se o arquivo de entrada nao esta vazio
	char c = fgetc(entrada);
	
	if (c == EOF) {
		printf("\nERRO!\nArquivo de entrada esta vazio.\nEncerrando Execucao.\n");
		fprintf(saida, "ERRO!\nArquivo de entrada esta vazio.");
		fclose(entrada);
		fclose(saida);
		exit(1);
	}
	
	// recebe o resto da linha
	fgets(str, MAXTAMSTR - 1, entrada);
	
	//verifica o parametro do modo de busca, apenas busca em largura inicialmente
	if (fgetc(entrada) == 'B')
		printf("\nModo de Busca: Busca em Largura (BFS).\n");
	else if (fgetc(entrada) == 'D') {
		printf("\nModo de Busca: Busca em Profundidade (DFS)\nAinda nao implementado.\n");
		exit(1);
	} else {
		printf("\nERRO!\nModo de busca invalido.\nEncerrando Execucao.");
		exit(1);
	}
	
	// recebe o resto da linha
	fgets(str, MAXTAMSTR - 1, entrada);
	switch (c) {
		case 'M':
			printf("\nMatriz de Adjacencia\n");
			
			fgets(str, MAXTAMSTR - 1, entrada);
			
			strcpy(aux,str);
			
			ach = strtok(aux, "(,)");
			tam = atoi(ach);
			
			if(tam>20 || tam<1){
				printf("\nERRO!\nAresta invalida.\nEncerrando Execucao.\n");
				fprintf(saida, "ERRO!\nAresta invalida.");
				free(ach);
				fclose(entrada);
				fclose(saida);
				exit(1);
			}
			
			while(ach != NULL) {
				ach = strtok(NULL, "(,)");
				if (ach == NULL)
					break;
					
				tam_aux = atoi(ach);
				
				if(tam_aux>20 || tam_aux<1){
					printf("\nERRO!\nAresta invalida.\nEncerrando Execucao.\n");
					fprintf(saida, "ERRO!\nAresta invalida.");
					free(ach);
					fclose(entrada);
					fclose(saida);
					exit(1);
				}
				
				if(tam < tam_aux){
					tam = tam_aux;
				}
			}
			
			GrafoMatriz grafo;
			iniciaGrafoMatriz(&grafo, tam);
			
			pch = strtok(str, delimitadores);
			
			while (pch != NULL) {
				if (pch == NULL)
					break;
				
				int v1 = atoi(pch);
				pch = strtok(NULL, delimitadores);
				int v2 = atoi(pch);
				
				if (!insereGrafoMatriz(&grafo, v1, v2)) {
					printf("\nERRO!\nVertice invalido.\nEncerrando Execucao.");
					destroiGrafoMatriz(&grafo);
					fclose(entrada);
					fclose(saida);
				}
				pch = strtok(NULL, delimitadores);
			}
			imprimeGrafoMatriz(&grafo);
			
			fscanf(entrada, "%i", &vBusca);
			
			if (vBusca < 1 || vBusca > grafo.maior_aresta)
				printf("\nERRO!\nVertice de busca invalido.\nEncerrando Execucao.");
			else
				bfsMatriz(&grafo, vBusca - 1, saida);
			
			destroiGrafoMatriz(&grafo);
			
			break;
		case 'L':
			printf("\nLista de Adjacencia\n");
			
			fgets(str, MAXTAMSTR - 1, entrada);
			
			strcpy(aux,str);
			
			ach = strtok(aux, "(,)");
			tam = atoi(ach);
			
			while(ach != NULL) {
				ach = strtok(NULL, "(,)");
				if (ach == NULL)
					break;
				
				tam_aux = atoi(ach);
				
				if(tam < tam_aux){
					tam = tam_aux;
				}
			}
			
			struct GrafoLista* grafoL = iniciaGrafo(tam);
			
			pch = strtok(str, delimitadores);
			
			while (pch != NULL) {
				if (pch == NULL)
					break;
				
				int v1 = atoi(pch);
				pch = strtok(NULL, delimitadores);
				int v2 = atoi(pch);
				
				if (!adicionaAresta(grafoL, v1-1, v2-1)) {
					printf("\nERRO!\nVertice invalido.\nEncerrando Execucao.");
					destroiGrafoLista(grafoL);
					fclose(entrada);
					fclose(saida);
				}
				pch = strtok(NULL, delimitadores);
			}
			
			imprimeGrafoLista(grafoL);
			
			fscanf(entrada, "%i", &vBusca);

			if (vBusca < 1 || vBusca > grafoL->vertice)
				printf("\nERRO!\nVertice de busca invalido.\nEncerrando Execucao.");
			else
				bfsLista(grafoL, vBusca - 1, saida);
			
			destroiGrafoLista(grafoL);
			
			break;
		default:
			printf("ERRO!\nTipo de estrutura inválida.");
			fprintf(saida, "ERRO!\nTipo de estrutura inválida.");
			break;
	}
	
	fclose(entrada);
	fclose(saida);
	
	return 0;
}
