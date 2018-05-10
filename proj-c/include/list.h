#ifndef __LONG_LIST__
#define __LONG_LIST__

/**
 * @brief Estrutura que armazena um LONG_list
 */

typedef struct llist * LONG_list;

/**
 *  @brief Função que se segue é responsável pela
 *  criação da lista de retorno que é pedida em algumas queries
 *  @param size Tamanho da lista
 *  @return criação da lista
 */

LONG_list create_list(int size);

/**
 *  @brief A função que se segue é responsável por permitir
 *  a leitura dos elementos da lista
 *  @param l Lista, index Indice
 *  @return acesso à lista
 */

long get_list(LONG_list l, int index);

/**
 *  @brief A função que se segue faz com que seja possível
 *  a alteração de elementos da lista
 *  @param l Lista,index Indice para onde se quer mudar
 *  @param value Novo valor que vai para esse Indice
 */

void set_list(LONG_list l, int index, long value);

/**
 *  @brief Função que liberta uma lista da memória
 *  @param l Lista
 */

void free_list(LONG_list l);

#endif
