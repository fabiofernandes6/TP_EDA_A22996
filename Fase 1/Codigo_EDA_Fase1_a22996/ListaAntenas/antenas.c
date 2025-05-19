#include "antenas.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Cria uma nova antena com frequência e coordenadas indicadas.
 * 
 * @param frequencia Letra da frequência da antena (ex: 'A', 'B')
 * @param x Coordenada X
 * @param y Coordenada Y
 * @return Apontador para a nova antena criada, ou NULL se falhar
 */
Antena* criarAntena(char frequencia, int x, int y) {
    Antena* nova = (Antena*)malloc(sizeof(Antena));
    if (!nova) {
        printf("Erro ao alocar memória para a antena!\n");
        return NULL;
    }
    nova->frequencia = frequencia;
    nova->x = x;
    nova->y = y;
    nova->proximo = NULL;
    return nova;
}

/**
 * @brief Insere uma nova antena no início da lista ligada.
 * 
 * @param lista Lista atual de antenas
 * @param frequencia Frequência da nova antena
 * @param x Coordenada X
 * @param y Coordenada Y
 * @return Nova cabeça da lista
 */
Antena* inserirAntena(Antena* lista, char frequencia, int x, int y) {
    Antena* nova = criarAntena(frequencia, x, y);
    if (!nova) return lista;
    nova->proximo = lista;
    return nova;
}

/**
 * @brief Remove a antena que estiver nas coordenadas (x, y).
 * 
 * @param lista Lista atual de antenas
 * @param x Coordenada X
 * @param y Coordenada Y
 * @return Nova cabeça da lista após remoção
 */
Antena* removerAntena(Antena* lista, int x, int y) {
    Antena *atual = lista, *anterior = NULL;

    while (atual != NULL && (atual->x != x || atual->y != y)) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) return lista;

    if (anterior == NULL) lista = atual->proximo;
    else anterior->proximo = atual->proximo;

    free(atual);
    return lista;
}

/**
 * @brief Mostra todas as antenas da lista.
 * 
 * @param lista Lista ligada de antenas
 * @return O mesmo apontador (termina em NULL)
 */
Antena* mostrarAntenas(Antena* lista) {
    if (!lista) {
        printf("Nenhuma antena registada.\n");
        return lista;
    }

    while (lista) {
        printf("\tFrequencia: %c / Coordenadas: (%d, %d)\n", lista->frequencia, lista->x, lista->y);
        lista = lista->proximo;
    }
    return lista;
}

/**
 * @brief Liberta toda a memória da lista de antenas.
 * 
 * @param lista Lista ligada de antenas
 * @return NULL (lista limpa)
 */
Antena* limparAntenas(Antena* lista) {
    while (lista) {
        Antena* temp = lista;
        lista = lista->proximo;
        free(temp);
    }
    return NULL;
}

/**
 * @brief Carrega antenas a partir de um ficheiro de texto.
 * 
 * Cada linha do ficheiro representa uma linha do mapa.
 * Caracteres diferentes de '.' são considerados antenas.
 * 
 * @param lista Lista inicial de antenas (pode ser NULL)
 * @param nomeFicheiro Caminho para o ficheiro
 * @return Lista ligada de antenas carregada
 */
Antena* carregarFicheiro(Antena* lista, const char* nomeFicheiro) {
    FILE* ficheiro = fopen(nomeFicheiro, "r");
    if (!ficheiro) {
        printf("Erro ao abrir o ficheiro %s!\n", nomeFicheiro);
        return lista;
    }

    char linha[100];
    int y = 0;

    while (fgets(linha, sizeof(linha), ficheiro)) {
        for (int x = 0; linha[x] != '\0' && linha[x] != '\n'; x++) {
            if (linha[x] != '.') {
                lista = inserirAntena(lista, linha[x], x, y);
            }
        }
        y++;
    }

    fclose(ficheiro);
    return lista;
}