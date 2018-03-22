#ifndef __ANSWER_H__
#define __ANSWER_H__

#include <stdlib.h>
#include "date.h"


typedef struct anwser * ANSWER;

ANSWER create_answer(size_t my_id, Date my_creation_date, ssize_t my_score);
void free_answer(ANSWER a);
size_t getID_answer(ANSWER a);
Date getDate_answer(ANSWER a);
ssize_t getScore_answer(ANSWER a);
void setID_answer(ANSWER a, size_t my_id);
void setDate_answer(ANSWER a, Date my_date);
void setScore_answer(ANSWER a, ssize_t my_score);


#endif //__ANSWER_H__