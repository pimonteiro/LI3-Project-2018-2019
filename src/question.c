#include "question.h"
#include <stdlib.h>
#include "mydate.h"
#include "glib.h"
#include <string.h>

struct question {
    MyDate creation_date;

    GArray* id_answers;

    char* title_question;
    char* tags;

    size_t id_question;
    size_t owner_id_question;
    size_t n_answers;

    ssize_t score;
};

QUESTION create_question(size_t my_id, char * my_title, char* my_tags, size_t my_owner_id,  MyDate my_creation_date, ssize_t my_score, size_t my_n_answer){
    QUESTION q = malloc(sizeof(struct question));

    q->id_question = my_id;
    q->title_question = g_strdup(my_title);
    q->tags = g_strdup(my_tags);
    q->owner_id_question = my_owner_id;
    q->creation_date = my_creation_date;
    q->n_answers = my_n_answer;
    q->score = my_score;
    q->id_answers = g_array_new(FALSE, FALSE, sizeof(size_t));

    return q;
}

void free_question(void* q){
    QUESTION tmp = (QUESTION)q;
    
    tmp->id_answers ? g_array_free(tmp->id_answers,TRUE) : NULL;
    tmp->creation_date ? free_Mydate(tmp->creation_date) : NULL;
    tmp->title_question ? free(tmp->title_question) : NULL;
    tmp->tags ? free(tmp->tags) : NULL;
    
    free(tmp);
}

/*QUESTION create_question_copy(QUESTION q){
    QUESTION ret = malloc(sizeof(struct question));
    ret->creation_date = getcreation_date_date_question(q);
    ret->end = getEnd_date_question(q);
    ret->id_answers = g_array_new(FALSE, FALSE, sizeof(size_t));

    int n = getN_answer_question(q);
    GArray* tst = getAnswers_array_question(q);

    for(int i = 0; i < n; i++)
        g_array_append_val(ret->id_answers, g_array_index(tst, size_t, i));

    ret->id_question = getId_question(q);
    ret->owner_id_question = getOwner_id_question(q);
    ret->n_answer = getN_answer_question(q);
    ret->title_question = getTitle_question(q);
    ret->score = getScore_question(q);
    ret->tags = "";

    return ret;

}*/

size_t getId_question(QUESTION q){
    return q->id_question;
}

char* getTitle_question(QUESTION q){
    return q->title_question ? g_strdup(q->title_question) : NULL;
}

size_t getOwnerId_question(QUESTION q){
    return q->owner_id_question;
}

MyDate getCreationDate_question(QUESTION q){
    return q->creation_date ? (q->creation_date) : NULL;
}


size_t getNanswers_question(QUESTION q){
    return q->n_answers;
}

ssize_t getScore_question(QUESTION q){
    return q->score;
}

char* getTags_question(QUESTION q){
    return q->tags ? g_strdup(q->tags) : NULL;
}

GArray* getIdAnswers_question(QUESTION q){
    return q->id_answers ? q->id_answers : NULL;
}


void setId_question(QUESTION q, size_t my_id_question){
    q->id_question = my_id_question;
}

void setTitle_question(QUESTION q, char* my_title_question){
    if(q->title_question != NULL){
        my_title_question ? (free(q->title_question), q->title_question = g_strdup(my_title_question)) : NULL;
    }
    q->title_question = g_strdup(my_title_question);
}

void setOwnerId_question(QUESTION q, size_t my_owner_id){
    q->owner_id_question = my_owner_id;
}

void setDate_question(QUESTION q, MyDate new_creation_date){
    q->creation_date = new_creation_date;
}

void setAnswers_array_question(QUESTION q, size_t id){
    q->id_answers ? g_array_append_val(q->id_answers, id) : NULL;
}

void setScore_question(QUESTION q, ssize_t my_score){
    q->score = my_score;
}

void setTags_question(QUESTION q, char* my_tags){
    if(q->tags != NULL)
        my_tags ? (free(q->tags), q->tags = g_strdup(my_tags)) : NULL;
    q->tags = g_strdup(my_tags);
}

/*void add_answers_array(QUESTION q, size_t id){
    g_ptr_array_add(p->id_answers, (gpointer)id);
}*/


/*size_t get_element_index_answers(QUESTION q, int i){
    return g_array_index(p->id_answers, size_t, i);
}*/
