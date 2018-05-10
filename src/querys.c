#include "date.h"
#include "user.h"
#include "pair.h"
#include "list.h"

#include "post.h"
#include "profile.h"
#include "main_struct.h"
#include "answer.h"
#include "question.h"

#include <stdlib.h>
#include <stdio.h>
#include "interface.h"
#include <glib.h>
#include <gmodule.h>
#include <string.h>

STR_pair get_info_from_post(TAD_community com, QUESTION q){
    char* titulo = NULL;
    char* name = NULL;

    titulo = getTitle_question(q);

    long owner_ptr = getOwnerId_question(q);

    PROFILE profile_ptr = getProfile_TAD(com, owner_ptr);

    if(profile_ptr != NULL){
        name = getName_profile(profile_ptr);
    }

    STR_pair ret = create_str_pair(titulo, name);

    return ret;
}

STR_pair info_from_post(TAD_community com, long id){
    POST post_ptr = getPost_TAD(com, id);
    STR_pair ret = NULL;

    if(post_ptr != NULL){
        if(getType_post(post_ptr) == 1){ //question
            ret = get_info_from_post(com, getQuestion_post(post_ptr));
        }else{
            long parent_id = getParentId_answer(getAnswer_post(post_ptr));
            post_ptr = getPost_TAD(com, parent_id);
            ret = get_info_from_post(com, getQuestion_post(post_ptr));
        }
    }
    return ret;
}
//END QUERY 1

typedef struct query2{
    int size;
    int len;
    PROFILE* arrlist;
    QUESTION* present; // para a query 11
    int present_index;
}* QUERY2;

/**
 * @brief Insere ordenadamente um perfil num array
 *
 * @param data Estrutura contendo o array e outros dados
 * @param p Perfil a ser inserido
 */
static void g_array_insert_sorted(QUERY2 data, PROFILE p){
    int done = 0;
    int tmp = data->len;
    if(data->len == 0){
        data->arrlist[0] = p;
        data->len++;
        return;
    }
    for(int i = 0; i < data->len && !done; i++){
        long old = getNposts_profile(data->arrlist[i]);
        long new = getNposts_profile(p);
        if(old < new){
            tmp = i;
            done = 1;
        }
    }
    int j = data->len;
    while(j > tmp){
        data->arrlist[j] = data->arrlist[j - 1];
        j--;
    }
    data->arrlist[tmp] = p;
    data->len++;
    if(data->len > data->size) data->len--;
}

/**
 * @brief Passa os utilizadores de uma HashTable para um array ordenado pelo número de posts (decrescente)
 * Chama a funcao g_insert_sorted para inserir ordenadamente um perfil no array de perfis
 * @param key Chave da HashTable
 * @param value Valor corresponde da chave da Hashtable (perfil de um utilizador)
 * @param user_data Estrutura com os dados necessários a outras funcoes auxiliares
 */
static GHFunc query_2_hash_to_array(gpointer key, gpointer value, gpointer user_data){
    (void)key;
    QUERY2 data = (QUERY2) user_data;
    PROFILE p = (PROFILE) value;

    g_array_insert_sorted(data, p);
    return NULL;
}

LONG_list top_most_active(TAD_community com, int N){
    PROFILE* arrlist = malloc(sizeof(PROFILE) * (N + 1));
    QUERY2 user_data = malloc(sizeof(struct query2));
    user_data->arrlist = arrlist;
    user_data->size = N;
    user_data->len = 0;

    profilesForEach_TAD(com, (GHFunc) query_2_hash_to_array, (gpointer) user_data);

    LONG_list final = create_list(N);

    for(int i = 0; i < N; i++){
        set_list(final, i, getId_profile(arrlist[i]));
    }

    free(arrlist);
    free(user_data);
    return final;
}
//END QUERY 2


//QUERY nº3
LONG_pair total_posts(TAD_community com, Date begin, Date end){
    MyDate beginn = create_date_with_teachers_date(begin);
    MyDate endd   = create_date_with_teachers_date(end);

    GSequence* seq_1 = getFromToF_TAD(com, beginn, endd, 1, NULL);
    GSequence* seq_2 = getFromToF_TAD(com, beginn, endd, 2, NULL);

    long n_seq_1 = g_sequence_get_length(seq_1);
    long n_seq_2 = g_sequence_get_length(seq_2);

    LONG_pair ret = create_long_pair(n_seq_1, n_seq_2);

    g_sequence_free(seq_1);
    g_sequence_free(seq_2);
    free_Mydate(beginn);
    free_Mydate(endd);

    return ret;
}
//END QUERY nº3


//QUERY nº4
typedef struct query4{
    char* tag_name;
    GArray* arr;
}* QUERY4;

static gint query_4_cmp_func(gconstpointer a, gconstpointer b, gpointer cmp_data){
    (void)cmp_data;
    QUESTION aa = (QUESTION) a;
    QUESTION bb = (QUESTION) b;

    MyDate ma = getCreationDate_question(aa);
    MyDate mb = getCreationDate_question(bb);

    //Decrescente - Mais recente para mais antigo
    return (gint) compare_dates(mb, ma);
}

static GFunc search_tag_questions(gpointer data, gpointer elem){
    QUERY4 user_data = (QUERY4) elem;
    QUESTION q = (QUESTION) data;

    char* found = strstr(getTags_question(q), user_data->tag_name);
    if(found != NULL){
        long id = getId_question(q);
        g_array_append_val(user_data->arr, id);
    }
    return NULL;
}

LONG_list questions_with_tag(TAD_community com, char* tag, Date begin, Date end){
    MyDate beginn = create_date_with_teachers_date(begin);
    MyDate endd   = create_date_with_teachers_date(end);

    GSequence* seq = getFromToF_TAD(com, beginn, endd, 1, query_4_cmp_func);

    if(g_sequence_is_empty(seq)) return NULL;

    QUERY4 user_data = malloc(sizeof(struct query4));
    GArray* tst = g_array_new(FALSE, FALSE, sizeof(long));
    user_data->tag_name = tag;
    user_data->arr = tst;

    g_sequence_foreach(seq, (GFunc) search_tag_questions, (gpointer) user_data);
    LONG_list final = create_list(tst->len);
    for(int i = 0; i < (int) tst->len; i++){
        set_list(final, i, g_array_index(tst, long, i));
    }

    free(user_data);
    g_array_free(tst, TRUE);
    g_sequence_free(seq);
    free_Mydate(beginn);
    free_Mydate(endd);

    return final;
}
//END QUERY nº4


//QUERY 5
USER get_user_info(TAD_community com, long id){
    USER res = NULL;
    long post_history[10];

    PROFILE profile_ptr = getProfile_TAD(com, id);

    if(profile_ptr != NULL){
        char* aboutme = getAboutMe_profile(profile_ptr);

        GSequence* posts = getPosts_profile(profile_ptr);
        GSequenceIter* bg = g_sequence_get_begin_iter(posts);
        GSequenceIter* nd = g_sequence_get_iter_at_pos(posts, 10);

        if(g_sequence_get(bg) != NULL){
            int i = 0;
            do{
                POST p = g_sequence_get(bg);
                if(getType_post(p) == 1){
                    post_history[i] = getId_question(getQuestion_post(p));
                }else{
                    post_history[i] = getID_answer(getAnswer_post(p));
                }
                i++;
                bg = g_sequence_iter_next(bg);
            }while(i < 10 && bg != nd);
        }
        res = create_user(aboutme, post_history);
    }

    return res;
}
//END QUERY nº5


//QUERY nº6
typedef struct query6{
    LONG_list ret;
    int i;
}* QUERY6;

static GFunc query_6_convert_long(gpointer data, gpointer user_data){
    QUERY6 tmp = (QUERY6) user_data;
    ANSWER a = (ANSWER) data;

    set_list(tmp->ret, tmp->i, getID_answer(a));
    tmp->i++;

    return NULL;
}

static gint query_6_cmp_func(gconstpointer a, gconstpointer b, gpointer cmp_data){
    (void)cmp_data;
    ANSWER aa = (ANSWER) a;
    ANSWER bb = (ANSWER) b;

    int na = getScore_answer(aa);
    int nb = getScore_answer(bb);

    if(na > nb){
        return -1;
    }
    else if (na < nb){
            return 1;
        }
        else{
            return 0;
        }
}

LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end){
    MyDate beginn = create_date_with_teachers_date(begin);
    MyDate endd   = create_date_with_teachers_date(end);

    GSequence* seq = getFromToF_TAD(com, beginn, endd, 2, query_6_cmp_func);

    if(g_sequence_is_empty(seq)) return NULL;

    QUERY6 user_data = malloc(sizeof(struct query6));
    user_data->i = 0;

    LONG_list ret;
    long l_seq = g_sequence_get_length(seq);
    if(l_seq > N)
        ret = create_list(N);
    else{
        ret = create_list(l_seq);
        N = l_seq;
    }

    user_data->ret = ret;

    GSequenceIter* a1 = g_sequence_get_begin_iter(seq);
    GSequenceIter* a2 = g_sequence_get_iter_at_pos(seq, N);

    g_sequence_foreach_range(a1, a2, (GFunc) query_6_convert_long, user_data);


    free(user_data);
    g_sequence_free(seq);
    free_Mydate(beginn);
    free_Mydate(endd);

    return ret;
}
//END QUERY nº6


//QUERY nº7

typedef struct query7{
    LONG_list ret;
    int i;
    int size;
}* QUERY7;

typedef struct query7_extra{
    long id;
    int count;
}* QUERY7_EXTRA;

typedef struct query7_dates{
    TAD_community cam;
    MyDate bg;
    MyDate nd;
    GSequence* seq;
}* QUERY7_DATES;

static void query_7_convert_long(gpointer data, gpointer user_data){
    QUERY7 tmp = (QUERY7) user_data;
    QUERY7_EXTRA q = (QUERY7_EXTRA) data;

    //if(tmp->i < tmp->size){
   //     printf("%d --- %ld -> %d\n", tmp->i, q->id, q->count); //TODO
        set_list(tmp->ret, tmp->i, q->id);
        tmp->i++;
  //  }
}

static gint cmp_func(gconstpointer a, gconstpointer b, gpointer cmp_data){
    (void)cmp_data;
    QUERY7_EXTRA aa = (QUERY7_EXTRA) a;
    QUERY7_EXTRA bb = (QUERY7_EXTRA) b;

    int na = aa->count;
    int nb = bb->count;
    //Ordem decrescente de nº de respostas
    return nb - na;
}

static GSequenceIter* search_for_item(GSequence* seq, long id){
    GSequenceIter* bg = g_sequence_get_begin_iter(seq);
    GSequenceIter* nd = g_sequence_get_end_iter(seq);

    while(bg != nd){
        QUERY7_EXTRA a = g_sequence_get(bg);
        if(a->id == id) return bg;
        bg = g_sequence_iter_next(bg);
    }
    return NULL;
}

static GFunc query_7_organize(gpointer data, gpointer user_data){
    QUERY7_DATES dados = (QUERY7_DATES) user_data;
    ANSWER a = (ANSWER) data;

    GSequenceIter* gg = search_for_item(dados->seq, getParentId_answer(a));

    if(gg == NULL){ //Nao existe essa questao na seq
        MyDate cmp = getDate_post(getPost_TAD(dados->cam, getParentId_answer(a)));
        if(cmp == NULL) return NULL;
        if(compare_dates(dados->bg, cmp) && compare_dates(dados->nd, cmp)){
            QUERY7_EXTRA tp = malloc(sizeof(struct query7_extra));
            tp->id = getParentId_answer(a);
            tp->count = 1;
            g_sequence_append(dados->seq, (gpointer)tp);
        }
    }
    else{
        QUERY7_EXTRA qq = g_sequence_get(gg);
        qq->count++;
    }
    return NULL;
}

LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end){
    MyDate beginn = create_date_with_teachers_date(begin);
    MyDate endd   = create_date_with_teachers_date(end);
    GSequence* seq = getFromToF_TAD(com, beginn, endd, 2, NULL);

    if(g_sequence_is_empty(seq)) return NULL;

    GSequence* tmp = g_sequence_new(NULL);
    QUERY7_DATES date_organize = malloc(sizeof(struct query7_dates));
    date_organize->cam = com;
    date_organize->bg = beginn;
    date_organize->nd = endd;
    date_organize->seq = tmp;
    g_sequence_foreach(seq, (GFunc)query_7_organize, (gpointer)date_organize);
    g_sequence_free(seq);


    QUERY7 user_data = malloc(sizeof(struct query7));

    int n_len = g_sequence_get_length(tmp);
    if(n_len > N)
        user_data->ret = create_list(N);
    else{
        user_data->ret = create_list(n_len);
        N = n_len;
    }
    user_data->i = 0;
    user_data->size = N;

    g_sequence_sort(tmp, cmp_func, NULL);

    //GSequenceIter* bg = g_sequence_get_begin_iter(tmp);
    //GSequenceIter* ed = g_sequence_get_iter_at_pos(tmp, N);

    g_sequence_foreach(tmp, (GFunc) query_7_convert_long, user_data);
    //g_sequence_foreach_range(bg, ed, (GFunc) query_7_convert_long, user_data);

    LONG_list ret = user_data->ret;

    free(user_data);
    g_sequence_free(tmp); //Falta dar free de cada
    free_Mydate(beginn);
    free_Mydate(endd);

    return ret;
}
//END QUERY nº7


//QUERY nº8
typedef struct query8{
    GArray* ret;
    char* title_name;
}* QUERY8;

static GFunc search_title_name(gpointer data, gpointer elem){
    QUERY8 user_data = (QUERY8) elem;
    QUESTION q = (QUESTION) data;

    char* found = strstr(getTitle_question(q), user_data->title_name);
    if(found != NULL){
        long id = getId_question(q);
        g_array_append_val(user_data->ret, id);
    }

    return NULL;
}

LONG_list contains_word(TAD_community com, char* word, int N){
    MyDate begin = create_date(0,0,0,0,1,1,2008);
    MyDate end = create_date(0,0,0,0,31,12,2018);
    GSequence* seq = getFromToF_TAD(com, begin, end, 1, query_4_cmp_func);

    if(g_sequence_is_empty(seq)) return NULL;

    QUERY8 user_data = malloc(sizeof(struct query8));
    GArray* tst = g_array_new(FALSE, FALSE, sizeof(long));
    user_data->title_name = word;
    user_data->ret = tst;

    g_sequence_foreach(seq, (GFunc) search_title_name, (gpointer) user_data);

    LONG_list final;
    if((int)tst->len > N)
        final = create_list(N);
    else{
        final = create_list(tst->len + 1);
        N = tst->len;
    }

    for(int i = 0; i < N; i++){
        set_list(final, i, g_array_index(tst, long, i));
    }
    set_list(final, N, (long)NULL);

    g_sequence_free(seq);
    free_Mydate(begin);
    free_Mydate(end);
    free(user_data);
    g_array_free(tst, TRUE);

    return final;
}
//END QUERY nº8


//QUERY nº9
typedef struct query9{
    long id2;
    GSequence* seq;
    TAD_community com;
}* QUERY9;

gint query_9_exists_question(gconstpointer a, gconstpointer b, gpointer user_data){
    (void)user_data;
    return a - b;
}

static GFunc sequence_function(gpointer elem, void* data){
    POST p = (POST) elem;
    QUERY9 user_data = (QUERY9) data;
    QUESTION q;

    if(getType_post(p) == 2){
        ANSWER a = getAnswer_post(p);

        q = getQuestion_post(getPost_TAD(user_data->com, getParentId_answer(a)));

        if(getOwnerId_question(q) == user_data->id2){
            //Verificar se já existe
            if(g_sequence_lookup(user_data->seq, (gpointer) q, (GCompareDataFunc)query_9_exists_question, NULL) == NULL){
                g_sequence_insert_sorted(user_data->seq, (gpointer) q, (GCompareDataFunc) query_4_cmp_func, NULL);
                return NULL;
            }
        }
    }else{
        q = getQuestion_post(p);
    }

    GArray* ans = getIdAnswers_question(q);
    for(int i = 0; i < (int) ans->len; i++){
        long tmp_id = getOwnerId_answer(getAnswer_post(getPost_TAD(user_data->com, g_array_index(ans, long, i))));
        if(tmp_id == user_data->id2){
            //So quero perguntas e Verificar se já existe
            if(g_sequence_lookup(user_data->seq, (gpointer) q, (GCompareDataFunc)query_9_exists_question, NULL) == NULL){
                g_sequence_insert_sorted(user_data->seq, (gpointer) q, (GCompareDataFunc) query_4_cmp_func, NULL);
                return NULL;
            }
        }
    }

    return NULL;
}

LONG_list both_participated(TAD_community com, long id1, long id2, int N){
    PROFILE p1 = getProfile_TAD(com, id1);
    if(p1 == NULL) return NULL;
    if(!(getNposts_profile(p1))) return NULL; //caso nao tenha respostas

    PROFILE p2 = getProfile_TAD(com, id2);
    if(p2 == NULL) return NULL;
    if(!(getNposts_profile(p2))) return NULL; //caso nao tenha respostas


    GSequence* seq = g_sequence_new(NULL);

    //Ver o menor
    GSequence* a1 = getPosts_profile(p1);

    QUERY9 user_data = malloc(sizeof(struct query9));
    user_data->id2 = id2;
    user_data->seq = seq;
    user_data->com = com;

    g_sequence_foreach(a1, (GFunc) sequence_function, (gpointer) user_data);

    if(g_sequence_is_empty(seq)) return NULL;

    LONG_list final;
    int g_size = g_sequence_get_length(seq);
    if(g_size < N){
        final = create_list(g_size);
        N = g_size;
    }
    else
        final = create_list(N);

    GSequenceIter* bg = g_sequence_get_begin_iter(seq);
    GSequenceIter* nd = g_sequence_get_end_iter(seq);

    for(int i = 0; i < N && bg != nd; i++, bg = g_sequence_iter_next(bg)){
        QUESTION q = g_sequence_get(bg);
        set_list(final, i, getId_question(q));
    }

    g_sequence_free(seq);
    free(user_data);

    return final;
}
//END QUERY nº9


//QUERY nº10
long better_answer(TAD_community com, long id){
    QUESTION q = getQuestion_post(getPost_TAD(com, id));
    if(q == NULL) return -1;
    long res = 0;
    GArray* answers = getIdAnswers_question(q);

    long tmp = 0;
    long total = 0;
    long scr = 0;
    long owner_id;
    PROFILE p;
    long rep = 0;
    long comments = 0;
    //Setting up first values
    long id_ans = g_array_index(answers, long, 0);
    ANSWER a = getAnswer_post(getPost_TAD(com, id_ans));
    if(a != NULL){
        scr = getScore_answer(a);
        owner_id = getOwnerId_answer(a);
        p = getProfile_TAD(com, owner_id);
        rep = getReputation_profile(p);
        comments = getComments_answer(a);
        tmp = (long) ((scr * 0.45) + (rep * 0.25) + (scr * 0.2) + (comments * 0.1));
        res = getID_answer(a);
        total = tmp;
    }

    for(int i = 1; i < (int) answers->len; i++){
        id_ans = g_array_index(answers, long, i);
        a = getAnswer_post(getPost_TAD(com, id_ans));
        if(a != NULL){
            scr = getScore_answer(a);
            owner_id = getOwnerId_answer(a);
            p = getProfile_TAD(com, owner_id);
            rep = getReputation_profile(p);
            comments = getComments_question(q);
            tmp = (long) ((scr * 0.45) + (rep * 0.25) + (scr * 0.2) + (comments * 0.1));
            if(tmp > total){
                total = tmp;
                res = getID_answer(a);
            }
        }else break;
    }
    return res;
}
//END QUERY nº10

//QUERY nº11
static GFunc catamorfismo(gpointer data, gpointer user_data){
    QUESTION q = (QUESTION) data;
    QUERY2 userd = (QUERY2) user_data;
    int i = 0;
    long parent_id = getOwnerId_question(q);
      for(i = 0; i < userd->len; i++){
          if(parent_id == getId_profile(userd->arrlist[i])){
              userd->present[userd->present_index] = q;
              ++(userd->present_index);
          }
          else
            continue;
    }
    return NULL;
}

static long max_index(long* a, int n){
    if(n <= 0) return -1;
    long i, max_i = 0;
    long max = a[0];
    for(i = 1; i < n; ++i){
        if(a[i] > max){
            max = a[i];
            max_i = i;
        }
    }
    return max_i;
}

static gint query_11_cmp_func(gconstpointer a, gconstpointer b, gpointer cmp_data){
    (void)cmp_data;
    QUESTION aa = (QUESTION) a;
    QUESTION bb = (QUESTION) b;

    long ida = getId_question(aa);
    long idb = getId_question(bb);
    //Decrescente - Mais recente para mais antigo
    return (gint) ida-idb;
}
LONG_list most_used_best_rep(TAD_community com, int N, Date begin, Date end){
    GList* tags = getTags_TAD(com);
    long ntags = getNTags_TAD(com);
    long countTags[ntags];
    for(int k = 0; k < ntags; k++){
        countTags[k] = 0;
    }
    // get by dates
    GSequence* seq = getFromToF_TAD(com, create_date_with_teachers_date(begin), create_date_with_teachers_date(end), 1,
            query_11_cmp_func);

    PROFILE* arrlist = malloc(sizeof(PROFILE) * (N));
    QUESTION* presents = malloc(sizeof(QUESTION) * (g_sequence_get_length(seq)));
    QUERY2 user_data = malloc(sizeof(struct query2));
    user_data->arrlist = arrlist;
    user_data->size = N;
    user_data->len = 0;
    user_data->present = presents;
    user_data->present_index = 0;

    profilesForEach_TAD(com, (GHFunc) query_2_hash_to_array, (gpointer) user_data);
    g_sequence_foreach(seq, (GFunc) catamorfismo, user_data);
    user_data->size = N;
    if(user_data->present_index == 0) return NULL;

    char tag1[64], tag2[64], tag3[64], tag4[64], tag5[64];
    tag1[0] = tag2[0] = tag3[0] = tag4[0] = tag5[0] = 0;
    int i = 0;
    int j = 0;
    for(i = 0; i < user_data->present_index; i++){
        sscanf(getTags_question(user_data->present[i]), "<%[^>]><%[^>]><%[^>]><%[^>]><%[^>]>", tag1, tag2, tag3, tag4,
                tag5);
        if(*tag1 != 0){
            j = 0;
            while(tags){
                if(!strcmp((char*) tags->data, tag1))
                    countTags[j] += 1;
                if(tags->next == NULL) break;
                tags = tags->next;
                ++j;
            }
            tags = g_list_first(tags);
        }

        if(*tag2 != 0){
            j = 0;
            while(tags){
                if(!strcmp((char*) tags->data, tag2))
                    countTags[j] += 1;
                if(tags->next == NULL) break;
                tags = tags->next;
                ++j;
            }
            tags = g_list_first(tags);
        }

        if(*tag3 != 0){
            j = 0;
            while(tags){
                if(!strcmp((char*) tags->data, tag3))
                    countTags[j] += 1;
                if(tags->next == NULL) break;
                tags = tags->next;
                ++j;
            }
            tags = g_list_first(tags);
        }

        if(*tag4 != 0){
            j = 0;
            while(tags){
                if(!strcmp(tags->data, tag4))
                    countTags[j] += 1;
                if(tags->next == NULL) break;
                tags = tags->next;
                ++j;
            }
            tags = g_list_first(tags);
        }

        if(*tag5 != 0){
            j = 0;
            while(tags){
                if(!strcmp((char*) tags->data, tag5))
                    countTags[j] += 1;
                if(tags->next == NULL) break;
                tags = tags->next;
                ++j;
            }
            tags = g_list_first(tags);
        }
        tag1[0] = tag2[0] = tag3[0] = tag4[0] = tag5[0] = 0;
    }

    LONG_list l = create_list(N);
    int n = 0;
    while(n < N){
        long m = max_index(countTags, (int) ntags);
        char* t = (char*) g_list_nth_data(tags, (guint) m);
        set_list(l, n, getQuark_TAD(com, t));
        countTags[m] = 0;
        ++n;
    }

    return l;
}
//END QUERY nº11
