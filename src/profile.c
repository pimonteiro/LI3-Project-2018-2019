#include "profile.h"
#include <stdlib.h>
#include <glib.h>
#include "post.h"
#include "question.h"
#include "mydate.h"

struct profile{
    GSequence* posts;

    char* about_me;
    char* name;

    long n_posts;
    long id;
    int reputation;
};

PROFILE create_profile(char* my_about, long my_id, char* my_name, int my_reputation){
    PROFILE p = malloc(sizeof(struct profile));

    p->n_posts = 0;
    p->about_me = NULL;
    p->about_me = g_strdup(my_about);
    p->id = my_id;
    p->name = g_strdup(my_name);
    p->reputation = my_reputation;
    p->posts = g_sequence_new(NULL);

    return p;
}

void free_profile(void* p){
    PROFILE tmp = (PROFILE) p;

    g_sequence_free(tmp->posts);
    g_free(tmp->about_me);
    g_free(tmp->name);

    free(tmp);
}

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

static gint cmpPosts(gconstpointer a, gconstpointer b, gpointer cmp_data){
    (void)cmp_data;
    POST pa = (POST) a;
    POST pb = (POST) b;

    MyDate da = getDate_post(pa);
    MyDate db = getDate_post(pb);

    //Ordem decrescente de nº de respostas
    return (gint) compare_dates(db, da);
}

void insertLastest_profile(PROFILE p, POST post){
    // g_sequence_prepend(p->posts, (gpointer)post);
    g_sequence_insert_sorted(p->posts, (gpointer) post, cmpPosts, NULL);
    ++(p->n_posts);
}
