#ifndef __QUESTION_H__
#define __QUESTION_H__

#include <stdlib.h>
#include "answer.h"
#include "date.h"
#include <glib.h>
#include <string.h>

typedef struct question * QUESTION;


QUESTION create_question(size_t my_id, char * my_title, char* my_tags, size_t my_owner_id, Date my_start,ssize_t my_score);
QUESTION create_question_copy(QUESTION q);
void free_question(void* p);
size_t getId_question(QUESTION p);
char* getTitle_question(QUESTION p);
size_t getOwner_id_question(QUESTION p);
Date getStart_date_question(QUESTION p);
Date getEnd_date_question(QUESTION p);
size_t getN_answer_question(QUESTION p);
GArray* getAnswers_array_question(QUESTION p);
ssize_t getScore_question(QUESTION p);
void setId_question(QUESTION p, size_t my_id_question);
void setTitle_question(QUESTION p, char * my_title_question);
void setOwner_id_question(QUESTION p, size_t my_owner_id);
void setStart_date_question(QUESTION p, Date new_start);
void setEnd_date_question(QUESTION p, Date new_end);
void setN_answer_question(QUESTION p, size_t my_n_answer);
void setAnswers_array_question(QUESTION p, size_t id);
void setScore_question(QUESTION p, ssize_t my_score);

void add_answers_array(QUESTION p, size_t id);
size_t get_element_index_answers(QUESTION p, int i);
#endif // __QUESTION_H__
