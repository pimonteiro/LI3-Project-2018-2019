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

//QUERY nº1
STR_pair get_info_from_post(TAD_community com, QUESTION q){
    char* titulo;
    char* name;

    titulo = getTitle_question(q);

    long owner_ptr = getOwnerId_question(q);

    PROFILE profile_ptr = getProfile_TAD(com, owner_ptr);

    if(profile_ptr != NULL){
        name = getName_profile(profile_ptr);
    }


    STR_pair ret = create_str_pair(name, titulo);

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
            post_ptr = getPost_TAD(com,parent_id);
            ret = get_info_from_post(com, getQuestion_post(post_ptr));
        }
    }
    return ret;
}
//END QUERY nº1

//QUERY nº2
typedef struct query2{
    int size;
    int len;
    PROFILE *arrlist;
}* QUERY2;

void g_array_insert_sorted(QUERY2 data, PROFILE p){
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
            data->arrlist[j] = data->arrlist[j-1];
            j--;
        }
    data->arrlist[tmp] = p;
    data->len++;
    if(data->len > data->size) data->len--;
}

GHFunc query_2_hash_to_array(gpointer key, gpointer value, gpointer user_data){
    QUERY2 data = (QUERY2) user_data;
    PROFILE p = (PROFILE) value;

    g_array_insert_sorted(data, p);
}


LONG_list top_most_active(TAD_community com, int N){
    PROFILE *arrlist = malloc(sizeof(PROFILE) * (N+1));
    QUERY2 user_data = malloc(sizeof(struct query2));
    user_data->arrlist = arrlist;
    user_data->size = N;
    user_data->len = 0;


    profilesForEach_TAD(com, (GHFunc) query_2_hash_to_array, (gpointer) user_data);

    LONG_list final = create_list(N);

    for(int i = 0; i < N; i++){
        set_list(final, i, getId_profile(arrlist[i]));
    }
    return final;
}
//END QUERY nº2


//QUERY nº3
typedef struct query3{
    long n_answers;
    long n_questions;
}* QUERY3;

GFunc query_3_count_posts(gpointer data, gpointer user_data){
    QUERY3 tmp = (QUERY3) user_data;
    POST p = (POST) data;
    if(getType_post(p) == 1) tmp->n_questions++;
    else tmp->n_answers++;
}

LONG_pair total_posts(TAD_community com, Date begin, Date end){
    GSequence* seq = getFromToF_TAD(com, create_date_with_teachers_date(begin), create_date_with_teachers_date(end), 1, NULL);
    if(!g_sequence_get_length(seq)) return NULL;

    QUERY3 user_data = malloc(sizeof(struct query3));
    user_data->n_answers   = 0;
    user_data->n_questions = 0;
    GSequenceIter* bg  = g_sequence_get_begin_iter(seq);
    GSequenceIter* ed  = g_sequence_get_end_iter(seq);
    g_sequence_foreach_range (bg, ed, (GFunc) query_3_count_posts, user_data);

    LONG_pair ret = create_long_pair(user_data->n_questions, user_data->n_answers);
    return ret;
}
//END QUERY nº3


//QUERY nº4
typedef struct query4 {
    LONG_list ret;
    int i;
}* QUERY4;

gint query_4_cmp_func(gconstpointer a, gconstpointer b, gpointer cmp_data){
    QUESTION aa = (QUESTION) a;
    QUESTION bb = (QUESTION) b;

    MyDate ma = getCreationDate_question(aa);
    MyDate mb = getCreationDate_question(bb);

    return (gint) compare_dates(mb,ma);

}


void query_4_convert_long(gpointer data, gpointer user_data){
    QUERY4 tmp = (QUERY4) user_data;
    QUESTION q = (QUESTION) data;

    printf("%ld CMP\n", getId_question(q));
}

LONG_list questions_with_tag(TAD_community com, char* tag, Date begin, Date end){
    GSequence* seq = getFromToF_TAD(com, create_date_with_teachers_date(begin), create_date_with_teachers_date(end), 1, query_4_cmp_func);

    if(g_sequence_is_empty(seq)) return NULL;

    GSequenceIter* a1 = g_sequence_get_begin_iter(seq);
    GSequenceIter* a2 = g_sequence_get_iter_at_pos(seq, 1);

    QUESTION q1 = g_sequence_get(a1);
    QUESTION q2 = g_sequence_get(a2);
    QUERY4 user_data = malloc(sizeof(struct query4));



    LONG_list ret = user_data->ret;
    free(user_data);

    return ret;

}
//END QUERY nº4


//QUERY 5

void query_5_sequence_to_list(long post_history[], GSequence* posts){

}

USER get_user_info(TAD_community com, long id){
    USER res = NULL;
    long post_history[10];

    for(int i = 0; i < 10; i++){
        post_history[i] = 0;
    }

    PROFILE profile_ptr = getProfile_TAD(com, id);

    if(profile_ptr != NULL){
        char *name = getName_profile(profile_ptr);
        char *aboutme = getAboutMe_profile(profile_ptr);
        int n = strlen(name) + strlen(aboutme) + 12;
        char short_bio[n];
        sprintf(short_bio, "Name: %s Bio: %s", name, aboutme);

        GSequence* posts = getPosts_profile(profile_ptr);
        GSequenceIter* bg = g_sequence_get_begin_iter(posts);
        GSequenceIter* nd = g_sequence_get_iter_at_pos(posts, 10);

        if(g_sequence_get(bg) != NULL){
            int i = 0;
            do{
                POST p = g_sequence_get(bg);
                if(getType_post(p) == 1){
                    post_history[i] = getId_question(getQuestion_post(p));
                }
                else{
                    post_history[i] = getID_answer(getAnswer_post(p));
                }
                i++;
                bg = g_sequence_get_iter_at_pos(posts, i);
            }while(i < 10 && bg != nd);
        }
        res = create_user(short_bio, post_history);
    }

    return res;
}
//END QUERY nº5


//QUERY nº6
typedef struct query6{
      LONG_list ret;
      int i;
      int size;
    }*QUERY6;

void query_6_convert_long(gpointer data,gpointer user_data){
  QUERY6 tmp = (QUERY6) user_data;
  ANSWER q = (ANSWER) data;

  if(tmp->i < tmp->size){
    set_list(tmp->ret,tmp->i,getID_answer(q));
    tmp->i++;
  }
}

gint query_6_cmp_func(gconstpointer a,gconstpointer b,gpointer cmp_data){
  ANSWER aa = (ANSWER)a;
  ANSWER ab = (ANSWER)b;

  int na = getScore_answer(aa);
  int nb = getScore_answer(ab);

  return na-nb;
}

LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end){
  GSequence* seq = getFromToF_TAD(com,create_date_with_teachers_date(begin),create_date_with_teachers_date(end),1,query_6_cmp_func);

  if(g_sequence_is_empty(seq)) return NULL;

  QUERY6 user_data = malloc(sizeof(struct query6));
  user_data->i = 0;
  user_data->size = N;

  for(int i = 0; i < N;i++){
    set_list(user_data->ret,i,0);
  }

  GSequenceIter* a1 = g_sequence_get_begin_iter(seq);
  GSequenceIter* a2 = g_sequence_get_iter_at_pos(seq,N);

  g_sequence_foreach_range(a1,a2,(GFunc) query_6_convert_long,user_data);

  LONG_list ret = user_data->ret;
  free(user_data);

  return ret;

}
//END QUERY nº6


//QUERY nº7

typedef struct query7 {
    LONG_list ret;
    int i;
    int size;
}* QUERY7;


void query_7_convert_long(gpointer data, gpointer user_data){
    QUERY7 tmp = (QUERY7) user_data;
    QUESTION q = (QUESTION) data;

    if(tmp->i < tmp->size){
        set_list(tmp->ret, tmp->i, getId_question(q));
        tmp->i++;
    }
}

gint cmp_func(gconstpointer a, gconstpointer b, gpointer cmp_data){
    QUESTION qa = (QUESTION)a;
    QUESTION qb = (QUESTION)b;

    int na = getNanswers_question(qa);
    int nb = getNanswers_question(qb);
    //Ordem decrescente de nº de respostas
    return na - nb;

}

LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end){
    GSequence* seq = getFromToF_TAD(com, create_date_with_teachers_date(begin), create_date_with_teachers_date(end), 1, cmp_func);
    if(g_sequence_is_empty(seq)) return NULL;

    //Transformacao para LONG_list CUIDADO o N está errado: tenho de ver se nao é menor que N
    QUERY7 user_data = malloc(sizeof(struct query7));
    user_data->ret = create_list(N);
    user_data->i   = 0;
    user_data->size = N;

    for(int i = 0; i < N; i++){
        set_list(user_data->ret, i, 0);
    }

    GSequenceIter* bg  = g_sequence_get_begin_iter(seq);
    GSequenceIter* ed  = g_sequence_get_iter_at_pos(seq, N);

    g_sequence_foreach_range (bg, ed, (GFunc) query_7_convert_long, user_data);



    LONG_list ret = user_data->ret;
    free(user_data);

    return ret;
}
//END QUERY nº7


//QUERY nº8
LONG_list contains_word(TAD_community com, char* word, int N){


}
//END QUERY nº8


/* //QUERY nº9


int exists_already(GArray* a, long n){
    if(!(a->len)) return 0;
    for(int i = 0; i < a-> len; i++){
        if(g_array_index(a, size_t, i) == n) return 1;
    }

    return 0;
}

typedef struct query9 {
    GHashTable* posts;
    long id1;
    long id2;
    GArray* final;
}* QUERY9;


GFunc sequence_function(gpointer elem, void* user_data){
    POST p = (POST) elem;
    QUERY9 pts = (QUERY9) user_data;

    if(getType_post(p))






    size_t parent_a = getParentId_answer(getAnswer_post(p));
    QUESTION q = g_hash_table_lookup(pts->posts, &parent_a);

    //Verificacao das questoes
    if(getOwnerId_question(q) == pts->id2)
        if(!exists_already(pts->final, parent_a)) g_array_append_val(pts->final, parent_a); //adiciona por nao existir

    //Verificacao das respostas das questoes
    GArray* a2 = getIdAnswers_question(q);
        if((a2->len)){
            for(int j = 0; j < a2->len; j++){
                size_t n_an = g_array_index(a2, size_t, j);
                ANSWER a = getAnswer_post(g_hash_table_lookup(pts->posts, &n_an));

                if(getOwnerId_answer(a) == pts->id2)
                    if(!exists_already(pts->final, n_an))
                        g_array_append_val(pts->final, n_an);
            }
        }
}

/*void get_common_posts(GArray* final, TAD_community com, long id1, long id2){
    GHashTable* posts = getPosts_TAD(com);
    GSequence* a1 = getId_answers_array_profile(g_hash_table_lookup(getProfiles_TAD(com), &id1));

    TMP1 user_data;
    user_data->posts = posts;
    user_data->final = final;
    user_data->id1 = id1;
    user_data->id2 = id2;

    g_sequence_foreach(a1, (GFunc)sequence_function,  (gpointer)user_data);


    for(int i = 0; i < a1->len; i++){
        //size_t n = g_array_index(a1, size_t, i);
        //size_t parent_a = getParentId_answer(g_hash_table_lookup(posts, &n));
        //QUESTION q = getQuestion_post(g_hash_table_lookup(posts, &parent_a));

        //Verificacao das questoes
        //if(getOwnerId_question(q) == id2)
         //   if(!exists_already(final, n)) g_array_append_val(final, n); //adiciona por nao existir

        //Verificacao das respostas das questoes
        GArray* a2 = getIdAnswers_question(q);
        if((a2->len)){
            for(int j = 0; j < a2->len; j++){
                size_t n_an = g_array_index(a2, size_t, j);
                ANSWER a = getAnswer_post(g_hash_table_lookup(posts, &n_an));

                if(getOwnerId_answer(a) == id2)
                    if(!exists_already(final, n_an)) g_array_append_val(final, n_an);
            }
        }
    }

}

LONG_list both_participated(TAD_community com, long id1, long id2, int N){
    PROFILE p1 = getProfile_TAD(com, id1);

    if (!(getNposts_profile(p1))) return NULL; //caso nao tenha respostas

    PROFILE p2 = g_hash_table_lookup(getProfiles_TAD(com), &id2);
    if (!(getNposts_profile(p2))) return NULL; //caso nao tenha respostas


    GArray* final = g_array_new(FALSE, FALSE, sizeof(size_t));

    QUERY9 user_data = malloc(sizeof(struct query9));

    GSequence* a1 = getPosts_profile(p1);
    user_data->posts = posts;
    user_data->final = final;
    user_data->id1 = id1;
    user_data->id2 = id2;
    g_sequence_foreach(a1, (GFunc)sequence_function,  (gpointer)user_data);



    a1 = getPosts_profile(p2);
    user_data->id1 = id2;
    user_data->id2 = id1;
    g_sequence_foreach(a1, sequence_function,  (gpointer)user_data);


    //Ordenar por ordem inversa e retornar ultimas


    g_array_free(final, TRUE); //i think
    return NULL;
}
//END QUERY nº9
 */

//QUERY nº10
long better_answer(TAD_community com, long id){
    QUESTION q = getQuestion_post(getPost_TAD(com, id));
    if(q == NULL) return -1;
    long res = 0;
    GArray* answers = getIdAnswers_question(q);

    size_t tmp = 0;
    size_t total = 0;
    size_t scr = 0;
    size_t owner_id;
    PROFILE p;
    size_t rep = 0;

    //Setting up first values
    size_t id_ans = g_array_index(answers, size_t, 0);
    ANSWER a = getAnswer_post(getPost_TAD(com, id_ans));
    if(a != NULL){
        scr      = getScore_answer(a);
        owner_id = getOwnerId_answer(a);
        p        = getProfile_TAD(com, owner_id);
        rep      = getReputation_profile(p);

        tmp   = (scr * 0.45) + (rep * 0.25) + (scr * 0.2) + (rep * 0.1);
        res   = getID_answer(a);
        total = tmp;
    }

    for(size_t i = 1; i < answers->len; i++){
        id_ans = g_array_index(answers, long, i);
        a = getAnswer_post(getPost_TAD(com, id_ans));
        if(a != NULL){
            scr      = getScore_answer(a);
            owner_id = getOwnerId_answer(a);
            p        = getProfile_TAD(com, owner_id);
            rep      = getReputation_profile(p);

            tmp = (scr * 0.45) + (rep * 0.25) + (scr * 0.2) + (rep * 0.1);
            if(tmp > total){
                total = tmp;
                res   = getID_answer(a);
            }
        }
        else break;
    }
    return total;
}
//END QUERY nº10

//QUERY nº11
LONG_list most_used_best_rep(TAD_community com, int N, Date begin, Date end){
    return NULL;
}
//END QUERY nº11






























/*

//QUERY nº2
LONG_list top_most_active(TAD_community com, int N){
    LONG_list res = create_list(N);

    GHashTableIter i;
    gpointer key, value;

    for(int i = 0; i < N; i++){
        g_hash_table_iter_next (i, getProfiles_TAD(com));
        //Conseguir o primeiro numero de posts da pessoa no primeiro index da hash
        long tmp_total;
        long tmp_id; //dara warning por termos long na estrutura?

        while(g_hash_table_iter_next(&i, &key, &value)){
            long aux = value->id_questions->len + value->id_awnsers->len;
            if (tmp_total < aux){
                tmp_total = aux;
                tmp_id = value->id;
            }
        }

        set_list(res, i, tmp_id);
    }
    return res;
}
*/
