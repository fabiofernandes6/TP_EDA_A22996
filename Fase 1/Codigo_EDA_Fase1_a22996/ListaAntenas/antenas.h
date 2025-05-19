#ifndef ANTENAS_H
#define ANTENAS_H

/**
 * @brief Estrutura que representa uma antena com frequência e coordenadas.
 */
typedef struct antena {
    char frequencia;           ///< Frequência da antena (ex: 'A', 'B')
    int x;                     ///< Coordenada X da antena
    int y;                     ///< Coordenada Y da antena
    struct antena* proximo;    ///< Próxima antena na lista
} Antena;

/**
 * @brief Cria uma nova antena.
 * 
 * @param frequencia Frequência da antena (caractere)
 * @param x Coordenada X
 * @param y Coordenada Y
 * @return Apontador para a nova antena criada, ou NULL se falhar
 */
Antena* criarAntena(char frequencia, int x, int y);

/**
 * @brief Insere uma nova antena no início da lista.
 * 
 * @param lista Lista atual de antenas
 * @param frequencia Frequência da nova antena
 * @param x Coordenada X
 * @param y Coordenada Y
 * @return Nova cabeça da lista
 */
Antena* inserirAntena(Antena* lista, char frequencia, int x, int y);

/**
 * @brief Remove a antena nas coordenadas especificadas.
 * 
 * @param lista Lista ligada de antenas
 * @param x Coordenada X
 * @param y Coordenada Y
 * @return Nova cabeça da lista após remoção
 */
Antena* removerAntena(Antena* lista, int x, int y);

/**
 * @brief Mostra todas as antenas registadas na lista.
 * 
 * @param lista Lista ligada de antenas
 * @return O mesmo ponteiro da lista (pode ser NULL no final)
 */
Antena* mostrarAntenas(Antena* lista);

/**
 * @brief Liberta toda a memória ocupada pelas antenas da lista.
 * 
 * @param lista Lista ligada de antenas
 * @return NULL após limpar
 */
Antena* limparAntenas(Antena* lista);

/**
 * @brief Carrega antenas a partir de um ficheiro de texto.
 * 
 * Os caracteres do ficheiro representam antenas (exceto '.').
 * 
 * @param lista Lista inicial (pode ser NULL)
 * @param nomeFicheiro Nome do ficheiro a abrir
 * @return Lista ligada com as antenas carregadas
 */
Antena* carregarFicheiro(Antena* lista, const char* nomeFicheiro);

#endif