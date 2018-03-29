#ifndef __ANSWER_H__
#define __ANSWER_H__

#include <stdlib.h>
#include "date.h"

#include <sys/types.h>

typedef struct answer * ANSWER;

ANSWER create_answer(size_t my_parent_id, size_t my_owner_id, size_t my_id, Date my_creation_date, ssize_t my_score);
ANSWER create_answer_copy(ANSWER a);
void free_answer(void* a);
size_t getID_answer(ANSWER a);
Date getDate_answer(ANSWER a);
ssize_t getScore_answer(ANSWER a);
size_t getParent_id_answer(ANSWER a);
size_t getOwner_id_answer(ANSWER a);
void setID_answer(ANSWER a, size_t my_id);
void setDate_answer(ANSWER a, Date my_date);
void setScore_answer(ANSWER a, ssize_t my_score);
void setParent_id_answer(ANSWER a, size_t my_parent_id);
void setOwner_id_answer(ANSWER a, size_t my_owner_id);

#endif //__ANSWER_H__
