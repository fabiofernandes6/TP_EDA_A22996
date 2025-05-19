#ifndef GRAFOS_H
#define GRAFOS_H

/// Número máximo de antenas (vértices) no grafo
#define MAX_VERTICES 100

/**
 * @brief Representa uma ligação (aresta) entre dois vértices do grafo.
 */
typedef struct Ligacao {
    int destino;                 ///< Índice do vértice de destino
    struct Ligacao* seguinte;   ///< Próxima ligação
} Ligacao;

/**
 * @brief Representa um vértice (antena) no grafo.
 */
typedef struct Vertice {
    char freq;                  ///< Frequência da antena
    int x, y;                   ///< Coordenadas da antena
    Ligacao* ligacoes;          ///< Lista de ligações para outras antenas
} Vertice;

/**
 * @brief Representa um grafo com lista fixa de vértices.
 */
typedef struct Grafo {
    Vertice vertices[MAX_VERTICES]; ///< Lista de antenas (vértices)
    int tamanho;                    ///< Número atual de vértices
} Grafo;

/**
 * @brief Estrutura simples usada para guardar e carregar vértices em ficheiros binários.
 */
typedef struct VerticeSimples {
    char freq;   ///< Frequência
    int x;       ///< Coordenada X
    int y;       ///< Coordenada Y
} VerticeSimples;

/**
 * @brief Inicializa um grafo vazio.
 * @param g Apontador para o grafo
 * @return 1 se for bem sucedido
 */
int iniciarGrafo(Grafo* g);

/**
 * @brief Adiciona uma nova antena ao grafo.
 * @param g Grafo
 * @param freq Frequência da antena
 * @param x Coordenada X
 * @param y Coordenada Y
 * @return Índice da antena adicionada, ou -1 em caso de erro
 */
int adicionarAntena(Grafo* g, char freq, int x, int y);

/**
 * @brief Liga entre si todas as antenas que têm a mesma frequência.
 * @param g Grafo
 * @return 1 após criação das ligações
 */
int ligarAntenasIguais(Grafo* g);

/**
 * @brief Liberta todas as ligações atuais do grafo, evitando duplicações.
 * @param g Apontador para o grafo
 * @return 1 após limpar
 */
int limparLigacoes(Grafo* g);

/**
 * @brief Mostra na consola todas as antenas registadas no grafo.
 * @param g Grafo
 * @return 1 após mostrar
 */
int mostrarAntenas(Grafo* g);

/**
 * @brief Encontra o índice de uma antena com coordenadas específicas.
 * @param g Grafo
 * @param x Coordenada X
 * @param y Coordenada Y
 * @return Índice da antena ou -1 se não for encontrada
 */
int encontrarAntena(Grafo* g, int x, int y);

/**
 * @brief Realiza percurso em profundidade (DFT) a partir de uma antena.
 * @param g Grafo
 * @param inicio Índice da antena de partida
 * @return 1 após execução
 */
int dft(Grafo* g, int inicio);

/**
 * @brief Realiza percurso em largura (BFT) a partir de uma antena.
 * @param g Grafo
 * @param inicio Índice da antena de partida
 * @return 1 após execução
 */
int bft(Grafo* g, int inicio);

/**
 * @brief Mostra todos os caminhos possíveis entre duas antenas.
 * @param g Grafo
 * @param origem Índice da antena de origem
 * @param destino Índice da antena de destino
 * @param caminho Vetor auxiliar para armazenar o caminho atual
 * @param comprimento Comprimento atual do caminho
 * @param visitado Vetor de visitados
 * @return 1 após mostrar
 */
int mostrarTodosCaminhos(Grafo* g, int origem, int destino, int* caminho, int comprimento, int* visitado);

/**
 * @brief Mostra as interseções entre ligações de frequências distintas (A-A vs B-B).
 * @param g Grafo
 * @param freqA Primeira frequência
 * @param freqB Segunda frequência
 * @return 1 após mostrar
 */
int mostrarIntersecoes(Grafo* g, char freqA, char freqB);

/**
 * @brief Guarda o estado atual do grafo num ficheiro binário.
 * @param g Grafo
 * @param nome Nome do ficheiro
 * @return 1 se bem sucedido, 0 caso contrário
 */
int guardarGrafoBinario(Grafo* g, const char* nome);

/**
 * @brief Carrega um grafo a partir de um ficheiro binário.
 * @param g Grafo
 * @param nome Nome do ficheiro
 * @return 1 se bem sucedido, 0 caso contrário
 */
int carregarGrafoBinario(Grafo* g, const char* nome);

#endif