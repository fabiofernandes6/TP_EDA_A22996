#include <stdio.h>
#include <stdlib.h>
#include "Grafos/grafos.h"

int main() {
    printf("\n--- Sistema de Grafos ---\n\n");

    Grafo g;
    iniciarGrafo(&g);

    // Carregar antenas do ficheiro estrutura.txt
    FILE* f = fopen("estrutura.txt", "r");
    if (f == NULL) {
        printf("Erro ao abrir o ficheiro.\n");
        return 1;
    }

    char linha[100];
    int y = 0;
    while (fgets(linha, sizeof(linha), f)) {
        int x = 0;
        while (linha[x] != '\0' && linha[x] != '\n') {
            if (linha[x] != '.') {
                adicionarAntena(&g, linha[x], x, y);
            }
            x++;
        }
        y++;
    }
    fclose(f);

    ligarAntenasIguais(&g);

    printf("\n>> Antenas carregadas:\n");
    mostrarAntenas(&g);

    int origem = encontrarAntena(&g, 6, 5);
    int destino = encontrarAntena(&g, 9, 9);

    // DFT e BFT a partir de uma antena do grupo 'A'
    if (origem >= 0) {
        printf("\n>> Procura em profundidade (DFT) a partir da antena (6,5):\n");
        dft(&g, origem);

        printf("\n>> Procura em largura (BFT) a partir da antena (6,5):\n");
        bft(&g, origem);
    }

    // Todos os caminhos entre duas antenas A
    if (origem >= 0 && destino >= 0) {
        printf("\n>> Todos os caminhos entre (6,5) e (9,9):\n");
        int caminho[MAX_VERTICES];
        int visitado[MAX_VERTICES] = {0};
        mostrarTodosCaminhos(&g, origem, destino, caminho, 0, visitado);
    }

    // Interseções entre frequências A e O
    printf("\n>> Intersecoes entre frequencias A e O:\n");
    mostrarIntersecoes(&g, 'A', 'O');

    // Exemplo: adicionar antenas B para testar interseção
    printf("\n(Exemplo) Inserir antenas B em (6,8) e (8,5) para demonstrar intersecao com A:\n");
    adicionarAntena(&g, 'B', 6, 8);
    adicionarAntena(&g, 'B', 8, 5);

    limparLigacoes(&g);              // Remover ligações antigas
    ligarAntenasIguais(&g);          // Atualizar com as novas ligações

    // Interseções entre frequências A e B
    printf("\n\tIntersecoes entre frequencias A e B:\n");
    mostrarIntersecoes(&g, 'A', 'B');

    // Guardar grafo em ficheiro binário
    printf("\nA guardar grafo em binario...\n");
    guardarGrafoBinario(&g, "grafo_guardado.dat");

    // Carregar grafo do ficheiro binário
    Grafo g2;
    iniciarGrafo(&g2);
    carregarGrafoBinario(&g2, "grafo_guardado.dat");

    printf("\n>> Antenas carregadas do binario:\n");
    mostrarAntenas(&g2);

    return 0;
}