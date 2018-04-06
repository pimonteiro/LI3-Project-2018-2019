#include "main_struct.h"
#include <glib.h>
#include "profile.h"
#include "post.h"
#include "tardis.h"

struct  TCD_community{
    GHashTable* profiles; //PtrArray que funcs like hashtable :D
    GHashTable* posts; //Hash posts por id
    GHashTable* tags;
    TARDIS type40; // Estrutura com os dados

};

TAD_community create_main_struct(){
    TAD_community m = malloc(sizeof(struct TCD_community));

    m->profiles = g_hash_table_new_full(g_int64_hash, g_int64_equal, g_free, free_profile);
    m->posts = g_hash_table_new_full(g_int64_hash, g_int64_equal, g_free, free_post);
    m->tags = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, NULL);
    m->type40 = landing_tardis(2018-2008); // Upload .mp3 landing sounds
    return m;
}

TAD_community clean(TAD_community com){
    g_hash_table_destroy(com->profiles);
    g_hash_table_destroy(com->posts);
    g_hash_table_destroy(com->tags);
    takeOf_tardis(com->type40);
    free(com);

    return NULL; // kek.exe
}

GHashTable* getProfiles_TAD(TAD_community com){
    return com->profiles;
}

GHashTable* getPosts_TAD(TAD_community com){
    return com->posts;
}

GHashTable* getTags_TAD(TAD_community com){
    return com->tags;
}

TARDIS getTARDIS_TAD(TAD_community com){
    return com->type40;
}

TAD_community init(){
    return create_main_struct();
}

