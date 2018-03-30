#include "main_struct.h"
#include <glib.h>
#include "profile.h"
#include "post.h"


struct  TCD_community{
    GHashTable* profiles; //PtrArray que funcs like hashtable :D

    GHashTable* posts; //Hash posts por id TODO

    GPtrArray* year_answers; // 2008 -> 2018
    GPtrArray* year_questions;
};

TAD_community create_main_struct(){
    TAD_community m = malloc(sizeof(struct TCD_community));

    m->profiles = g_hash_table_new_full(g_int64_hash, g_int64_equal, g_free, free_profile);
    m->posts = g_hash_table_new_full(g_int64_hash, g_int64_equal, g_free, free_post);



    // REVIEW
    m->year_questions= g_ptr_array_sized_new(10);
    g_ptr_array_set_free_func(m->year_questions, g_free);

    m->year_answers = g_ptr_array_sized_new(10);
    g_ptr_array_set_free_func(m->year_answers, g_free);



    return m;
}

TAD_community clean(TAD_community com){
    g_hash_table_destroy(com->profiles);
    g_hash_table_destroy(com->posts);

    g_ptr_array_free(com->year_questions, TRUE);
    g_ptr_array_free(com->year_answers, TRUE);

    free(com);
    return NULL;
}

GHashTable* getProfiles_TAD(TAD_community com){
    return com->profiles;
}

GHashTable* getPosts_TAD(TAD_community com){
    return com->posts;
}


TAD_community init(){
    return create_main_struct();
}

