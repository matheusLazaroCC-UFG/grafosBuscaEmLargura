/**
 * Algoritmo de busca em largura
*/

#include <stdio.h>
#include <stdlib.h>

#define tamanho 100

struct fila{
    int itens[tamanho];
    int sucessor;
    int antecessor;
};

struct fila* criarfila();

void enfileirar(struct fila* q, int);

int desenfileirar(struct fila* q);

void mostrar(struct fila* q);

int verificaVazia(struct fila* q);

void imprimirFila(struct fila* q);

struct no {
    int vertice;
    struct no* proximo;
};

struct no* criarNo(int);

struct grafo {
    int numVertices;
    struct no** ListasAdj;
    int* visitado;
};

void BuscaEmLargura(struct grafo* grafo, int verticeInicial) {
    struct fila* q = criarfila();

    grafo->visitado[verticeInicial] = 1;
    enfileirar(q, verticeInicial);

    while (!verificaVazia(q)) {
        imprimirFila(q);
        int verticeAtual = desenfileirar(q);
        printf(" %d visitado\n", verticeAtual);

        struct no* temp = grafo->ListasAdj[verticeAtual];

        while (temp) {
            int adjvertice = temp->vertice;

            if (grafo->visitado[adjvertice] == 0) {
                grafo->visitado[adjvertice] = 1;
                enfileirar(q, adjvertice);
            }
            temp = temp->proximo;
        }
    }
}

struct no* criarNo(int v) {
    struct no* novoNo = malloc(sizeof(struct no));
    novoNo->vertice = v;
    novoNo->proximo = NULL;

    return novoNo;
}

struct grafo* criarGrafo(int vertices) {
    struct grafo* grafo = malloc(sizeof(struct grafo));
    grafo->numVertices = vertices;

    grafo->ListasAdj = malloc(vertices * sizeof(struct no*));
    grafo->visitado = malloc(vertices * sizeof(int));

    int i;
    for (i = 0; i < vertices; i++) {
        grafo->ListasAdj[i] = NULL;
        grafo->visitado[i] = 0;
    }

    return grafo;
}

void adicionarBorda(struct grafo* grafo, int inicio, int fim) {
    // Adicionar borda do inicio ao fim
    struct no* novoNo = criarNo(fim);
    novoNo->proximo = grafo->ListasAdj[inicio];
    grafo->ListasAdj[inicio] = novoNo;

    // Adicionar borda do fim ao inicio
    novoNo = criarNo(inicio);
    novoNo->proximo = grafo->ListasAdj[fim];
    grafo->ListasAdj[fim] = novoNo;
}

struct fila* criarfila() {
    struct fila* q = malloc(sizeof(struct fila));
    q->sucessor = -1;
    q->antecessor = -1;
    return q;
}

int verificaVazia(struct fila* q) {
    if (q->antecessor == -1)
        return 1;
    else
        return 0;
}

void enfileirar(struct fila* q, int valor) {
    if (q->antecessor == tamanho - 1)
        printf("\nA fila esta cheia!");
    else {
        if (q->sucessor == -1)
            q->sucessor = 0;
        q->antecessor++;
        q->itens[q->antecessor] = valor;
    }
}

int desenfileirar(struct fila* q) {
    int item;
    if (verificaVazia(q)) {
        printf("A fila esta vazia!");
        item = -1;
    } else {
        item = q->itens[q->sucessor];
        q->sucessor++;
        if (q->sucessor > q->antecessor) {
            printf("Reiniciando a fila");
            q->sucessor = q->antecessor = -1;
        }
    }
    return item;
}

void imprimirFila(struct fila* q) {
    int i = q->sucessor;

    if (verificaVazia(q)) {
        printf("A fila esta vazia!");
    } else {
        for (i = q->sucessor; i < q->antecessor + 1; i++) {
            printf("%d ", q->itens[i]);
        }
    }
}

int main() {
    /**struct grafo* grafo = criarGrafo(6);

    adicionarBorda(grafo, 0, 1);
    adicionarBorda(grafo, 0, 2);
    adicionarBorda(grafo, 1, 2);
    adicionarBorda(grafo, 1, 4);
    adicionarBorda(grafo, 1, 3);
    adicionarBorda(grafo, 2, 4);
    adicionarBorda(grafo, 3, 4);*/

    /*struct grafo* grafo = criarGrafo(7);

    adicionarBorda(grafo, 0, 1);
    adicionarBorda(grafo, 0, 2);
    adicionarBorda(grafo, 1, 2);
    adicionarBorda(grafo, 2, 3);
    adicionarBorda(grafo, 2, 4);
    adicionarBorda(grafo, 3, 4);
    adicionarBorda(grafo, 2, 5);
    adicionarBorda(grafo, 2, 6);*/

    struct grafo* grafo = criarGrafo(5);

    adicionarBorda(grafo, 0, 1);
    adicionarBorda(grafo, 0, 2);
    adicionarBorda(grafo, 0, 3);
    adicionarBorda(grafo, 1, 2);
    adicionarBorda(grafo, 2, 4);


    BuscaEmLargura(grafo, 0);

    scanf("%*c");
    return 0;
}