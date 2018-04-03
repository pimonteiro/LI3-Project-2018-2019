#ifndef __QUESTION_H__
#define __QUESTION_H__

#include <stdlib.h>
#include "answer.h"
#include "mydate.h"
#include <glib.h>
#include <string.h>

typedef struct question * QUESTION;



QUESTION create_question(long my_id, char * my_title, char* my_tags, long my_owner_id,  MyDate my_creation_date, int my_score, long my_n_answer);
void free_question(void* q);

long getId_question(QUESTION q);
char* getTitle_question(QUESTION q);
long getOwnerId_question(QUESTION q);
MyDate getCreationDate_question(QUESTION q);
long getNanswers_question(QUESTION q);
int getScore_question(QUESTION q);
char* getTags_question(QUESTION q);
GArray* getIdAnswers_question(QUESTION q);

void setId_question(QUESTION q, long my_id_question);
void setTitle_question(QUESTION q, char* my_title_question);
void setOwnerId_question(QUESTION q, long my_owner_id);
void setDate_question(QUESTION q, MyDate new_creation_date);
void setAnswers_array_question(QUESTION q, long id);
void setScore_question(QUESTION q, int my_score);
void setTags_question(QUESTION q, char* my_tags);

#endif // __QUESTION_H__
