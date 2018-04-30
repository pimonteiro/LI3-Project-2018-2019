#ifndef __POST_H__
#define __POST_H__

#include "answer.h"
#include "question.h"
#include "mydate.h"

/**
 *  @brief  Estrutura de um post. Visto dividir-se em Questions e Answers e ambas
 *   partilharem atributos, decidiu-se implmentar uma union, de forma
 *  a conseguir-se juntar os Posts ou separá-los como fosse mais conveniente.
 */
typedef struct post* POST;

/**
 *  @brief  Função responsável pela criação de um post de acordo com
 *  as questões e/ou respostas
 *  @param type Tipo 1 para Question e 2 para Answer, q Questão, a Answer
 *  @return criação de um Post
 */
POST create_post(long type, QUESTION q, ANSWER a);

/**
 *  @brief  Função que liberta um post da memória
 *  @param p Um Post
 */
void free_post(void* p);

/**
 *  @brief  Função responsável por ver o tipo
 *  de um dado Post,ou seja, se é Questão ou Resposta
 *  @param p Um post
 *  @return Tipo de um Post
 */
long getType_post(POST p);

/**
 *  @brief  Função responsável pela leitura
 *  do conteúdo do tipo Questão
 *  @param p Um Post
 *  @return Conteúdo de uma questão de um Post
 */
QUESTION getQuestion_post(POST p);

/**
 *  @brief  Função responsável pela leitura
 *  do conteúdo do tipo Resposta
 *  @param p Um Post
 *  @return Conteúdo de uma resposta de um Post
 */
ANSWER getAnswer_post(POST p);

/**
 *  @brief  Funão responsável pela leitura
 *  da Data de um determinado Post
 *  @param p Um Post
 *  @return Data de um Post
 */
MyDate getDate_post(POST p);

#endif
