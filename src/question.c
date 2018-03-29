#include "question.h"
#include "answer.h"
#include <stdlib.h>
#include "date.h"
#include "glib.h"
#include <string.h>

struct question {
    Date start; //Obviamente pertence a pergunta
    Date end;

    GArray* id_answers; //Array dos id de Answers
    GArray* tags_question;

    size_t id_question;
    size_t owner_id_question;
    size_t n_answer;
    ssize_t score;

    char* title_question;
    char* tags;

};

QUESTION create_question(size_t my_id, char * my_title, char* my_tags, size_t my_owner_id,  Date my_start, ssize_t my_score){
    QUESTION p = malloc(sizeof(struct question));
    p->id_question = my_id;
    p->title_question = g_strdup(my_title);
    p->tags = g_strdup(my_tags);
    p->owner_id_question = my_owner_id;
    p->start = my_start;
    p->end   = createDate(0, 0, 0); // HERULUME
    p->n_answer = 0;
    p->score = my_score;

    p->id_answers = g_array_new(FALSE, FALSE, sizeof(size_t));

    /*for(int i = 0; i < my_answers->len; i++){
        g_array_append_val(p->id_answers, g_array_index(my_answers, size_t, i));
    }   */

    return p;
}


QUESTION create_question_copy(QUESTION q){
    QUESTION ret = malloc(sizeof(struct question));
    ret->start = getStart_date_question(q);
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

}
void free_question(void* p){
    QUESTION tmp = (QUESTION)p;
    g_array_free(tmp->id_answers, TRUE);
    free(tmp->start);
    free(tmp->end);
  free(tmp->title_question);
  free(tmp->tags);
    free(tmp);
}

size_t getId_question(QUESTION p){
    return p->id_question;
}

char* getTitle_question(QUESTION p){
    return p->title_question?g_strdup(p->title_question):NULL;
}

size_t getOwner_id_question(QUESTION p){
    return p->owner_id_question;
}

Date getStart_date_question(QUESTION p){
    return p->start?(p->start):NULL;
}

Date getEnd_date_question(QUESTION p){
    return p->end?(p->end):NULL;
}

size_t getN_answer_question(QUESTION p){
    return p->n_answer;
}

GArray* getAnswers_array_question(QUESTION p){
    GArray* novo = g_array_new(FALSE, FALSE, sizeof(size_t));

    for(int i = 0; i < p->id_answers->len; i++){
        g_array_append_val(novo, g_array_index(p->id_answers, size_t, i));
    }

    return novo;

}

ssize_t getScore_question(QUESTION p){
    return p->score;
}

void setId_question(QUESTION p, size_t my_id_question){
    p->id_question = my_id_question;
}

void setTitle_question(QUESTION p, char * my_title_question){
    p->title_question = my_title_question;
}

void setOwner_id_question(QUESTION p, size_t my_owner_id){
    p->owner_id_question = my_owner_id;
}

void setStart_date_question(QUESTION p, Date new_start){
    p->start = new_start;
}

void setEnd_date_question(QUESTION p, Date new_end){
    p->end = new_end;
}

void setN_answer_question(QUESTION p, size_t my_n_answer){
    p->n_answer = my_n_answer;
}

void setAnswers_array_question(QUESTION p, GArray* my_answers){
    //devo limpar o garray primeiro?
  free(p->id_answers);
    p->id_answers = g_array_new(FALSE, FALSE, sizeof(size_t));

    for(int i = 0; i < my_answers->len; i++){
        g_array_append_val(p->id_answers, g_array_index(my_answers, size_t, i));
    }
}

void setScore_question(QUESTION p, ssize_t my_score){
    p->score = my_score;
}

void add_answers_array(QUESTION p, size_t id){
    g_array_append_val(p->id_answers, id);
}


size_t get_element_index_answers(QUESTION p, int i){
    return g_array_index(p->id_answers, size_t, i);
}
