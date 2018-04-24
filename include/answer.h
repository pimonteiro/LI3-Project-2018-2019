#ifndef __ANSWER_H__
#define __ANSWER_H__

#include "mydate.h"


typedef struct answer* ANSWER;

ANSWER create_answer(long my_parent_id, long my_owner_id, long my_id, MyDate my_creation_date, int my_score, long comments);

void free_answer(void* a);

long getID_answer(ANSWER a);

MyDate getDate_answer(ANSWER a);

int getScore_answer(ANSWER a);

long getParentId_answer(ANSWER a);

long getOwnerId_answer(ANSWER a);

long getComments_answer(ANSWER a);

#endif //__ANSWER_H__
