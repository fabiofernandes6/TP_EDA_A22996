#include <stdio.h>
#include <stdlib.h>
#include "nefastos.h"

/**
 * @brief Adiciona um novo efeito nefasto à lista, se estiver dentro dos limites do mapa.
 * 
 * @param lista Lista atual de efeitos nefastos
 * @param x Coordenada X do novo efeito
 * @param y Coordenada Y do novo efeito
 * @param largura Largura do mapa
 * @param altura Altura do mapa
 * @return Nova cabeça da lista de efeitos
 */
EfeitoNefasto* adicionarEfeito(EfeitoNefasto* lista, int x, int y, int largura, int altura) {
    if (x >= 0 && x < largura && y >= 0 && y < altura) {
        EfeitoNefasto* novo = (EfeitoNefasto*)malloc(sizeof(EfeitoNefasto));
        if (novo) {
            novo->x = x;
            novo->y = y;
            novo->proximo = lista;
            return novo;
        }
    }
    return lista;
}

/**
 * @brief Deduz os efeitos nefastos causados por pares de antenas com a mesma frequência.
 * 
 * Para cada par de antenas com a mesma frequência, calcula dois pontos externos que
 * representam os efeitos gerados e adiciona à lista.
 * 
 * @param lista Lista ligada de antenas
 * @param largura Largura do mapa
 * @param altura Altura do mapa
 * @return Lista ligada de efeitos nefastos
 */
EfeitoNefasto* deduzirEfeitosNefastos(Antena* lista, int largura, int altura) {
    EfeitoNefasto* efeitos = NULL;

    for (Antena* a1 = lista; a1 != NULL; a1 = a1->proximo) {
        for (Antena* a2 = a1->proximo; a2 != NULL; a2 = a2->proximo) {
            if (a1->frequencia == a2->frequencia) {
                int dx = a2->x - a1->x;
                int dy = a2->y - a1->y;

                int ex1_x = a1->x - dx;
                int ex1_y = a1->y - dy;
                int ex2_x = a2->x + dx;
                int ex2_y = a2->y + dy;

                efeitos = adicionarEfeito(efeitos, ex1_x, ex1_y, largura, altura);
                efeitos = adicionarEfeito(efeitos, ex2_x, ex2_y, largura, altura);
            }
        }
    }

    return efeitos;
}

/**
 * @brief Mostra todos os efeitos nefastos presentes na lista.
 * 
 * @param lista Lista ligada de efeitos nefastos
 * @return A mesma lista (sem modificações)
 */
EfeitoNefasto* mostrarEfeitosNefastos(EfeitoNefasto* lista) {
    if (!lista) {
        printf("Nenhum efeito nefasto detetado.\n");
        return lista;
    }

    EfeitoNefasto* atual = lista;
    while (atual) {
        printf("\tEfeito Nefasto em: (%d, %d)\n", atual->x, atual->y);
        atual = atual->proximo;
    }

    return lista;
}

/**
 * @brief Liberta a memória de todos os efeitos nefastos da lista.
 * 
 * @param lista Lista ligada de efeitos nefastos
 * @return NULL após limpar tudo
 */
EfeitoNefasto* limparEfeitosNefastos(EfeitoNefasto* lista) {
    while (lista) {
        EfeitoNefasto* temp = lista;
        lista = lista->proximo;
        free(temp);
    }
    return NULL;
}