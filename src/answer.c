#include "answer.h"
#include <stdlib.h>
#include <sys/types.h>
struct answer {
	Date creationDate;

	size_t owner_id;
    size_t id;
    size_t parent_id;
    ssize_t score;

    // TODO TAGS?
}; // TODO

ANSWER create_answer(size_t my_parent_id, size_t my_owner_id, size_t my_id, Date my_creation_date, ssize_t my_score){
	ANSWER a = (ANSWER)malloc(sizeof(struct answer));
	a->id = my_id;
	a->score = my_score;
  a->parent_id = my_parent_id;
	a->creationDate = my_creation_date;
	a->owner_id = my_owner_id;

	return a;
}

ANSWER create_answer_copy(ANSWER a){
	ANSWER ret = (ANSWER) malloc(sizeof(struct answer));
	ret = a;

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

	return a->creationDate?a->creationDate:NULL;
}

ssize_t getScore_answer(ANSWER a){
	return a->score;
}

size_t getOwner_id_answer(ANSWER a){
	return a->id;
}

void setID_answer(ANSWER a, size_t my_id){
	a->id = my_id;
}

void setDate_answer(ANSWER a, Date my_date){
  if(a->creationDate != NULL) free(a->creationDate);
	a->creationDate = my_date;
}

void setScore_answer(ANSWER a, ssize_t my_score){
	a->score = my_score;
}

void setParent_id_answer(ANSWER a, size_t my_parent_id){
	a->parent_id = my_parent_id;
}

void setOwner_id_answer(ANSWER a, size_t my_owner_id){
	a->parent_id = my_owner_id;
}

