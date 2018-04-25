#include "question.h"
#include <stdlib.h>
#include "mydate.h"
#include "glib.h"
#include <string.h>

/**
 *  @brief
 *  @param
 *  @return
 */
/*Estrutura que contém os principais atributos associados às perguntas:apontador para a estrutura Data,
 id das respostas,titulo das questões,tags,id das questões,número de respostas,score.*/
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
 *  @brief
 *  @param
 *  @return
 */
/*Função responsável pela criação de uma pergunta de acordo com os seus atributos */
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
 *  @brief
 *  @param
 *  @return
 */
/*Função que liberta uma pergunta da memória */
void free_question(void* q){
    QUESTION tmp = (QUESTION) q;

    tmp->id_answers ? g_array_free(tmp->id_answers, TRUE) : NULL;
    tmp->creation_date ? free_Mydate(tmp->creation_date) : NULL;
    tmp->title_question ? free(tmp->title_question) : NULL;
    tmp->tags ? free(tmp->tags) : NULL;

    free(tmp);
}

/**
 *  @brief
 *  @param
 *  @return
 */


/*As funções que se seguem são responsáveis pelos getters  dos vários atributos
das questoes para que seja possível a sua leitura  */

long getId_question(QUESTION q){
    return q->id_question;
}

/**
 *  @brief
 *  @param
 *  @return
 */
char* getTitle_question(QUESTION q){
    return q->title_question ? g_strdup(q->title_question) : NULL;
}

/**
 *  @brief
 *  @param
 *  @return
 */
long getOwnerId_question(QUESTION q){
    return q->owner_id_question;
}

/**
 *  @brief
 *  @param
 *  @return
 */
MyDate getCreationDate_question(QUESTION q){
    if(q != NULL)
        return q->creation_date ? (q->creation_date) : NULL;
    else return NULL;
}

/**
 *  @brief
 *  @param
 *  @return
 */
long getComments_question(QUESTION q){
    return q->comments;
}

/**
 *  @brief
 *  @param
 *  @return
 */
long getNanswers_question(QUESTION q){
    return q->n_answers;
}

/**
 *  @brief
 *  @param
 *  @return
 */
int getScore_question(QUESTION q){
    return q->score;
}

/**
 *  @brief
 *  @param
 *  @return
 */
char* getTags_question(QUESTION q){
    return q->tags ? g_strdup(q->tags) : NULL;
}

/**
 *  @brief
 *  @param
 *  @return
 */
GArray* getIdAnswers_question(QUESTION q){
    return q->id_answers ? q->id_answers : NULL;
}

/**
 *  @brief
 *  @param
 *  @return
 */
void setAnswers_array_question(QUESTION q, long id){
    q->id_answers ? g_array_append_val(q->id_answers, id) : NULL;
}
