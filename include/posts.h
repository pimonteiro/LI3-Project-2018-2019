#ifndef __POSTS_H__
#define __POSTS_H__

#include <stdlib.h>
#include "answer.h"
#include "date.h"
#include <glib.h>
typedef struct post * POST;


POST create_post(size_t my_id, char * my_title, size_t my_owner_id, GArray my_awnsers, Date my_start, Date my_end, size_t my_n_answer);
void free_post(void* p);
size_t getId_question(POST p);
char* getTitle(POST p);
size_t getOwner_id_question(POST p);
Date getStart_date(POST p);
Date getEnd_date(POST p);
size_t getN_answer(POST p);
GArray getAnswers_array(POST p);
void setId_question(POST p, size_t my_id_question);
void setTitle(POST p, char * my_title_question);
void setOwner_id_question(POST p, size_t my_owner_id);
void setStart_date(POST p, Date new_start);
void setEnd_date(POST p, Date new_end);
void setN_answer(POST p, size_t my_n_answer);
void setAnswers_array(POST p, GArray new_awnsers);

GArray add_awnser_array(POST p, ANSWER a);

#endif //__POSTS_H__
