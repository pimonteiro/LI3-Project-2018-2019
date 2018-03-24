#include "posts.h"
#include "answer.h"
#include <stdlib.h>
#include "date.h"
#include "glib.h"
struct post {
    size_t id_question;
    char* title_question;
    char* tags; 
    size_t owner_id;


    GArray answers; //Array de Answers
    Date start; //Obviamente pertence a pergunta
    Date end;
    size_t n_answer;
};

POST create_post(size_t my_id, char * my_title, size_t my_owner_id, GArray my_awnsers, Date my_start, Date my_end, size_t my_n_answer){
	POST p = malloc(sizeof(struct post));
	p->id_question = my_id;
	p->title_question = strdup(my_title);
	p->owner_id_question = my_owner_id;
	p->start = my_start;
	p->end   = my_end;
	p->n_answer = my_n_answer;

	//Falta inicilizar o array
}

void free_post(void* p){
	POST tmp = (POST)p;
	free(tmp);
}

size_t getId_question(POST p){
	return p->id_question;
}

char* getTitle(POST p){
	return p->title_question;
}

size_t getOwner_id_question(POST p){
	return p->owner_id_question;
}

Date getStart_date(POST p){
	return p->start;
}

Date getEnd_date(POST p){
	return p->end;
}

size_t getN_answer(POST p){
	return p->n_answer;
}

GArray getAnswers_array(POST p){
	//....
}


void setId_question(POST p, size_t my_id_question){
	p->id_question = my_id_question;
}

void setTitle(POST p, char * my_title_question){
	p->title_question = my_title_question;
}

void setOwner_id_question(POST p, size_t my_owner_id){
	p->owner_id_question = my_owner_id;
}

void setStart_date(POST p, Date new_start){
	p->start = new_start;
}

void setEnd_date(POST p, Date new_end){
	p->end = new_end;
}

void setN_answer(POST p, size_t my_n_answer){
	p->n_answer = my_n_answer;
}

void setAnswers_array(POST p, GArray new_awnsers){
	//....
}


GArray add_awnser_array(POST p, ANSWER a){
	 g_array_append_val(&(p->answers), a);

}
