#include "post.h"
#include "answer.h"
#include "question.h"
#include "mydate.h"

struct post{
    long type;
    union content{
        QUESTION q;
        ANSWER a;
    }content;
};

POST create_post(long type, QUESTION q, ANSWER a){
    POST p = malloc(sizeof(struct post));

    if(type == 1){
        p->type = 1;
        p->content.q = q;
    }else{
        p->type = 2;
        p->content.a = a;
    }

    return p;
}

void free_post(void* p){
    POST post = (POST) p;
    if(getType_post(post) == 1)
        free_question(post->content.q);
    else
        free_answer(post->content.a);

    free(post);
}

long getType_post(POST p){
    return p->type;
}

QUESTION getQuestion_post(POST p){
    return p->content.q;
}

ANSWER getAnswer_post(POST p){
    return p->content.a;
}

MyDate getDate_post(POST p){
    if(p != NULL){
        if(p->type == 1){
            return getCreationDate_question(p->content.q);
        }else{
            return getDate_answer(p->content.a);
        }
    }
    return NULL;
}
