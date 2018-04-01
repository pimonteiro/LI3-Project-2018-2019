#include "main_struct.h"
#include <glib.h>
#include "profile.h"
#include "post.h"
#include "tardis.h"

struct  TCD_community{
    GHashTable* profiles; //PtrArray que funcs like hashtable :D

    GHashTable* posts; //Hash posts por id

    TARDIS type40; // Estrutura com os dados

    GPtrArray* tags; // Cada indice corresponde a uma tagg
};

TAD_community create_main_struct(){
    TAD_community m = malloc(sizeof(struct TCD_community));

    m->profiles = g_hash_table_new_full(g_int64_hash, g_int64_equal, g_free, free_profile);
    m->posts = g_hash_table_new_full(g_int64_hash, g_int64_equal, g_free, free_post);

    m->type40 = lading_tardis(); // Upload .mp3 landing sounds


    return m;
}

TAD_community clean(TAD_community com){
    g_hash_table_destroy(com->profiles);
    g_hash_table_destroy(com->posts);
    takeOf_tardis(com->type40);
// TARDIS FREE
    free(com);

    return NULL; // kek.exe
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

