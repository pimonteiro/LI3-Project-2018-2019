#include "question.h"
#include <stdlib.h>
#include "mydate.h"
#include "glib.h"
#include <string.h>

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

/*Função que liberta uma pergunta da memória */
void free_question(void* q){
    QUESTION tmp = (QUESTION) q;

    tmp->id_answers ? g_array_free(tmp->id_answers, TRUE) : NULL;
    tmp->creation_date ? free_Mydate(tmp->creation_date) : NULL;
    tmp->title_question ? free(tmp->title_question) : NULL;
    tmp->tags ? free(tmp->tags) : NULL;

    free(tmp);
}



/*As funções que se seguem são responsáveis pelos getters  dos vários atributos
das questoes para que seja possível a sua leitura  */

long getId_question(QUESTION q){
    return q->id_question;
}

char* getTitle_question(QUESTION q){
    return q->title_question ? g_strdup(q->title_question) : NULL;
}

long getOwnerId_question(QUESTION q){
    return q->owner_id_question;
}

MyDate getCreationDate_question(QUESTION q){
    if(q != NULL)
        return q->creation_date ? (q->creation_date) : NULL;
    else return NULL;
}

long getComments_question(QUESTION q){
    return q->comments;
}
long getNanswers_question(QUESTION q){
    return q->n_answers;
}

int getScore_question(QUESTION q){
    return q->score;
}

char* getTags_question(QUESTION q){
    return q->tags ? g_strdup(q->tags) : NULL;
}

GArray* getIdAnswers_question(QUESTION q){
    return q->id_answers ? q->id_answers : NULL;
}

void setAnswers_array_question(QUESTION q, long id){
    q->id_answers ? g_array_append_val(q->id_answers, id) : NULL;
}
