#include "profile.h"
#include <stdlib.h>
#include <glib.h>
#include "post.h"
#include "question.h"
#include "mydate.h"

/**
 *  @brief Estrutura que contém os principais atributos associados aos utilizadores:
 *  GSequence sao guardadas as questões e respostas criadas pelo dito utilizador;
 *  informação do perfil e nome do utilizador;número de posts;id do utilizador e reputação
 *  de um utilizador
 */

struct profile{
    GSequence* posts;

    char* about_me;
    char* name;

    long n_posts;
    long id;
    int reputation;
};


/**
 *  @brief  Função responsável pela criação dos perfis dos utilizadores de
 *  acordo com os atributos acima referidos
 *  @param my_about Informação do perfil,my_id ID do utilizador,my_name
 *  Nome do Utilizador,my_reputation Reputação do Utilizador
 *  @return Criação do Perfil dos Utilizadores
 */

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

/**
 *  @brief  Função que liberta o perfil do utilizador assim como alguns
 *  dos seus atributos
 *  @param p Um Post
 */

void free_profile(void* p){
    PROFILE tmp = (PROFILE) p;

    g_sequence_free(tmp->posts);
    g_free(tmp->about_me);
    g_free(tmp->name);

    free(tmp);
}

/**
 *  @brief A função que se segue é responsável pela leitura dos
 *  Posts do perfil de um Utilizador
 *  @param p Perfil Utilizador
 *  @return GSequence com o tipo do Post
 */

GSequence* getPosts_profile(PROFILE p){
    return p->posts;
}

/**
 *  @brief A função que se segue é responsável pela leitura da
 *  informação do perfil de um Utilizador
 *  @param p Perfil Utilizador
 *  @return Array com a informação do Utilizador
 */

char* getAboutMe_profile(PROFILE p){
    return p->about_me ? g_strdup(p->about_me) : NULL;
}

/**
 *  @brief A função que se segue é responsável pela leitura do
 *  nome de um Utilizador
 *  @param p Perfil Utilizador
 *  @return Array com o nome dos vários Utilizadores
 */

char* getName_profile(PROFILE p){
    return p->name ? g_strdup(p->name) : NULL;
}

/**
 *  @brief A função que se segue é responsável pela leitura do
 *  número de Posts do perfil de um Utilizador
 *  @param p Perfil Utilizador
 *  @return Número de Posts de um Utilizador
 */

long getNposts_profile(PROFILE p){
    return p->n_posts;
}

/**
 *  @brief A função que se segue é responsável pela leitura
 *  do ID de um Utilizador
 *  @param p Perfil Utilizador
 *  @return ID de um utilizador
 */

long getId_profile(PROFILE p){
    return p->id;
}

/**
 *  @brief A função que se segue é responsável pela leitura da
 *  Reputação de um Utilizador
 *  @param p Perfil Utilizador
 *  @return quantia da Reputação
 */

int getReputation_profile(PROFILE p){
    return p->reputation;
}


/**
 *  @brief Função que se segue é auxiliar da função insertLatest_profile.
 *  Usada para ordenar posts em cronologia inversa, ou seja, mais recente
 *  no ínicio da lista
 *  @param a e b São 2 posts,cmp_data Compara da data de ambos os posts
 *  @return Ordenação pelo post mais recente
 */

static gint cmpPosts(gconstpointer a, gconstpointer b, gpointer cmp_data){
    POST pa = (POST) a;
    POST pb = (POST) b;

    MyDate da = getDate_post(pa);
    MyDate db = getDate_post(pb);

    //Ordem decrescente de nº de respostas
    return (gint) compare_dates(db, da);
}

/**
 *  @brief Função responsável pela inserção do utilizador mais recente no início
 *  @param p Perfil do Utilizador,post Post do Utilizador
 */

void insertLastest_profile(PROFILE p, POST post){
    // g_sequence_prepend(p->posts, (gpointer)post);
    g_sequence_insert_sorted(p->posts, (gpointer) post, cmpPosts, NULL);
    ++(p->n_posts);
}
