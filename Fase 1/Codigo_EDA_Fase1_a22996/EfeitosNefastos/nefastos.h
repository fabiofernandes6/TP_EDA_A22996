#ifndef NEFASTOS_H
#define NEFASTOS_H

#include "../ListaAntenas/antenas.h"

/**
 * @brief Estrutura que representa um efeito nefasto, causado por antenas em conflito.
 */
typedef struct efeitoNefasto {
    int x;                             ///< Coordenada X do efeito
    int y;                             ///< Coordenada Y do efeito
    struct efeitoNefasto* proximo;    ///< Próximo efeito na lista
} EfeitoNefasto;

/**
 * @brief Deduz os efeitos nefastos provocados por pares de antenas com a mesma frequência.
 * 
 * Para cada par de antenas idênticas, calcula dois pontos externos que representam
 * os efeitos nefastos gerados, e adiciona-os à lista.
 * 
 * @param lista Lista ligada de antenas
 * @param largura Largura do mapa
 * @param altura Altura do mapa
 * @return Lista ligada de efeitos nefastos
 */
EfeitoNefasto* deduzirEfeitosNefastos(Antena* lista, int largura, int altura);

/**
 * @brief Mostra todos os efeitos nefastos na consola.
 * 
 * @param lista Lista ligada de efeitos nefastos
 * @return A mesma lista, sem alterações
 */
EfeitoNefasto* mostrarEfeitosNefastos(EfeitoNefasto* lista);

/**
 * @brief Liberta a memória ocupada pelos efeitos nefastos.
 * 
 * @param lista Lista ligada de efeitos nefastos
 * @return NULL após limpar tudo
 */
EfeitoNefasto* limparEfeitosNefastos(EfeitoNefasto* lista);

#endif