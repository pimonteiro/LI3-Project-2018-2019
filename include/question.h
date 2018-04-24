#ifndef __QUESTION_H__
#define __QUESTION_H__

#include <stdlib.h>
#include "mydate.h"
#include <glib.h>

typedef struct question* QUESTION;


QUESTION create_question(long my_id,
                         char* my_title,
                         char* my_tags,
                         long my_owner_id,
                         MyDate my_creation_date,
                         int my_score,
                         long my_n_answer,
                         long comments);

void free_question(void* q);

long getId_question(QUESTION q);

long getComments_question(QUESTION q);

char* getTitle_question(QUESTION q);

long getOwnerId_question(QUESTION q);

MyDate getCreationDate_question(QUESTION q);

long getNanswers_question(QUESTION q);

int getScore_question(QUESTION q);

char* getTags_question(QUESTION q);

GArray* getIdAnswers_question(QUESTION q);

void setAnswers_array_question(QUESTION q, long id);

#endif // __QUESTION_H__
