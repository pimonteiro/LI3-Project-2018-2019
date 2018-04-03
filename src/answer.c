#include "mydate.h"
#include "answer.h"
#include <stdlib.h>
#include <sys/types.h>
struct answer {
    MyDate creationDate;

    long id;
    long owner_id;
    long parent_id;
    int score;

};

ANSWER create_answer(long my_parent_id, long my_owner_id, long my_id, MyDate my_creation_date, int my_score){
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

long getParentId_answer(ANSWER a){
    return a->parent_id;
}

long getID_answer(ANSWER a){
    return a->id;
}

MyDate getDate_answer(ANSWER a){
    if(a!=NULL)
    return a->creationDate;
    else return NULL;
}

int getScore_answer(ANSWER a){
    return a->score;
}

long getOwnerId_answer(ANSWER a){
    return a->owner_id;
}

void setID_answer(ANSWER a, long my_id){
    a->id = my_id;
}

void setDate_answer(ANSWER a, MyDate my_date){
    if(a->creationDate != NULL) free(a->creationDate);
    my_date ? a->creationDate = my_date : NULL;
}

void setScore_answer(ANSWER a, int my_score){
    a->score = my_score;
}

void setParent_id_answer(ANSWER a, long my_parent_id){
    a->parent_id = my_parent_id;
}

void setOwner_id_answer(ANSWER a, long my_owner_id){
    a->parent_id = my_owner_id;
}
