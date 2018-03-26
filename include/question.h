#ifndef __QUESTION_H__
#define __QUESTION_H__
 
#include <stdlib.h>
#include "answer.h"
#include "date.h"
#include <glib.h>
#include <string.h>

typedef struct question * QUESTION;


QUESTION create_question(size_t my_id, char * my_title, size_t my_owner_id, Date my_start, Date my_end, int my_n_answer, GArray* my_awnsers);
void free_question(void* p);
size_t getId_question(QUESTION p);
char* getTitle(QUESTION p);
size_t getOwner_id_question(QUESTION p);
Date getStart_date(QUESTION p);
Date getEnd_date(QUESTION p);
int getN_answer(QUESTION p);
GArray* getAnswers_array(QUESTION p);
void setId_question(QUESTION p, size_t my_id_question);
void setTitle(QUESTION p, char * my_title_question);
void setOwner_id_question(QUESTION p, size_t my_owner_id);
void setStart_date(QUESTION p, Date new_start);
void setEnd_date(QUESTION p, Date new_end);
void setN_answer(QUESTION p, int my_n_answer);
void setAnswers_array(QUESTION p, GArray* new_awnsers);

void add_answers_array(QUESTION p, size_t id);
size_t get_element_index_answers(QUESTION p, int i);
#endif // __QUESTION_H__
