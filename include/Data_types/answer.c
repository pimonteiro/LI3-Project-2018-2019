#include "awnser.h"

struct answer {
    size_t id;   //guardamos o id do pai? compensa?
    Date creationDate;
    ssize_t score;
    // TODO TAGS?
}; // TODO

ANSWER create_answer(size_t my_id, DATE my_creation_date, ssize_t my_score){
	ANSWER a = malloc(sizeof(struct answer));
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

DATE getDate_answer(ANSWER a){
	return a->creationDate;
}

ssize_t getScore_answer(ANSWER a){
	return a->score;
}

void setID_answer(ANSWER a, size_t my_id){
	a->id = my_id;
}

void setDate_answer(ANSWER a, DATE my_date){
	a->creationDate = my_date;
}

void setScore_answer(ANSWER a, ssize_t my_score){
	a->score = my_score;
}
