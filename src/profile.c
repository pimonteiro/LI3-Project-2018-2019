#include "profile.h"
#include <stdlib.h>
#include <glib.h>
#include "post.h"
#include "question.h"
#include "answer.h"
#include "mydate.h"
#include <string.h>
#include "heap.h"

struct profile {
    HEAP ten_posts;
    GArray* id_answers;

    size_t n_questions;
    size_t n_answer;
    size_t id;
    ssize_t reputation;

    char* about_me;
    char* name;

 };

int cmpDates (void* a, void* b){
    int result;
    POST p1 = (POST)a;
    POST p2 = (POST)b;

    size_t type1 = getType_post(p1);
    size_t type2 = getType_post(p2);
    MyDate d1=NULL;
    MyDate d2=NULL;

    if(type1 == 1){
        d1 = getStart_date_question(getQuestion_post(p1));
    }
    else{
        d1 = getDate_answer(getAnswer_post(p1));
    }
    if(type2 == 1){
        d2 = getStart_date_question(getQuestion_post(p2));
    }
    else{
        d2 = getDate_answer(getAnswer_post(p2));
    }

    result = compare_dates(d1, d2);

    return result;
}
PROFILE create_profile(char * my_about, size_t my_id, char * my_name, ssize_t my_reputation){
    PROFILE p = malloc(sizeof(struct profile));
    p->n_questions = 0;
    p->n_answer = 0;
    p->about_me = g_strdup(my_about);
    p->id = my_id;
    p->name = g_strdup(my_name);
    p->reputation = my_reputation;
    p->ten_posts = initHeap(10, cmpDates);
    p->id_answers = g_array_new(FALSE, FALSE, sizeof(size_t));

    return p;
}

void free_profile(void* d){
    PROFILE tmp = (PROFILE)d;
    g_array_free(tmp->id_answers, TRUE);
    free(tmp->name);
    free(tmp->about_me);
    free_heap(tmp->ten_posts);
    free(tmp);
}

char* getAboutMe_profile(PROFILE d){
    return d->about_me?g_strdup(d->about_me):NULL;
}

size_t getId_profile(PROFILE d){
    return d->id;
}

char* getName_profile(PROFILE d){
    return d->name?g_strdup(d->name):NULL;
}

ssize_t getReputation_profile(PROFILE d){
    return d->reputation;
}

GArray* getId_answers_array_profile(PROFILE d){
    GArray* novo = g_array_new(FALSE, FALSE, sizeof(size_t));

    for(int i = 0; i < d->id_answers->len; i++){
        g_array_append_val(novo, g_array_index(d->id_answers, size_t, i));
    }

    return novo;

}

void setAboutMe_profile(PROFILE d, char * my_about){
  free(d->about_me);
    d->about_me = g_strdup(my_about);
}

void setId_profile(PROFILE d, size_t my_id){
    d->id = my_id;
}

void setName_profile(PROFILE d, char * my_name){
  free(d->name);
    d->name = g_strdup(my_name);
}

void setReputation_profile(PROFILE d, ssize_t my_reputation){
    d->reputation = my_reputation;
}

void setId_answers_array_profile(PROFILE d, GArray* my_id_answers){
    //devo limpar o garray primeiro?
  free(d->id_answers);//sim, mas já esta feito , MEIRAS :D
    d->id_answers = g_array_new(FALSE, FALSE, sizeof(size_t));

    for(int i = 0; i < my_id_answers->len; i++){
        g_array_append_val(d->id_answers, g_array_index(my_id_answers, size_t, i));
    }
}



//FALTA GET E SET DA AVL


/*GTree* getAvl_profile(PROFILE d){
    GTree *a = g_tree_new((GCompareFunc) data_order_avl);

    //


}


void setAvl_profile(PROFILE d, ____){

}


//Seria uma "auxiliar", nao podendo ser acedida por fora: pode se por private?
void createAvl_profile(GTree* a){
    a = g_tree_new((GCompareFunc) data_order_avl);  //funcao a criar
}*/


void profile_add_answers_array(PROFILE d, size_t id){
  if(d->id_answers !=NULL)
         g_array_append_val(d->id_answers, id);
}
