#ifndef __ANSWER_H__
#define __ANSWER_H__

#include "mydate.h"
#include <sys/types.h>

typedef struct answer * ANSWER;

ANSWER create_answer(long my_parent_id, long my_owner_id, long my_id, MyDate my_creation_date, int my_score);
void free_answer(void* a);

long getID_answer(ANSWER a);
MyDate getDate_answer(ANSWER a);
int getScore_answer(ANSWER a);
long getParentId_answer(ANSWER a);
long getOwnerId_answer(ANSWER a);

void setID_answer(ANSWER a, long my_id);
void setDate_answer(ANSWER a, MyDate my_date);
void setScore_answer(ANSWER a, int my_score);
void setParentId_answer(ANSWER a, long my_parent_id);
void setOwnerId_answer(ANSWER a, long my_owner_id);

#endif //__ANSWER_H__
