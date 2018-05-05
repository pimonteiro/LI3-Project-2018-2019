#ifndef __ANSWER_H__
#define __ANSWER_H__

#include "mydate.h"

/**
@file answer.h
Ficheiro da class ANSWER
*/

/**
 *  @brief Estrutura que contém os principais atributos associados às respostas como sendo a sua data
 de criação da resposta, o seu id,id de quem escreveu a resposta,id da questão que está a responder,número de comentários,score.
 */

typedef struct answer* ANSWER;

/**
 *  @brief Função responsável pela criação de uma resposta de acordo com os seus atributos
 *  @param my_parent_id ID da pergunta que está a responder, my_owner_id ID de quem faz a resposta, my_id ID da resposta,
 *  my_creation_date Data de criação de uma resposta, my_score Score de uma resposta,comments Número de comentários
 *  @return inicialização de uma resposta ANSWER
 */

ANSWER create_answer(long my_parent_id, long my_owner_id, long my_id, MyDate my_creation_date, int my_score, long comments);

/**
 *  @brief Função que liberta uma resposta da memória
 *  @param a Uma resposta(answer)
 *  @return libertação de uma dada resposta
 */

void free_answer(void* a);

/**
 *  @brief *A função que se segue é responsável pela leitura do atributo
 *  do ID da resposta em causa
 *  @param a Uma resposta
 *  @return ID da resposta
 */

long getID_answer(ANSWER a);

/**
 *  @brief *A função que se segue é responsável pela
 *  leitura da data de criação
 *  @param a Uma resposta
 *  @return Data de criação da resposta
 */

MyDate getDate_answer(ANSWER a);

/**
 *  @brief *A função que se segue é responsável pela
 *  leitura do atributo score
 *  @param a Uma resposta
 *  @return Score de uma resposta
 */

int getScore_answer(ANSWER a);

/**
 *  @brief *A função que se segue é responsável pela leitura do atributo
 *  do ID da questão que está a ser respondida
 *  @param a Uma resposta
 *  @return ID da questão a que se está a responder
 */

long getParentId_answer(ANSWER a);

/**
 *  @brief *A função que se segue é responsável pela
 *  leitura do atributo Id da pessoa que respondeu
 *  @param a Uma resposta
 *  @return ID de quem respondeu
 */

long getOwnerId_answer(ANSWER a);

/**
 *  @brief *A função que se segue é responsável pela leitura do
 *  número de comentários
 *  @param a Uma resposta
 *  @return Número de comentários
 */

long getComments_answer(ANSWER a);

#endif //__ANSWER_H__
