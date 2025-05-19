#include <stdio.h>
#include <stdlib.h>
#include "grafos.h"

/**
 * @brief Inicializa o grafo, definindo tamanho 0 e ligações a NULL.
 * @param g Apontador para o grafo
 * @return 1 se for bem sucedido
 */
int iniciarGrafo(Grafo* g) {
    g->tamanho = 0;
    for (int i = 0; i < MAX_VERTICES; i++) {
        g->vertices[i].ligacoes = NULL;
    }
    return 1;
}

/**
 * @brief Adiciona uma antena ao grafo.
 * @param g Apontador para o grafo
 * @param freq Frequência da antena
 * @param x Coordenada X
 * @param y Coordenada Y
 * @return Índice da antena adicionada ou -1 se falhar
 */
int adicionarAntena(Grafo* g, char freq, int x, int y) {
    if (g->tamanho >= MAX_VERTICES) return -1;
    g->vertices[g->tamanho].freq = freq;
    g->vertices[g->tamanho].x = x;
    g->vertices[g->tamanho].y = y;
    g->vertices[g->tamanho].ligacoes = NULL;
    g->tamanho++;
    return g->tamanho - 1;
}

/**
 * @brief Cria uma ligação entre duas antenas.
 * @param g Apontador para o grafo
 * @param origem Índice do vértice de origem
 * @param destino Índice do vértice de destino
 * @return 1 se for bem sucedido, 0 caso contrário
 */
int criarLigacao(Grafo* g, int origem, int destino) {
    Ligacao* nova = (Ligacao*)malloc(sizeof(Ligacao));
    if (nova == NULL) return 0;
    nova->destino = destino;
    nova->seguinte = g->vertices[origem].ligacoes;
    g->vertices[origem].ligacoes = nova;
    return 1;
}

/**
 * @brief Liga todas as antenas que têm a mesma frequência.
 * @param g Apontador para o grafo
 * @return 1 se for bem sucedido
 */
int ligarAntenasIguais(Grafo* g) {
    for (int i = 0; i < g->tamanho; i++) {
        for (int j = i + 1; j < g->tamanho; j++) {
            if (g->vertices[i].freq == g->vertices[j].freq) {
                criarLigacao(g, i, j);
                criarLigacao(g, j, i);
            }
        }
    }
    return 1;
}

/**
 * @brief Liberta todas as ligações (arestas) existentes no grafo.
 *
 * Esta função percorre todos os vértices e liberta a memória das suas listas
 * de ligações, deixando cada lista vazia. É útil para evitar duplicações de
 * ligações quando se chamam funções como ligarAntenasIguais() mais de uma vez.
 *
 * @param g Apontador para o grafo
 * @return 1 após a limpeza
 */
int limparLigacoes(Grafo* g) {
    for (int i = 0; i < g->tamanho; i++) {
        Ligacao* atual = g->vertices[i].ligacoes;
        while (atual != NULL) {
            Ligacao* temp = atual;
            atual = atual->seguinte;
            free(temp);
        }
        g->vertices[i].ligacoes = NULL;
    }
    return 1;
}

/**
 * @brief Mostra todas as antenas do grafo.
 * @param g Apontador para o grafo
 * @return 1 após mostrar
 */
int mostrarAntenas(Grafo* g) {
    for (int i = 0; i < g->tamanho; i++) {
        printf("\tAntena %c em (%d,%d)\n", g->vertices[i].freq, g->vertices[i].x, g->vertices[i].y);
    }
    return 1;
}

/**
 * @brief Procura o índice de uma antena pelas coordenadas.
 * @param g Apontador para o grafo
 * @param x Coordenada X
 * @param y Coordenada Y
 * @return Índice da antena ou -1 se não existir
 */
int encontrarAntena(Grafo* g, int x, int y) {
    for (int i = 0; i < g->tamanho; i++) {
        if (g->vertices[i].x == x && g->vertices[i].y == y) return i;
    }
    return -1;
}

/**
 * @brief Função auxiliar de DFT (profundidade).
 * @param g Grafo
 * @param atual Índice atual
 * @param visitado Vetor de visitados
 * @return 1
 */
int visitarDFT(Grafo* g, int atual, int* visitado) {
    visitado[atual] = 1;
    printf("\tDFT: (%d,%d)\n", g->vertices[atual].x, g->vertices[atual].y);
    Ligacao* l = g->vertices[atual].ligacoes;
    while (l != NULL) {
        if (!visitado[l->destino]) {
            visitarDFT(g, l->destino, visitado);
        }
        l = l->seguinte;
    }
    return 1;
}

/**
 * @brief Executa DFT (Depth-First Traversal) a partir de uma antena.
 * @param g Apontador para o grafo
 * @param inicio Índice da antena de partida
 * @return 1 após execução
 */
int dft(Grafo* g, int inicio) {
    int visitado[MAX_VERTICES] = {0};
    return visitarDFT(g, inicio, visitado);
}

/**
 * @brief Executa BFT (Breadth-First Traversal) a partir de uma antena.
 * @param g Apontador para o grafo
 * @param inicio Índice da antena de partida
 * @return 1 após execução
 */
int bft(Grafo* g, int inicio) {
    int visitado[MAX_VERTICES] = {0}, fila[MAX_VERTICES];
    int frente = 0, tras = 0;

    fila[tras++] = inicio;
    visitado[inicio] = 1;

    while (frente < tras) {
        int atual = fila[frente++];
        printf("\tBFT: (%d,%d)\n", g->vertices[atual].x, g->vertices[atual].y);

        Ligacao* l = g->vertices[atual].ligacoes;
        while (l != NULL) {
            if (!visitado[l->destino]) {
                fila[tras++] = l->destino;
                visitado[l->destino] = 1;
            }
            l = l->seguinte;
        }
    }
    return 1;
}

/**
 * @brief Mostra todos os caminhos possíveis entre duas antenas.
 * @param g Grafo
 * @param origem Índice da antena de origem
 * @param destino Índice da antena de destino
 * @param caminho Vetor auxiliar de caminho
 * @param comprimento Comprimento atual do caminho
 * @param visitado Vetor de visitados
 * @return 1
 */
int mostrarTodosCaminhos(Grafo* g, int origem, int destino, int* caminho, int comprimento, int* visitado) {
    visitado[origem] = 1;
    caminho[comprimento++] = origem;

    if (origem == destino) {
        for (int i = 0; i < comprimento; i++) {
            printf("\t(%d,%d)", g->vertices[caminho[i]].x, g->vertices[caminho[i]].y);
            if (i < comprimento - 1) printf(" -> ");
        }
        printf("\n");
    } else {
        Ligacao* l = g->vertices[origem].ligacoes;
        while (l != NULL) {
            if (!visitado[l->destino]) {
                mostrarTodosCaminhos(g, l->destino, destino, caminho, comprimento, visitado);
            }
            l = l->seguinte;
        }
    }

    visitado[origem] = 0;
    return 1;
}

/**
 * @brief Verifica interseções geométricas entre ligações de duas frequências distintas (A-A vs B-B).
 * 
 * Considera como interseção o cruzamento entre arestas da frequência A com arestas da frequência B,
 * se os segmentos (x1,y1)-(x2,y2) se cruzam no espaço.
 * 
 * @param g Grafo
 * @param freqA Primeira frequência (ex: 'A')
 * @param freqB Segunda frequência (ex: 'B')
 * @return 1 se correr com sucesso
 */
int mostrarIntersecoes(Grafo* g, char freqA, char freqB) {
    int encontrou = 0;

    for (int i = 0; i < g->tamanho; i++) {
        if (g->vertices[i].freq != freqA) continue;

        Ligacao* la = g->vertices[i].ligacoes;
        while (la != NULL) {
            if (g->vertices[la->destino].freq != freqA || i > la->destino) {
                la = la->seguinte;
                continue;
            }

            int ax1 = g->vertices[i].x, ay1 = g->vertices[i].y;
            int ax2 = g->vertices[la->destino].x, ay2 = g->vertices[la->destino].y;

            for (int j = 0; j < g->tamanho; j++) {
                if (g->vertices[j].freq != freqB) continue;

                Ligacao* lb = g->vertices[j].ligacoes;
                while (lb != NULL) {
                    if (g->vertices[lb->destino].freq != freqB || j > lb->destino) {
                        lb = lb->seguinte;
                        continue;
                    }

                    int bx1 = g->vertices[j].x, by1 = g->vertices[j].y;
                    int bx2 = g->vertices[lb->destino].x, by2 = g->vertices[lb->destino].y;

                    int d1 = (bx2 - bx1) * (ay1 - by1) - (by2 - by1) * (ax1 - bx1);
                    int d2 = (bx2 - bx1) * (ay2 - by1) - (by2 - by1) * (ax2 - bx1);
                    int d3 = (ax2 - ax1) * (by1 - ay1) - (ay2 - ay1) * (bx1 - ax1);
                    int d4 = (ax2 - ax1) * (by2 - ay1) - (ay2 - ay1) * (bx2 - ax1);

                    if ((d1 * d2 < 0) && (d3 * d4 < 0)) {
                        printf("\t\tIntersecao entre ligacao %c(%d,%d)-(%d,%d) e %c(%d,%d)-(%d,%d)\n",
                            freqA, ax1, ay1, ax2, ay2,
                            freqB, bx1, by1, bx2, by2);
                        encontrou = 1;
                    }

                    lb = lb->seguinte;
                }
            }

            la = la->seguinte;
        }
    }

    if (!encontrou) {
        printf("Nenhuma intersecao entre ligacoes de %c e %c.\n", freqA, freqB);
    }

    return 1;
}

/**
 * @brief Guarda o grafo num ficheiro binário.
 * @param g Grafo
 * @param nome Nome do ficheiro
 * @return 1 se for bem sucedido
 */
int guardarGrafoBinario(Grafo* g, const char* nome) {
    FILE* f = fopen(nome, "wb");
    if (!f) return 0;

    fwrite(&g->tamanho, sizeof(int), 1, f);
    for (int i = 0; i < g->tamanho; i++) {
        VerticeSimples v = {
            g->vertices[i].freq,
            g->vertices[i].x,
            g->vertices[i].y
        };
        fwrite(&v, sizeof(VerticeSimples), 1, f);
    }

    fclose(f);
    return 1;
}

/**
 * @brief Carrega um grafo de um ficheiro binário.
 * @param g Grafo
 * @param nome Nome do ficheiro
 * @return 1 se for bem sucedido
 */
int carregarGrafoBinario(Grafo* g, const char* nome) {
    FILE* f = fopen(nome, "rb");
    if (!f) return 0;

    int tamanhoLido = 0;
    fread(&tamanhoLido, sizeof(int), 1, f);

    iniciarGrafo(g);
    for (int i = 0; i < tamanhoLido; i++) {
        VerticeSimples v;
        fread(&v, sizeof(VerticeSimples), 1, f);
        adicionarAntena(g, v.freq, v.x, v.y);
    }

    fclose(f);
    ligarAntenasIguais(g);
    return 1;
}