#include "profile.h"
#include <stdlib.h>
#include <glib.h>
#include "post.h"
#include "question.h"
#include "answer.h"
#include "mydate.h"
#include "heap.h"
#include <stdlib.h>

#define TOPTEN(i) (i < 11 ?  i++ : i )

struct profile {
    GSequence* posts;

    char* about_me;
    char* name;

    long inserts;
    long n_posts;
    long id;
    int reputation;
 };
 static int cmpDates (const void* a, const void* b){
    int result;

    const POST* p1 = (POST*)a;
    const POST* p2 = (POST*)b;

    const MyDate d1= getDate_post(*p1);
    const MyDate d2= getDate_post(*p2);

    if(d1 == NULL) return -1;
    if(d2 == NULL) return 1;

    result = compare_dates(d2, d1);

    return result;
}

PROFILE create_profile(char * my_about, long my_id, char * my_name, int my_reputation){
    PROFILE p= malloc(sizeof(struct profile));

    p->inserts=0;
    p->n_posts= 0;
    p->about_me = g_strdup(my_about);
    p->id = my_id;
    p->name = g_strdup(my_name);
    p->reputation = my_reputation;
    p->posts = g_sequence_new(NULL);

    return p;
}

void free_profile(void* p){
    PROFILE tmp = (PROFILE)p;

    g_sequence_free(tmp->posts);
    g_free(tmp->name);
    g_free(tmp->about_me);

    free(tmp);
}

/**
 * Getters
 */

GSequence* getPosts_profile(PROFILE p){
    return p->posts;
}

char* getAboutMe_profile(PROFILE p){
    return p->about_me ? g_strdup(p->about_me) : NULL;
}

char* getName_profile(PROFILE p){
    return p->name ? g_strdup(p->name) : NULL;
}

long getNposts_profile(PROFILE p){
    return p->n_posts;
}

long getId_profile(PROFILE p){
    return p->id;
}

int getReputation_profile(PROFILE p){
    return p->reputation;
}


/**
 * Setters
 */

void setAboutMe_profile(PROFILE p, char* my_about){
    if(my_about != NULL){
        p->about_me ? (free(p->about_me), p->about_me = g_strdup(my_about)) : (p->about_me = g_strdup(my_about));
    }
}

void setId_profile(PROFILE p, long my_id){
    p->id = my_id;
}

void setName_profile(PROFILE p, char* my_name){
     if(my_name != NULL){
        p->name ? (free(p->name), p->name = g_strdup(my_name)) : (p->name = g_strdup(my_name));
    }
}

void setReputation_profile(PROFILE p, int my_reputation){
    p->reputation = my_reputation;
}


/**
 * Aux functions
 */



void insertLastest_profile(PROFILE p, POST post){
    g_sequence_prepend(p->posts, (gpointer)post);
     ++(p->n_posts);
}
