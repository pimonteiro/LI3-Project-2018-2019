#include "profile.h"
#include <stdlib.h>
#include <glib.h>
#include <string.h>

struct avl_posts_users{
    int type;
    size_t id;
};


struct profile {
    GTree* avl_users;    //struct avl_posts_users* avl_posts; //Verificar
    GArray* id_answers;

    size_t n_questions;
    size_t n_answer;
    size_t id;
    ssize_t reputation;

    char* about_me;
    char* name;

 };

PROFILE create_profile(char * my_about, size_t my_id, char * my_name, ssize_t my_reputation){
    PROFILE p = malloc(sizeof(struct profile));
    p->n_questions = 0;
    p->n_answer = 0;
    p->about_me = g_strdup(my_about);
    p->id = my_id;
    p->name = g_strdup(my_name);
    p->reputation = my_reputation;

    p->id_answers = g_array_new(FALSE, FALSE, sizeof(size_t));

    /*for(int i = 0; i < my_id_answers->len; i++){
        g_array_append_val(p->id_answers, g_array_index(my_id_answers, size_t, i));
    }*/

    //createAvl_profile(p->avl_users);
    return p;
}

void free_profile(void* d){
    PROFILE tmp = (PROFILE)d;
    //free_avl(tmp->avl_users); //TODO
    g_array_free(tmp->id_answers, TRUE);
  free(tmp->name);
  free(tmp->about_me);
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
