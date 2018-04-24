#ifndef __POST_H__
#define __POST_H__

#include "answer.h"
#include "question.h"
#include "mydate.h"

typedef struct post* POST;

POST create_post(long type, QUESTION q, ANSWER a);

void free_post(void* p);

long getType_post(POST p);

QUESTION getQuestion_post(POST p);

ANSWER getAnswer_post(POST p);

MyDate getDate_post(POST p);

#endif