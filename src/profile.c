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

	size_t n_questions;
    size_t n_answer;
    size_t id;
    ssize_t reputation;

    char* about_me;
    char* name;
    		
 };

PROFILE create_profile(char * my_about, size_t my_id, char * my_name, ssize_t my_reputation, size_t my_n_questions, size_t my_n_answer){
	PROFILE p = malloc(sizeof(struct profile));
	p->n_questions = my_n_questions;
	p->n_answer = my_n_answer;
	p->about_me = g_strdup(my_about);
	p->id = my_id;
	p->name = g_strdup(my_name);
	p->reputation = my_reputation;
	
	//createAvl_profile(p->avl_users); 
	return p;
}

void free_profile(void* d){
	PROFILE tmp = (PROFILE)d;
	//free_avl(tmp->avl_users); //TODO
	free(tmp);
}

char* getAboutMe_profile(PROFILE d){
	return d->about_me;
}

size_t getId_profile(PROFILE d){
	return d->id;
}

char* getName_profile(PROFILE d){
	return d->name;
}

ssize_t getReputation_profile(PROFILE d){
	return d->reputation;
}

void setAboutMe_profile(PROFILE d, char * my_about){
	d->about_me = g_strdup(my_about);
}

void setId_profile(PROFILE d, size_t my_id){
	d->id = my_id;
}

void setName_profile(PROFILE d, char * my_name){
	d->name = g_strdup(my_name);
}

void setReputation_profile(PROFILE d, ssize_t my_reputation){
	d->reputation = my_reputation;
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