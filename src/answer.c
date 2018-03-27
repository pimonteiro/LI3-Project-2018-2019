#include "answer.h"
#include <stdlib.h>
#include <sys/types.h>
struct answer {
	Date creationDate;

    size_t id;
    size_t parent_id;
    ssize_t score;
    
    // TODO TAGS?
}; // TODO

ANSWER create_answer(size_t my_id, Date my_creation_date, ssize_t my_score){
	ANSWER a = (ANSWER)malloc(sizeof(struct answer));
	a->id = my_id;
	a->score = my_score;
	a->creationDate = my_creation_date;

	return a;
}

ANSWER create_answer_copy(ANSWER a){
	ANSWER ret = (ANSWER) malloc(sizeof(struct answer));
	ret->creationDate = getDate_answer(a);
	ret->id = getID_answer(a);
	ret->parent_id = getParent_id_answer(a);
	ret->score = getScore_answer(a);

	return ret;
}

void free_answer(void* a){
	ANSWER tmp = (ANSWER)a;
	free(tmp->creationDate);
	free(tmp);
}

size_t getParent_id_answer(ANSWER a){
	return a->parent_id;
} 

size_t getID_answer(ANSWER a){
	return a->id;
}

Date getDate_answer(ANSWER a){
	return a->creationDate;
}

ssize_t getScore_answer(ANSWER a){
	return a->score;
}

void setID_answer(ANSWER a, size_t my_id){
	a->id = my_id;
}

void setDate_answer(ANSWER a, Date my_date){
	a->creationDate = my_date;
}

void setScore_answer(ANSWER a, ssize_t my_score){
	a->score = my_score;
}

void setParent_id_answer(ANSWER a, size_t my_parent_id){
	a->parent_id = my_parent_id;
}