#include "main_struct.h"
#include <glib.h>
#include <assert.h>
#include "profile.h"
#include "question.h"
#include "answer.h"
#include "post.h"
#include "mydate.h"
#include "tardis.h"


/**
 *  @brief
 *  @param
 *  @return
 */
/*Estrutura principal: 3 Hashtables para users, posts e tags respetivamente. Tardis é uma estrutura de dados que armazena em 2 arrays os meses e anos. */
struct TCD_community{
    GHashTable* profiles;
    GHashTable* posts;
    GHashTable* tags;
    TARDIS type40;
    long n_tags;
};

/**
 *  @brief
 *  @param
 *  @return
 */
/*Função responsável pela criação da estrutura principal */
TAD_community create_main_struct(){
    TAD_community m = malloc(sizeof(struct TCD_community));

    m->profiles = g_hash_table_new_full(g_int64_hash, g_int64_equal, g_free, free_profile);
    m->posts = g_hash_table_new_full(g_int64_hash, g_int64_equal, g_free, free_post);
    m->tags = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, NULL);
    m->type40 = landing_tardis(2018 - 2008); // Upload .mp3 landing sounds
    m->n_tags = 0;
    return m;
}

/**
 *  @brief
 *  @param
 *  @return
 */
/*Função que liberta tanto as componentes existentes na Estrutura Principal como a Estrutura em si */
TAD_community clean(TAD_community com){
    g_hash_table_destroy(com->tags);
    takeOf_tardis(com->type40);
    g_hash_table_destroy(com->posts);
    g_hash_table_destroy(com->profiles);

    free(com);

    return NULL; // kek.exe
}

/**
 *  @brief
 *  @param
 *  @return
 */
/*As funções que se seguem executam os get's dos users,posts,tags e tardis para que seja possivel a sua leitura dos respetivos ficheiros */
/*Função que inicializa a Estrutura de dados */
TAD_community init(){
    return create_main_struct();
}

/**
 *  @brief
 *  @param
 *  @return
 */
void insertProfile_TAD(TAD_community com, PROFILE p, long id){
    gint64* key = malloc(sizeof(gint64));
    *key = id;
    g_hash_table_insert(com->profiles, key, (gpointer) p);
}

/**
 *  @brief
 *  @param
 *  @return
 */
void insertQuestion_TAD(TAD_community com, QUESTION q, long id, long owner_id, POST p, MyDate start){
    gint64* key = malloc(sizeof(gint64));
    *key = id;
    g_hash_table_insert(com->posts, key, (gpointer) p);

    insert_TARDIS(com->type40, q, start, 1);

    PROFILE prof = (PROFILE) g_hash_table_lookup(com->profiles, &owner_id);
    if(prof)
        insertLastest_profile(prof, p);
}

/**
 *  @brief
 *  @param
 *  @return
 */
void insertAnswer_TAD(TAD_community com, ANSWER a, long id, long owner_id, long parent_id, POST p, MyDate start){
    gint64* key = malloc(sizeof(gint64));
    *key = id;
    g_hash_table_insert(com->posts, key, (gpointer) p);

    insert_TARDIS(com->type40, a, start, 2);

    PROFILE prof = (PROFILE) g_hash_table_lookup(com->profiles, &owner_id);
    if(prof)
        insertLastest_profile(prof, p);

    POST q = g_hash_table_lookup(com->posts, &parent_id);
    if(q)
        setAnswers_array_question(getQuestion_post(q), id);
}

/**
 *  @brief
 *  @param
 *  @return
 */
void insertTag_TAD(TAD_community com, char* tag_name, long id){
    g_hash_table_insert(com->tags, tag_name, (gpointer) id);
}

/**
 *  @brief
 *  @param
 *  @return
 */
PROFILE getProfile_TAD(TAD_community com, long id){
    return (PROFILE) g_hash_table_lookup(com->profiles, &id);
}

/**
 *  @brief
 *  @param
 *  @return
 */
POST getPost_TAD(TAD_community com, long id){
    return (POST) g_hash_table_lookup(com->posts, &id);
}

/**
 *  @brief
 *  @param
 *  @return
 */
GSequence* getFromToF_TAD(TAD_community com, MyDate inicio, MyDate fim, int type, GCompareDataFunc f){
    return getRangeFilter_TARDIS(com->type40, inicio, fim, type, f);
}

/**
 *  @brief
 *  @param
 *  @return
 */
void profilesForEach_TAD(TAD_community com, GHFunc f, gpointer user_data){
    assert(f != NULL && user_data != NULL);
    g_hash_table_foreach(com->profiles, f, user_data);
}

/**
 *  @brief
 *  @param
 *  @return
 */
long getQuark_TAD(TAD_community com, char* tag){
    long quark = (long) g_hash_table_lookup(com->tags, tag);
    if(quark) return quark;

    return -1;
}

/**
 *  @brief
 *  @param
 *  @return
 */
long getNTags_TAD(TAD_community com){
    return com->n_tags;
}

/**
 *  @brief
 *  @param
 *  @return
 */
void setNTags_TAD(TAD_community com){
    GList* tmp = g_hash_table_get_keys(com->tags);
    com->n_tags = (long) g_list_length(tmp);
    g_list_free(tmp);
}

/**
 *  @brief
 *  @param
 *  @return
 */
GList* getTags_TAD(TAD_community com){
    return g_hash_table_get_keys(com->tags);
}
