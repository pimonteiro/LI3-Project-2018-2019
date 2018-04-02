#ifndef __ANSWER_H__
#define __ANSWER_H__

#include "mydate.h"
#include <sys/types.h>

typedef struct answer * ANSWER;

ANSWER create_answer(size_t my_parent_id, size_t my_owner_id, size_t my_id, MyDate my_creation_date, ssize_t my_score);
void free_answer(void* a);

size_t getID_answer(ANSWER a);
MyDate getDate_answer(ANSWER a);
ssize_t getScore_answer(ANSWER a);
size_t getParentId_answer(ANSWER a);
size_t getOwnerId_answer(ANSWER a);

void setID_answer(ANSWER a, size_t my_id);
void setDate_answer(ANSWER a, MyDate my_date);
void setScore_answer(ANSWER a, ssize_t my_score);
void setParentId_answer(ANSWER a, size_t my_parent_id);
void setOwnerId_answer(ANSWER a, size_t my_owner_id);

#endif //__ANSWER_H__
