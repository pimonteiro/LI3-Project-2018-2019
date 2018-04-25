#include <stdlib.h>
#include "mydate.h"
#include "answer.h"
/**
 *  @brief
 *  @param
 *  @return
*Estrutura que contém os principais atributos associados às respostas como sendo a sua data
 de criação, o seu id,score.*/
struct answer{
    MyDate creationDate;

    long id;
    long owner_id;
    long parent_id;
    long comments;
    int score;
};

/**
 *  @brief
 *  @param
 *  @return
 */
/*Função responsável pela criação de uma resposta de acordo com os seus atributos */
ANSWER create_answer(long my_parent_id, long my_owner_id, long my_id, MyDate my_creation_date, int my_score, long comments){
    ANSWER a = (ANSWER) malloc(sizeof(struct answer));

    a->id = my_id;
    a->score = my_score;
    a->parent_id = my_parent_id;
    a->creationDate = my_creation_date;
    a->owner_id = my_owner_id;
    a->comments = comments;

    return a;
}

/**
 *  @brief
 *  @param
 *  @return
 */
/*Função que liberta uma resposta da memória */
void free_answer(void* a){
    ANSWER tmp = (ANSWER) a;
    free_Mydate(tmp->creationDate);
    free(tmp);
}

/**
 *  @brief
 *  @param
 *  @return
 */
/*As funções que se seguem são responsáveis pelos getters  dos vários atributos
 das respostas para que seja possível a sua leitura  */
long getParentId_answer(ANSWER a){
    return a->parent_id;
}

/**
 *  @brief
 *  @param
 *  @return
 */
long getID_answer(ANSWER a){
    return a->id;
}

/**
 *  @brief
 *  @param
 *  @return
 */
long getComments_answer(ANSWER a){
    return a->comments;
}

/**
 *  @brief
 *  @param
 *  @return
 */
MyDate getDate_answer(ANSWER a){
    if(a != NULL)
        return a->creationDate;
    else return NULL;
}

/**
 *  @brief
 *  @param
 *  @return
 */
int getScore_answer(ANSWER a){
    return a->score;
}

/**
 *  @brief
 *  @param
 *  @return
 */
long getOwnerId_answer(ANSWER a){
    return a->owner_id;
}
