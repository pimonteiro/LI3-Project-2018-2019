#include "post.h"
#include "answer.h"
#include "question.h"

struct post {
  size_t type; // 1 Question 2 Anser
  union content {
    QUESTION q;
    ANSWER a;
  }content;
};

// tens que ver se tipo = 1 ou = 2 para cada metodo e chamas o metodos correspondente
// do quesiton ou answer respectivamente

POST create_post(size_t type, QUESTION q, ANSWER a){
	POST p = malloc(sizeof(struct post));
	if(type == 1){
		p->type = 1;
		p->content.q = create_question_copy(q);	
	} 
	else{
		p->type = 2;
		p->content.a = create_answer_copy(a);
	}
	return p;
}

void free_post(void* p){
	POST q = (POST) p;
	if(getType_post(q) == 1)
		free_question(q->content.q);
	else 
		free_answer(q->content.a);

	free(q);
}


size_t getType_post(POST p){
	return p->type;
}

void setType_post(POST p, size_t type){
	p->type = type;
}