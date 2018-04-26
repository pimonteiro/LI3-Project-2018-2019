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
 *  @brief Estrutura principal: 3 Hashtables para users, posts e tags respetivamente.
 *  Tardis é uma estrutura que consiste num array de arrays com GSequences,
 *   o primeiro array corresponde aos anos, o segundo array corresponde aos
 *    meses e aos dias desse ano. Por último, temos o número de tags
*/
struct TCD_community{
    GHashTable* profiles;
    GHashTable* posts;
    GHashTable* tags;
    TARDIS type40;
    long n_tags;
};

/**
 *  @brief Função que é responsável pela criação da estrutura principal
    com todas as suas estruturas e componentes
 *  @return criação da estrutura
 */

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
 *  @brief  Função que liberta tanto as componentes existentes na
 *  Estrutura Principal como a Estrutura em si
 *  @param com Estruturs Principal
 *  @return libertação da Estrutura
 */

TAD_community clean(TAD_community com){
    g_hash_table_destroy(com->tags);
    takeOf_tardis(com->type40);
    g_hash_table_destroy(com->posts);
    g_hash_table_destroy(com->profiles);

    free(com);

    return NULL;
}

/**
 *  @brief  Função que inicializa a Estrutura Principal
 *  @return inicialização da Estrutura
 */

TAD_community init(){
    return create_main_struct();
}

/**
 *  @brief Função responsável pela inserção de um
 *  user na Estrutura Principal
 *  @param com Estrutura Principal, p Perfil de um user, id ID de um user
 */
void insertProfile_TAD(TAD_community com, PROFILE p, long id){
    gint64* key = malloc(sizeof(gint64));
    *key = id;
    g_hash_table_insert(com->profiles, key, (gpointer) p);
}

/**
 *  @brief Função responsável pela inserção de uma
 *  questão na Estrutura Principal
 *  @param com Estrutura Principal, q Questão, id ID da questão, owner_id ID de
 * quem formulou a questão,p Post desse user,start Data de escrita da questão
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
 *  @brief Função responsável pela inserção de uma
 *  resposta na Estrutura Principal
 *  @param com Estrutura Principal, a Answer, id ID da resposta, owner_id ID de
 * quem formulou a resposta,parent_id ID da questão correspondente a uma dada resposta
 *  p Post desse user,start Data de escrita da resposta
 */
/
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
 *  @brief Função responsável pela inserção de uma
 *  tag na Estrutura Principal
 *  @param com Estrutura Principal,tag_name Nome da tag, id ID da tag
*/
void insertTag_TAD(TAD_community com, char* tag_name, long id){
    g_hash_table_insert(com->tags, tag_name, (gpointer) id);
}

/**
 *  @brief Função que se segue responsável pela leitura
 *  do perfil de um user da Estrutura Principal
 *  @param com Estrutura Principal, id ID de um user
 *  @return HashTable com os perfis dos users
 */
PROFILE getProfile_TAD(TAD_community com, long id){
    return (PROFILE) g_hash_table_lookup(com->profiles, &id);
}

/**
 *  @brief  Função que se segue responsável pela leitura dos
 *  Posts da Estrutura Principal
 *  @param com Estrutura Principal, id do Utilizador
 *  @return
 */
POST getPost_TAD(TAD_community com, long id){
    return (POST) g_hash_table_lookup(com->posts, &id);
}

/**
 *  @brief Função que calcula o intervalo arbitrário de tempo que é pedido em algumas queries
 *  @param com Estrutura Principal, inicio  e fim intervalo arbitrário de datas, type 1-Question
 *  2-Answer,f compara datas
 *  @return GSequence de um intervalo aleatório de tempo
 */
GSequence* getFromToF_TAD(TAD_community com, MyDate inicio, MyDate fim, int type, GCompareDataFunc f){
    return getRangeFilter_TARDIS(com->type40, inicio, fim, type, f);
}

/**
 *  @brief Função que se segue
 *  @param com Estrutura Principal
 */
void profilesForEach_TAD(TAD_community com, GHFunc f, gpointer user_data){
    assert(f != NULL && user_data != NULL);
    g_hash_table_foreach(com->profiles, f, user_data);
}

/**
 *  @brief
 *  @param com Estrutura Principal, tag Array com as tags
 *  @return
 */
long getQuark_TAD(TAD_community com, char* tag){
    long quark = (long) g_hash_table_lookup(com->tags, tag);
    if(quark) return quark;

    return -1;
}

/**
 *  @brief Função responsável pela leitura do número
 *  de tags da Estrutura Principal
 *  @param com Estrutura Principal
 *  @return Número de tags
*/

long getNTags_TAD(TAD_community com){
    return com->n_tags;
}

/**
 *  @brief Função que se segue faz com que seja possível
 *  a modificação do número de tags da Estrutura Principal
 *  @param com Estrutura Principal
 */

void setNTags_TAD(TAD_community com){
    GList* tmp = g_hash_table_get_keys(com->tags);
    com->n_tags = (long) g_list_length(tmp);
    g_list_free(tmp);
}

/**
 *  @brief Função responsável pela leitura de uma
 *  tag da Estrutura Principal
 *  @param com Estrutura Principal
 *  @return Dupla lista ligada com as tags
*/

GList* getTags_TAD(TAD_community com){
    return g_hash_table_get_keys(com->tags);
}
