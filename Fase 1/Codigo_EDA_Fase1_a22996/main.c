/**
 * @file main.c
 * @brief Programa principal para gerir antenas e efeitos nefastos.
 *
 * Este programa carrega uma lista de antenas a partir de um ficheiro de texto
 * e determina efeitos nefastos causados por pares de antenas com a mesma frequência.
 * Permite ainda inserir e remover antenas, atualizar os efeitos e visualizar tudo
 * através de um mapa textual.
 */

#include <stdio.h>
#include <stdlib.h>
#include "ListaAntenas/antenas.h"
#include "EfeitosNefastos/nefastos.h"

/**
 * @brief Gera e imprime um mapa textual com antenas e efeitos nefastos.
 * 
 * Antenas são representadas pela letra da sua frequência.
 * Efeitos nefastos são representados por '*'.
 * Espaços vazios são representados por '.'.
 * 
 * @param antenas Lista ligada de antenas
 * @param efeitos Lista ligada de efeitos nefastos
 * @param largura Largura do mapa
 * @param altura Altura do mapa
 * @return NULL (não é usada para devolver valor)
 */
char* gerarMapa(Antena* antenas, EfeitoNefasto* efeitos, int largura, int altura) {
    int tamanho = (largura + 1) * altura + 1; // +1 por linha, +1 para '\0'
    char* mapa = (char*)malloc(tamanho * sizeof(char));
    if (!mapa) return NULL;

    int index = 0;
    for (int y = 0; y < altura; y++) {
        for (int x = 0; x < largura; x++) {
            char simbolo = '.';

            for (Antena* a = antenas; a != NULL; a = a->proximo) {
                if (a->x == x && a->y == y) {
                    simbolo = a->frequencia;
                    break;
                }
            }

            if (simbolo == '.') {
                for (EfeitoNefasto* e = efeitos; e != NULL; e = e->proximo) {
                    if (e->x == x && e->y == y) {
                        simbolo = '*';
                        break;
                    }
                }
            }

            mapa[index++] = simbolo;
        }
        mapa[index++] = '\n';
    }
    mapa[index] = '\0';

    printf("%s", mapa);
    free(mapa);
    return NULL;
}

/**
 * @brief Função principal que coordena as operações sobre antenas e efeitos.
 * 
 * 1. Carrega antenas do ficheiro.
 * 2. Gera o mapa inicial.
 * 3. Deduz e mostra efeitos nefastos.
 * 4. Insere e remove antenas.
 * 5. Atualiza efeitos e mapa após alterações.
 * 6. Limpa toda a memória usada.
 * 
 * @return 0 se terminar com sucesso
 */
int main() {
    printf("\n--- Sistema de Antenas e Efeitos Nefastos ---\n\n");

    Antena* listaAntenas = NULL;
    EfeitoNefasto* listaEfeitos = NULL;

    // 1. Carregar antenas do ficheiro
    listaAntenas = carregarFicheiro(listaAntenas, "estrutura.txt");
    printf(">> Antenas carregadas do ficheiro:\n");
    mostrarAntenas(listaAntenas);

    printf("\n>> Mapa inicial:\n");
    gerarMapa(listaAntenas, listaEfeitos, 12, 12);

    // 2. Deduzir efeitos nefastos iniciais
    listaEfeitos = deduzirEfeitosNefastos(listaAntenas, 12, 12);
    printf("\n>> Efeitos nefastos detetados inicialmente:\n");
    mostrarEfeitosNefastos(listaEfeitos);

    printf("\n>> Mapa com efeitos nefastos:\n");
    gerarMapa(listaAntenas, listaEfeitos, 12, 12);

    listaEfeitos = limparEfeitosNefastos(listaEfeitos);

    // 3. Inserir novas antenas
    listaAntenas = inserirAntena(listaAntenas, 'B', 3, 3);
    listaAntenas = inserirAntena(listaAntenas, 'B', 5, 5);
    printf("\n>> Antenas apos inserir B(3,3) e B(5,5):\n");
    mostrarAntenas(listaAntenas);

    printf("\n>> Mapa apos inserir novas antenas:\n");
    gerarMapa(listaAntenas, listaEfeitos, 12, 12);

    // 4. Atualizar efeitos nefastos
    listaEfeitos = limparEfeitosNefastos(listaEfeitos);
    listaEfeitos = deduzirEfeitosNefastos(listaAntenas, 12, 12);
    printf("\n>> Efeitos nefastos apos inserir novas antenas:\n");
    mostrarEfeitosNefastos(listaEfeitos);

    printf("\n>> Mapa atualizado com novos efeitos nefastos:\n");
    gerarMapa(listaAntenas, listaEfeitos, 12, 12);

    listaEfeitos = limparEfeitosNefastos(listaEfeitos);

    // 5. Remover antenas inseridas
    listaAntenas = removerAntena(listaAntenas, 3, 3);
    listaAntenas = removerAntena(listaAntenas, 5, 5);
    printf("\n>> Antenas apos remover B(3,3) e B(5,5):\n");
    mostrarAntenas(listaAntenas);

    printf("\n>> Mapa apos remocao das antenas B:\n");
    gerarMapa(listaAntenas, listaEfeitos, 12, 12);

    // 6. Efeitos finais
    listaEfeitos = limparEfeitosNefastos(listaEfeitos);
    listaEfeitos = deduzirEfeitosNefastos(listaAntenas, 12, 12);
    printf("\n>> Efeitos nefastos finais:\n");
    mostrarEfeitosNefastos(listaEfeitos);

    printf("\n>> Mapa final:\n");
    gerarMapa(listaAntenas, listaEfeitos, 12, 12);

    // 7. Limpeza final
    listaAntenas = limparAntenas(listaAntenas);
    listaEfeitos = limparEfeitosNefastos(listaEfeitos);

    printf("\nTerminado com sucesso\n");
    return 0;
}