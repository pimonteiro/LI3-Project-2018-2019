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

    size_t id_question;
    size_t owner_id_question;
    int n_answer;

    char* title_question;
    char* tags; 

};

QUESTION create_question(size_t my_id, char * my_title, size_t my_owner_id, Date my_start, Date my_end, int my_n_answer, GArray* my_answers){
	QUESTION p = malloc(sizeof(struct question));
	p->id_question = my_id;
	p->title_question = g_strdup(my_title);
	p->owner_id_question = my_owner_id;
	p->start = my_start;
	p->end   = my_end;
	p->n_answer = my_n_answer;

	p->id_answers = g_array_new(FALSE, FALSE, sizeof(size_t));
	
	for(int i = 0; i < my_answers->len; i++){
		g_array_append_val(p->id_answers, g_array_index(my_answers, size_t, i));
	}	

	return p;
}

void free_question(void* p){
	QUESTION tmp = (QUESTION)p;
	g_array_free(tmp->id_answers, TRUE);
	free(tmp->start);
	free(tmp->end);
	free(tmp);
}

size_t getId_question(QUESTION p){
	return p->id_question;
}

char* getTitle(QUESTION p){
	return p->title_question;
}

size_t getOwner_id_question(QUESTION p){
	return p->owner_id_question;
}

Date getStart_date(QUESTION p){
	return p->start;
}

Date getEnd_date(QUESTION p){
	return p->end;
}

int getN_answer(QUESTION p){
	return p->n_answer;
}

GArray* getAnswers_array(QUESTION p){
	GArray* novo = g_array_new(FALSE, FALSE, sizeof(size_t));

	for(int i = 0; i < p->id_answers->len; i++){
		g_array_append_val(novo, g_array_index(p->id_answers, size_t, i));
	}	

	return novo;

}


void setId_question(QUESTION p, size_t my_id_question){
	p->id_question = my_id_question;
}

void setTitle(QUESTION p, char * my_title_question){
	p->title_question = my_title_question;
}

void setOwner_id_question(QUESTION p, size_t my_owner_id){
	p->owner_id_question = my_owner_id;
}

void setStart_date(QUESTION p, Date new_start){
	p->start = new_start;
}

void setEnd_date(QUESTION p, Date new_end){
	p->end = new_end;
}

void setN_answer(QUESTION p, int my_n_answer){
	p->n_answer = my_n_answer;
}

void setAnswers_array(QUESTION p, GArray* my_answers){
	//devo limpar o garray primeiro?
	p->id_answers = g_array_new(FALSE, FALSE, sizeof(ANSWER));
	
	for(int i = 0; i < my_answers->len; i++){
		g_array_append_val(p->id_answers, g_array_index(my_answers, size_t, i));
	}	
}


void add_answers_array(QUESTION p, size_t id){
	g_array_append_val(p->id_answers, id);
}


size_t get_element_index_answers(QUESTION p, int i){
	return g_array_index(p->id_answers, size_t, i);
}