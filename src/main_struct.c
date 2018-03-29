#include "main_struct.h"
#include "profile.h"
#include "question.h"
#include "date.h"
#include "post.h"
#include <sys/types.h>
#include <glib.h>
#include <stdlib.h>

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