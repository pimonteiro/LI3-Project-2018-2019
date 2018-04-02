#include "mydate.h"
#include "answer.h"
#include <stdlib.h>
#include <sys/types.h>
struct answer {
    MyDate creationDate;

    size_t id;

    size_t owner_id;
    size_t parent_id;
    ssize_t score;

};

ANSWER create_answer(size_t my_parent_id, size_t my_owner_id, size_t my_id, MyDate my_creation_date, ssize_t my_score){
    ANSWER a = (ANSWER)malloc(sizeof(struct answer));

    a->id = my_id;
    a->score = my_score;
    a->parent_id = my_parent_id;
    a->creationDate = my_creation_date;
    a->owner_id = my_owner_id;

    return a;
}

/*ANSWER create_answer_copy(ANSWER a){
    ANSWER ret = (ANSWER) malloc(sizeof(struct answer));
    ret = a;

    return ret;
}*/

void free_answer(void* a){
    ANSWER tmp = (ANSWER)a;

    free_Mydate(tmp->creationDate);
    free(tmp);
}

size_t getParentId_answer(ANSWER a){
    return a->parent_id;
}

size_t getID_answer(ANSWER a){
    return a->id;
}

MyDate getDate_answer(ANSWER a){
    if(a!=NULL)
    return a->creationDate;
    else return NULL;
}

ssize_t getScore_answer(ANSWER a){
    return a->score;
}

size_t getOwnerId_answer(ANSWER a){
    return a->id;
}

void setID_answer(ANSWER a, size_t my_id){
    a->id = my_id;
}

void setDate_answer(ANSWER a, MyDate my_date){
    if(a->creationDate != NULL) free(a->creationDate);
    my_date ? a->creationDate = my_date : NULL;
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
