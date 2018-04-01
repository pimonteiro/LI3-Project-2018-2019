#ifndef __POST_H__
#define __POST_H__

#include "answer.h"
#include "question.h"
#include <sys/types.h>

typedef struct post * POST;

POST create_post(size_t type, QUESTION q, ANSWER a);
void free_post(void* p);
size_t getType_post(POST p);
void setType_post(POST p, size_t type);
QUESTION getQuestion_post(POST p);
ANSWER getAnswer_post(POST p);
#endif
