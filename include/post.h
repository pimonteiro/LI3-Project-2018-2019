#ifndef __POST_H__
#define __POST_H__

#include "answer.h"
#include "question.h"
#include <sys/types.h>

typedef struct post * POST;

POST create_post(size_t type, QUESTION q, ANSWER a);
void free_post(void* p);
size_t getType();
// mais cenas que precisares

#endif
