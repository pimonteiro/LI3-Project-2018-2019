#include "question.h"
#include <stdlib.h>
#include "mydate.h"
#include "glib.h"
#include <string.h>

/**
 *  @brief Estrutura que contém os principais atributos associados às questões
 *  como sendo a data de criação, id das respostas associadas a cada questão
 *  título da questão,tag de cada questão,id da questão,id de quem formulou a
 *  pergunta,número de respostas de cada questão,número de comentários e,por
 *  último,o score de uma pergunta.
 */
struct question{
    MyDate creation_date;

    GArray* id_answers;

    char* title_question;
    char* tags;

    long id_question;
    long owner_id_question;
    long n_answers;
    long comments;
    int score;
};
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
                         long comments){
    QUESTION q = malloc(sizeof(struct question));

    q->id_question = my_id;
    q->title_question = g_strdup(my_title);
    q->tags = g_strdup(my_tags);
    q->owner_id_question = my_owner_id;
    q->creation_date = my_creation_date;
    q->n_answers = my_n_answer;
    q->score = my_score;
    q->id_answers = g_array_new(FALSE, FALSE, sizeof(long));
    q->comments = comments;

    return q;
}

/**
 *  @brief Função que liberta uma questão da memória
 *  @param q Uma questão(question)
 *  @return libertação de uma dada questão
 */

void free_question(void* q){
    QUESTION tmp = (QUESTION) q;

    tmp->id_answers ? g_array_free(tmp->id_answers, TRUE) : NULL;
    tmp->creation_date ? free_Mydate(tmp->creation_date) : NULL;
    tmp->title_question ? free(tmp->title_question) : NULL;
    tmp->tags ? free(tmp->tags) : NULL;

    free(tmp);
}


/**
 *  @brief A função que se segue é responsável pela
 *  leitura do atributo ID da questão
 *  @param q Uma questão
 *  @return ID da questão
 */

long getId_question(QUESTION q){
    return q->id_question;
}

/**
 *  @brief A função que se segue é responsável pela leitura do atributo
 *  titulo da questão
 *  @param q Uma questão
 *  @return titulo da questão
 */

char* getTitle_question(QUESTION q){
    return q->title_question ? g_strdup(q->title_question) : NULL;
}

/**
 *  @brief A função que se segue é responsável pela leitura do atributo
 *  ID de quem formulou a questão
 *  @param q Uma questão
 *  @return ID de quem fez a questão
 */

long getOwnerId_question(QUESTION q){
    return q->owner_id_question;
}

/**
 *  @brief  A função que se segue é responsável pela leitura
 *  da data de criação
 *  @param q Uma questão
 *  @return Data de criação da questão
 */

MyDate getCreationDate_question(QUESTION q){
    if(q != NULL)
        return q->creation_date ? (q->creation_date) : NULL;
    else return NULL;
}

/**
 *  @brief  A função que se segue é responsável pela
 *  leitura do número de comentários
 *  @param q Uma questão
 *  @return Número de comentários
 */

long getComments_question(QUESTION q){
    return q->comments;
}

/**
 *  @brief  A função que se segue é responsável pela
 *  leitura do número de respostas associdas a cada questão
 *  @param q Uma questão
 *  @return Número de respostas
 */

long getNanswers_question(QUESTION q){
    return q->n_answers;
}

/**
 *  @brief A função que se segue é responsável pela leitura do atributo
 *  Score de uma questão
 *  @param q Uma questão
 *  @return Score da questão
 */

int getScore_question(QUESTION q){
    return q->score;
}

/**
 *  @brief A função que se segue é responsável pela leitura do atributo
 *  Tag de cada questão
 *  @param q Uma questão
 *  @return Tag da questão
 */

char* getTags_question(QUESTION q){
    return q->tags ? g_strdup(q->tags) : NULL;
}

/**
 *  @brief  A função que se segue é responsável pela leitura do atributo
 *  Id das respostas associadas a cada questão
 *  @param q Uma questão
 *  @return Array com ID das respostas de cada questão
 */
GArray* getIdAnswers_question(QUESTION q){
    return q->id_answers ? q->id_answers : NULL;
}

/**
 *  @brief A função que se segue faz com que seja possível
 *  a alteração/modificação do array que tem o Id das
 *  respostas de cada questão
 *  @param q Uma questão, id das respostas
 */

void setAnswers_array_question(QUESTION q, long id){
    q->id_answers ? g_array_append_val(q->id_answers, id) : NULL;
}
