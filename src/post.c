#include "post.h"
#include "answer.h"
#include "question.h"
#include "mydate.h"

/**
 *  @brief  Estrutura de um post. Visto dividir-se em Questions e Answers e ambas
 *   partilharem atributos, decidiu-se implmentar uma union, de forma
 *  a conseguir-se juntar os Posts ou separá-los como fosse mais conveniente.
 */
struct post{
    long type; // 1 Question 2 Answer
    union content{
        QUESTION q;
        ANSWER a;
    }content;
};

/**
 *  @brief  Função responsável pela criação de um post de acordo com
 *  as questões e/ou respostas
 *  @param type Tipo 1 para Question e 2 para Answer, q Questão, a Answer
 *  @return criação de um Post
 */

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

/**
 *  @brief  Função que liberta um post da memória
 *  @param p Um Post
 */
void free_post(void* p){
    POST post = (POST) p;
    if(getType_post(post) == 1)
        free_question(post->content.q);
    else
        free_answer(post->content.a);

    free(post);
}

/**
 *  @brief  Função responsável por ver o tipo
 *  de um dado Post,ou seja, se é Questão ou Resposta
 *  @param p Um post
 *  @return Tipo de um Post
 */
long getType_post(POST p){
    return p->type;
}

/**
 *  @brief  Função responsável pela leitura
 *  do conteúdo do tipo Questão
 *  @param p Um Post
 *  @return Conteúdo de uma questão de um Post
 */

QUESTION getQuestion_post(POST p){
    return p->content.q;
}

/**
 *  @brief  Função responsável pela leitura
 *  do conteúdo do tipo Resposta
 *  @param p Um Post
 *  @return Conteúdo de uma resposta de um Post
 */
ANSWER getAnswer_post(POST p){
    return p->content.a;
}

/**
 *  @brief  Funão responsável pela leitura
 *  da Data de um determinado Post
 *  @param p Um Post
 *  @return Data de um Post
 */
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
