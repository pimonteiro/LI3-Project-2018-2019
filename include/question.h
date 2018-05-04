#ifndef __QUESTION_H__
#define __QUESTION_H__

#include <stdlib.h>
#include "mydate.h"
#include <glib.h>

/**
 *  @brief Estrutura que contém os principais atributos associados às questões
 *  como sendo a data de criação, id das respostas associadas a cada questão
 *  título da questão,tag de cada questão,id da questão,id de quem formulou a
 *  pergunta,número de respostas de cada questão,número de comentários e,por
 *  último,o score de uma pergunta.
 */
typedef struct question* QUESTION;

/**
 *  @brief Função responsável pela criação de uma questão de acordo com os seus atributos
 *  @param  my_id ID da questão,my_title Título de uma questão,my_tags Tag de uma questão,my_owner_id ID de quem faz a questão,
 *  my_creation_date Data de criação de uma questão, my_score Score de uma questão,
 *  my_n_answer Número de respostas de uma determinada questão,comments Número de comentários
 *  @return inicialização de uma resposta ANSWER
 */
QUESTION create_question(long my_id,
                         char* my_title,
                         char* my_tags,
                         long my_owner_id,
                         MyDate my_creation_date,
                         int my_score,
                         long my_n_answer,
                         long comments);

/**
 *  @brief Função que liberta uma questão da memória
 *  @param q Uma questão(question)
 *  @return libertação de uma dada questão
 */
void free_question(void* q);

/**
 *  @brief A função que se segue é responsável pela
 *  leitura do atributo ID da questão
 *  @param q Uma questão
 *  @return ID da questão
 */
long getId_question(QUESTION q);

/**
 *  @brief  A função que se segue é responsável pela
 *  leitura do número de comentários
 *  @param q Uma questão
 *  @return Número de comentários
 */
long getComments_question(QUESTION q);

/**
 *  @brief A função que se segue é responsável pela leitura do atributo
 *  titulo da questão
 *  @param q Uma questão
 *  @return titulo da questão
 */
char* getTitle_question(QUESTION q);

/**
 *  @brief A função que se segue é responsável pela leitura do atributo
 *  ID de quem formulou a questão
 *  @param q Uma questão
 *  @return ID de quem fez a questão
 */
long getOwnerId_question(QUESTION q);

/**
 *  @brief  A função que se segue é responsável pela leitura
 *  da data de criação
 *  @param q Uma questão
 *  @return Data de criação da questão
 */
MyDate getCreationDate_question(QUESTION q);

/**
 *  @brief  A função que se segue é responsável pela
 *  leitura do número de respostas associdas a cada questão
 *  @param q Uma questão
 *  @return Número de respostas
 */
long getNanswers_question(QUESTION q);

/**
 *  @brief A função que se segue é responsável pela leitura do atributo
 *  Score de uma questão
 *  @param q Uma questão
 *  @return Score da questão
 */
int getScore_question(QUESTION q);

/**
 *  @brief A função que se segue é responsável pela leitura do atributo
 *  Tag de cada questão
 *  @param q Uma questão
 *  @return Tag da questão
 */
char* getTags_question(QUESTION q);

/**
 *  @brief  A função que se segue é responsável pela leitura do atributo
 *  Id das respostas associadas a cada questão
 *  @param q Uma questão
 *  @return Array com ID das respostas de cada questão
 */
GArray* getIdAnswers_question(QUESTION q);

/**
 *  @brief A função que se segue faz com que seja possível
 *  a alteração/modificação do array que tem o Id das
 *  respostas de cada questão
 *  @param q Uma questão, id das respostas
 */
void setAnswers_array_question(QUESTION q, long id);

#endif // __QUESTION_H__
