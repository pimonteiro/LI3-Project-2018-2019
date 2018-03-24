#include "answer.h"
#include <stdlib.h>
#include <sys/types.h>
struct answer {
    size_t id;
    size_t parent_id; //guardamos o id do pai? compensa?
    Date creationDate;
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

void free_answer(ANSWER a){
	free(a);
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
