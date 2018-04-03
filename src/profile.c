#include "profile.h"
#include <stdlib.h>
#include <glib.h>
#include "post.h"
#include "question.h"
#include "answer.h"
#include "mydate.h"
#include "heap.h"

struct profile {
    GPtrArray* ten_posts;
    MyDate oldest;
    GArray* id_answers;

    char* about_me;
    char* name;

    size_t inserts;
    size_t n_posts;
    size_t id;
    ssize_t reputation;
 };

static int cmpDates (const void* a, const void* b){
    int result;
    POST p1 = (POST)a;
    POST p2 = (POST)b;

    size_t type1 = getType_post(p1);
    size_t type2 = getType_post(p2);
    MyDate d1=NULL;
    MyDate d2=NULL;

    if(type1 == 1){
        d1 = getCreationDate_question(getQuestion_post(p1));
    }
    else{
        d1 = getDate_answer(getAnswer_post(p1));
    }
    if(type2 == 1){
        d2 = getCreationDate_question(getQuestion_post(p2));
    }
    else{
        d2 = getDate_answer(getAnswer_post(p2));
    }

    result = compare_dates(d1, d2);

    return result;
}

PROFILE create_profile(char * my_about, size_t my_id, char * my_name, ssize_t my_reputation){
    PROFILE p= malloc(sizeof(struct profile));

    p->inserts=0;
    p->n_posts= 0;
    p->oldest = NULL;
    p->about_me = g_strdup(my_about);
    p->id = my_id;
    p->name = g_strdup(my_name);
    p->reputation = my_reputation;

    p->ten_posts = g_ptr_array_new();
    p->id_answers = g_array_new(FALSE, FALSE, sizeof(size_t));

    return p;
}

void free_profile(void* p){
    PROFILE tmp = (PROFILE)p;

    g_ptr_array_free(tmp->ten_posts, FALSE);
    g_array_free(tmp->id_answers, TRUE);

    free(tmp->name);
    free(tmp->about_me);

    free(tmp);
}

/**
 * Getters
 */

// TODO GET 10 POSTS

GPtrArray* getTenPosts_profile(PROFILE p){
    return p->ten_posts;
}
GArray* getId_answers_array_profile(PROFILE p){
    return p->id_answers ? p->id_answers : NULL;


    /* confirmar se é preciso dup
    GArray* novo = g_array_new(FALSE, FALSE, sizeof(size_t));

    for(int i = 0; i < d->id_answers->len; i++){
        g_array_append_val(novo, g_array_index(d->id_answers, size_t, i));
    }

    return novo; */
}

char* getAboutMe_profile(PROFILE p){
    return p->about_me ? g_strdup(p->about_me) : NULL;
}

char* getName_profile(PROFILE p){
    return p->name ? g_strdup(p->name) : NULL;
}

size_t getNposts_profile(PROFILE p){
    return p->n_posts;
}

size_t getId_profile(PROFILE p){
    return p->id;
}

ssize_t getReputation_profile(PROFILE p){
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

void setId_profile(PROFILE p, size_t my_id){
    p->id = my_id;
}

void setName_profile(PROFILE p, char* my_name){
     if(my_name != NULL){
        p->name ? (free(p->name), p->name = g_strdup(my_name)) : (p->name = g_strdup(my_name));
    }
}

void setReputation_profile(PROFILE p, ssize_t my_reputation){
    p->reputation = my_reputation;
}


/**
 * Aux functions
 */

void addIdAnswer_profile(PROFILE p, size_t id){
  if(p->id_answers !=NULL)
         g_array_append_val(p->id_answers, id);
}

void increaseNposts_profile(PROFILE p){
    ++(p->n_posts);
}

void insertLastest_profile(PROFILE p, POST post){
  int i ;
    if(p->oldest != NULL && p->inserts >= 10 && compare_dates(p->oldest, getDate_post(post)) < 0){
      g_ptr_array_add(p->ten_posts, post);
      qsort(p->ten_posts, p->ten_posts->len, sizeof(POST), cmpDates);
      g_ptr_array_remove_index(p->ten_posts, 0);
      p->oldest = getDate_post(post);
    }
    if(p->oldest == NULL)
         g_ptr_array_add(p->ten_posts, post);
    if(p->oldest != NULL &&  p->inserts < 10 && compare_dates(p->oldest, getDate_post(post)) < 0){
         g_ptr_array_add(p->ten_posts, post);
         qsort(p->ten_posts, p->ten_posts->len, sizeof(POST), cmpDates);
         p->oldest = getDate_post(post);
         ++(p->inserts);
    }
    if(p->oldest != NULL &&  p->inserts < 10 && compare_dates(p->oldest, getDate_post(post)) > 0){
         g_ptr_array_add(p->ten_posts, post);
         ++(p->inserts);
         qsort(p->ten_posts, p->ten_posts->len, sizeof(POST), cmpDates);
    }
}
