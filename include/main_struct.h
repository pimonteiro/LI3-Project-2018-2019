#ifndef __MAIN_STRUCT_H__
#define __MAIN_STRUCT_H__

#include <glib.h>
#include "profile.h"
#include "question.h"
#include "answer.h"
#include "post.h"
#include "mydate.h"

/**
 *  @brief Estrutura principal: 3 Hashtables para users, posts e tags respetivamente.
 *  Tardis é uma estrutura que consiste num array de arrays com GSequences,
 *   o primeiro array corresponde aos anos, o segundo array corresponde aos
 *    meses e aos dias desse ano. Por último, temos o número de tags
*/
typedef struct TCD_community* TAD_community;

/**
 *  @brief Função responsável pela inserção de uma
 *  tag na Estrutura Principal
 *  @param com Estrutura Principal,tag_name Nome da tag, id ID da tag
*/
void insertTag_TAD(TAD_community com, char* tag_name, long id);

/**
 *  @brief Função que se segue é responsável por percorrer toda
 *  a HashTable para cada valor/chave do perfil do user
 *  @param com Estrutura Principal, f Função para cada chave/valor
 *  user_data Utilizador
 */
void profilesForEach_TAD(TAD_community com, GHFunc f, gpointer user_data);

/**
 *  @brief Função que é responsável pela criação da estrutura principal
    com todas as suas estruturas e componentes
 *  @return criação da estrutura
 */
TAD_community create_main_struct();

/**
 *  @brief  Função que inicializa a Estrutura Principal
 *  @return inicialização da Estrutura
 */
TAD_community init();

/**
 *  @brief  Função que liberta tanto as componentes existentes na
 *  Estrutura Principal como a Estrutura em si
 *  @param com Estruturs Principal
 *  @return libertação da Estrutura
 */
TAD_community clean(TAD_community com);

/**
 *  @brief Função responsável pela inserção de um
 *  user na Estrutura Principal
 *  @param com Estrutura Principal, p Perfil de um user, id ID de um user
 */
void insertProfile_TAD(TAD_community com, PROFILE p, long id);

/**
 *  @brief Função responsável pela inserção de uma
 *  questão na Estrutura Principal
 *  @param com Estrutura Principal, q Questão, id ID da questão, owner_id ID de
 * quem formulou a questão,p Post desse user,start Data de escrita da questão
 */
void insertQuestion_TAD(TAD_community com, QUESTION q, long id, long owner_id, POST p, MyDate start);

/**
 *  @brief Função responsável pela inserção de uma
 *  resposta na Estrutura Principal
 *  @param com Estrutura Principal, a Answer, id ID da resposta, owner_id ID de
 * quem formulou a resposta,parent_id ID da questão correspondente a uma dada resposta
 *  p Post desse user,start Data de escrita da resposta
 */
void insertAnswer_TAD(TAD_community com, ANSWER a, long id, long owner_id, long parent_id, POST p, MyDate start);

/**
 *  @brief Função que se segue responsável pela leitura
 *  do perfil de um user da Estrutura Principal
 *  @param com Estrutura Principal, id ID de um user
 *  @return Perfis de um user dado o id
 */
PROFILE getProfile_TAD(TAD_community com, long id);

/**
 *  @brief  Função que se segue responsável pela leitura dos
 *  Posts da Estrutura Principal
 *  @param com Estrutura Principal, id do Utilizador
 *  @return Post dado o id
 */
POST getPost_TAD(TAD_community com, long id);

/**
 *  @brief Função que calcula o intervalo arbitrário de tempo que é pedido em algumas queries
 *  @param com Estrutura Principal, inicio  e fim intervalo arbitrário de datas, type 1-Question e 2-Answer,f compara datas
 *  @return GSequence de um intervalo aleatório de tempo
 */
GSequence* getFromToF_TAD(TAD_community com, MyDate inicio, MyDate fim, int type, GCompareDataFunc f);

/**
 *  @brief Função que se segue tira uma tag da Estrutura
 *  @param com Estrutura Principal, tag Array com as tags
 *  @return valor da tag
 */
long getQuark_TAD(TAD_community com, char* tag);

/**
 *  @brief Função responsável pela leitura do número
 *  de tags da Estrutura Principal
 *  @param com Estrutura Principal
 *  @return Número de tags
*/
long getNTags_TAD(TAD_community com);

/**
 *  @brief Função que se segue faz com que seja possível
 *  a modificação do número de tags da Estrutura Principal
 *  @param com Estrutura Principal
 */
void setNTags_TAD(TAD_community com);

/**
 *  @brief Função responsável pela leitura das chave das
 *  tags da Estrutura Principal e guardá-las numa lista
 *  @param com Estrutura Principal
 *  @return Dupla lista ligada com as tags
*/
GList* getTags_TAD(TAD_community com);

#endif //__MAIN_STRUCT_H__
