#include "profile.h"
#include <stdlib.h>
#include <glib.h>

struct avl_posts_users{
	int type;
	size_t id;
};


struct profile {
    char* about_me;
    size_t id;
    char* name;
    long int reputation;

    size_t n_questons;
    size_t n_awnsers;

	struct avl_posts_users* avl_posts; //Verificar
 };

PROFILE create_profile(char * my_about, size_t my_id, char * my_name, long int my_reputation, GArray my_avl_posts){
	PROFILE p = malloc(sizeof(struct profile));
	p->about_me = strdup(my_about);
	p->id = my_id;
	p->name = strdup(my_name);
	p->reputation = my_reputation;
	//p->avl_posts = my_avl_posts; //TA MAL, ERA SO PRA ESTAR PARA AVANÇAR

	return p;
}

void free_profile(void* d){
	PROFILE tmp = (PROFILE)d;
	free(tmp);
}

char getAboutMe_profile(PROFILE d){
	return d->about_me;
}

size_t getId_profile(PROFILE d){
	return d->id;
}

char getName_profile(PROFILE d){
	return d->name;
}

long int getReputation_profile(PROFILE d){
	return d->reputation;
}

void setAboutMe_profile(PROFILE d, char * my_about){
	d->about_me = strdup(my_about);
}

void setId_profile(PROFILE d, size_t my_id){
	d->id = my_id;
}

void setName_profile(PROFILE d, char * my_name){
	d->name = strdup(my_name);
}

void setReputation_profile(PROFILE d, long int my_reputation){
	d->reputation = my_reputation;
}

//FALTA GET E SET DA AVL
