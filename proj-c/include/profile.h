#ifndef __PROFILE_H__
#define __PROFILE_H__

#include <glib.h>
#include "post.h"

/**
@file profile.h
Ficheiro da class PROFILE
*/

/**
 *  @brief Estrutura que armazena os principais atributos associados aos utilizadores:
 *  GSequence sao guardadas as questões e respostas criadas pelo dito utilizador;
 *  informação do perfil e nome do utilizador;número de posts;id do utilizador e reputação
 *  de um utilizador
 */

typedef struct profile* PROFILE;

/**
 *  @brief  Função responsável pela criação dos perfis dos utilizadores de
 *  acordo com os atributos acima referidos
 *  @param my_about Informação do perfil,my_id ID do utilizador,my_name
 *  Nome do Utilizador,my_reputation Reputação do Utilizador
 *  @return Criação do Perfil dos Utilizadores
 */

PROFILE create_profile(char* my_about, long my_id, char* my_name, int my_reputation);

/**
 *  @brief  Função que liberta o perfil do utilizador assim como alguns
 *  dos seus atributos
 *  @param p Um Post
 */

void free_profile(void* p);

/**
 *  @brief A função que se segue é responsável pela leitura dos
 *  Posts do perfil de um Utilizador
 *  @param p Perfil Utilizador
 *  @return GSequence com o tipo do Post
 */

GSequence* getPosts_profile(PROFILE p);

/**
 *  @brief A função que se segue é responsável pela leitura da
 *  informação do perfil de um Utilizador
 *  @param p Perfil Utilizador
 *  @return Array com a informação do Utilizador
 */

char* getAboutMe_profile(PROFILE p);

/**
 *  @brief A função que se segue é responsável pela leitura do
 *  nome de um Utilizador
 *  @param p Perfil Utilizador
 *  @return Array com o nome dos vários Utilizadores
 */

char* getName_profile(PROFILE p);

/**
 *  @brief A função que se segue é responsável pela leitura do
 *  número de Posts do perfil de um Utilizador
 *  @param p Perfil Utilizador
 *  @return Número de Posts de um Utilizador
 */

long getNposts_profile(PROFILE p);

/**
 *  @brief A função que se segue é responsável pela leitura
 *  do ID de um Utilizador
 *  @param p Perfil Utilizador
 *  @return ID de um utilizador
 */

long getId_profile(PROFILE p);

/**
 *  @brief A função que se segue é responsável pela leitura da
 *  Reputação de um Utilizador
 *  @param p Perfil Utilizador
 *  @return quantia da Reputação
 */

int getReputation_profile(PROFILE p);

/**
 *  @brief Função responsável pela inserção do utilizador mais recente no início
 *  @param p Perfil do Utilizador,post Post do Utilizador
 */

void insertLastest_profile(PROFILE p, POST post);

#endif /* __PROFILE_H__ */
