#ifndef __PAIR_H__
#define __PAIR_H__
typedef struct str_pair* STR_pair;

/**
 * @brief Função responsável pela criação
 * de um par do tipo String de informação do
 * Utilizador
 * @param fst 1ªcomponente do par,snd 2ªcomponente do par
 * @return criação do Par
 */

STR_pair create_str_pair(char* fst, char* snd);

/**
 * @brief Função responsável por permitir que a
 * 1ª componente do par possa ser alterada
 * @param pair Par com as 2 componentes, str String passada
 */

void set_fst_str(STR_pair pair, char* str);

/**
 * @brief Função responsável por permitir que a
 * 2ªcomponente do par possa ser alterada
 * @param pair Par com as 2 componentes, str String passada
 *
 */

void set_snd_str(STR_pair pair, char* str);

/**
 * @brief Função responsável pela leitura
 * da 1ª componente do par
 * @param pair Par com as 2 componentes
 * @return Array com a informação relativa à 1ª componente
 */

char* get_fst_str(STR_pair pair);

/**
 * @brief Função responsável pela leitura
 * da 2ª componente do par
 * @param pair Par com as 2 componentes
 * @return Array com a informação relativa à 2ªcomponente
 */

char* get_snd_str(STR_pair pair);

/**
 * @brief  Função responsável pela libertação
 *na memória do Par
 * @param pair Par com as 2 componentes
 */

void free_str_pair(STR_pair pair);


typedef struct long_pair* LONG_pair;

/**
 * @brief Função responsável pela criação
 * de um par
 * @param fst 1ªcomponente do par,snd 2ªcomponente do par
 * @return criação do Par
 */
LONG_pair create_long_pair(long fst, long snd);


/**
 * @brief Função responsável por permitir que a
 * 1ª componente do par possa ser alterada
 * @param pair Par com as 2 componentes, str String passada
 */
void set_fst_long(LONG_pair pair, long l);


/**
 * @brief Função responsável por permitir que a
 * 2ªcomponente do par possa ser alterada
 * @param pair Par com as 2 componentes, str String passada
 *
 */
void set_snd_long(LONG_pair pair, long l);

/**
 * @brief Função responsável pela leitura
 * da 1ª componente do par
 * @param pair Par com as 2 componentes
 * @return Array com a informação relativa à 1ª componente
 */
long get_fst_long(LONG_pair pair);

/**
 * @brief Função responsável pela leitura
 * da 2ª componente do par
 * @param pair Par com as 2 componentes
 * @return Array com a informação relativa à 2ªcomponente
 */
long get_snd_long(LONG_pair pair);


/**
 * @brief  Função responsável pela libertação
 *na memória do Par
 * @param pair Par
 */
void free_long_pair(LONG_pair pair);


#endif
