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


/**
@file querys.c
Ficheiro das querys
*/


/**
 * QUERY 1
 *
 * @brief Auxiliar de info_from_post que retira informacao da questao
 * Devido á possibilidade de receber um ID de um post tipo resposta e sendo retirada apenas
 * a informacao referente á respetiva, a funcao info_from_post trata o ID de forma a
 * esta auxiliar receber apenas o post tipo pergunta.
 * @param q Questao a ser analizada
 * @return Par contendo a informaçao do post
 */
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

    free_profile(profile_ptr);
    return ret;
}

 /**
 * @brief Retorna o titulo de um dado POST e o nome do seu criador
 * Se for o ID de uma resposta, passa á funcao auxiliar o ID da correspondente pergunta
 * Caso contrário passa diretamente o ID dessa pergunta
 * @param id ID do post a ser analizado
 * @return Par com informacao do post: Nome do Utilizador - Titulo do Post
 */
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
    free_post(post_ptr);
    return ret;
}
//END QUERY 1

/**
 * QUERY 2
 *
 * @brief Estrutura para faciliar a passagem de dados entre funcoes
 * @var size Número máximo de utilizadores dentro do array
 * @var len Tamanho do array com os perfis dos utilizadores
 * @var arrlist Array de perfis dos utilizadores
 *
 */
typedef struct query2{
    int size;
    int len;
    PROFILE *arrlist;
    PROFILE* present; // para a query 11
    int present_index;
}* QUERY2;

/**
 * @brief Insere ordenadamente um perfil num array
 *
 * @param data Estrutura contendo o array e outros dados
 * @param p Perfil a ser inserido
 */
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

/**
 * @brief Passa os utilizadores de uma HashTable para um array ordenado pelo número de posts (decrescente)
 * Chama a funcao g_insert_sorted para inserir ordenadamente um perfil no array de perfis
 * @param key Chave da HashTable
 * @param value Valor corresponde da chave da Hashtable (perfil de um utilizador)
 * @param user_data Estrutura com os dados necessários a outras funcoes auxiliares
 */
GHFunc query_2_hash_to_array(gpointer key, gpointer value, gpointer user_data){
    QUERY2 data = (QUERY2) user_data;
    PROFILE p = (PROFILE) value;

    g_array_insert_sorted(data, p);

}

/**
 * QUERY 2
 * @brief Retorna os N utilizadores com maior número de posts de sempre
 * Depois de ordenar por ordem decrescente pelo numero de posts de todos os utilizadores
 * é transformada no tipo de retorno
 * @param N Numero de utilizadores
 * @return LONG_list Lista dos utilizadores
 */
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

    free(arrlist);      //DOUBT
    free(user_data);
    return final;
}
//END QUERY 2


//QUERY nº3

GFunc print_que(gpointer data, gpointer user_data){
    QUESTION q = (QUESTION) data;
    printf("%ld\n", getId_question(q));
}

GFunc print_ans(gpointer data, gpointer user_data){
    ANSWER q = (ANSWER) data;
    printf("%ld\n", getID_answer(q));
}

LONG_pair total_posts(TAD_community com, Date begin, Date end){
    GSequence* seq_1 = getFromToF_TAD(com, create_date_with_teachers_date(begin), create_date_with_teachers_date(end), 1, NULL);
    GSequence* seq_2 = getFromToF_TAD(com, create_date_with_teachers_date(begin), create_date_with_teachers_date(end), 2, NULL);

    g_sequence_foreach(seq_1, print_que, NULL);
    //printf("----------------------------\n");
    //g_sequence_foreach(seq_2, print_ans, NULL);


    long n_seq_1 = g_sequence_get_length(seq_1);
    long n_seq_2 = g_sequence_get_length(seq_2);


    LONG_pair ret = create_long_pair(n_seq_1, n_seq_2);

    free(seq_1);
    free(seq_2);

    return ret;
}
//END QUERY nº3


//QUERY nº4
typedef struct query4{
    char* tag_name;
    GArray* arr;
}* QUERY4;

gint query_4_cmp_func(gconstpointer a, gconstpointer b, gpointer cmp_data){
    QUESTION aa = (QUESTION) a;
    QUESTION bb = (QUESTION) b;

    MyDate ma = getCreationDate_question(aa);
    MyDate mb = getCreationDate_question(bb);

    return (gint) compare_dates(mb,ma);

}

GFunc search_tag_questions(gpointer data, gpointer elem){
    QUERY4 user_data = (QUERY4) elem;
    QUESTION q = (QUESTION) data;

    char* found = strstr(getTags_question(q), user_data->tag_name);
    if(found != NULL){
        long id = getId_question(q);
        g_array_append_val(user_data->arr, id);
    }

}

LONG_list questions_with_tag(TAD_community com, char* tag, Date begin, Date end){
    GSequence* seq = getFromToF_TAD(com, create_date_with_teachers_date(begin), create_date_with_teachers_date(end), 1, query_4_cmp_func);

    if(g_sequence_is_empty(seq)) return NULL;

    QUERY4 user_data = malloc(sizeof(struct query4));
    GArray* tst = g_array_new(FALSE, FALSE, sizeof(long));
    user_data->tag_name = tag;
    user_data->arr = tst;

    g_sequence_foreach(seq, (GFunc) search_tag_questions, (gpointer) user_data);
    LONG_list final = create_list(tst->len);
    for(int i = 0; i < (int)tst->len; i++){
        printf("%d --- %ld\n", i, g_array_index(tst, long, i));
        set_list(final, i, g_array_index(tst, long, i));
    }
    free(user_data);

    return final;

}
//END QUERY nº4


//QUERY 5
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

GFunc query_6_convert_long(gpointer data,gpointer user_data){
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

    QUERY7 user_data = malloc(sizeof(struct query7));

    int n_len = g_sequence_get_length(seq);
    if(n_len > N)
        user_data->ret = create_list(N);
    else{
        user_data->ret = create_list(n_len);
        N = n_len;
    }
    user_data->i   = 0;
    user_data->size = N;

    GSequenceIter* bg  = g_sequence_get_begin_iter(seq);
    GSequenceIter* ed  = g_sequence_get_iter_at_pos(seq, N);

    g_sequence_foreach_range (bg, ed, (GFunc) query_7_convert_long, user_data);


    LONG_list ret = user_data->ret;
    free(user_data);
    free(seq);

    return ret;
}
//END QUERY nº7


//QUERY nº8
typedef struct query8{
      LONG_list ret;
      char* title_name;
      GSequence* seq;
      int i;
      int size;
   }*QUERY8;

  GFunc query_8_convert_long(gpointer data,gpointer user_data){
    QUERY8 tmp = (QUERY8) user_data;
    QUESTION q = (QUESTION) data;

    if (tmp->i < tmp->size){
      set_list(tmp->ret,tmp->i,getId_question(q));
      tmp->i++;
    }
  }

gint query_8_cmp_func(gconstpointer a, gconstpointer b, gpointer cmp_data){
    QUESTION aa = (QUESTION) a;
    QUESTION bb = (QUESTION) b;

    MyDate ma = getCreationDate_question(aa);
    MyDate mb = getCreationDate_question(bb);

    return (gint) compare_dates(mb,ma);

}
  GFunc search_title_name(gpointer data, gpointer elem){
      QUERY8 user_data = (QUERY8) elem;
      QUESTION q = (QUESTION) data;

      char* found = strstr(getTitle_question(q), user_data->title_name);
      if(found != NULL){
          long id = getId_question(q);
          g_array_append_val(user_data->ret, id);
      }
  }

LONG_list contains_word(TAD_community com, char* word, int N){

    GSequence* seq = getFromToF_TAD(com,2008,2018,1,query_8_cmp_func);

    if(g_sequence_is_empty(seq)) return NULL;

    QUERY8 user_data = malloc(sizeof(struct query8));
    GArray* tst = g_array_new(FALSE, FALSE, sizeof(long));
    user_data->title_name = word;
    user_data->ret = tst;

    g_sequence_foreach(seq, (GFunc) search_title_name, (gpointer) user_data);
    LONG_list final = create_list(tst->len);
    for(int i = 0; i < (int)tst->len; i++){
        printf("%d --- %ld\n", i, g_array_index(tst, long, i));
        set_list(final, i, g_array_index(tst, long, i));
    }
    free(user_data);

    return final;




/*
 GSequenceIter* bg = g_sequence_get_begin_iter(seq);
 GsequenceIter* nd = g_sequence_get_iter_at_pos(seq,N);

  g_sequence_foreach_range (bg, ed, (GFunc) query_8_convert_long, user_data);

 QUERY7 user_data = malloc(sizeof(struct query7));

 LONG_list ret = user_data->ret;
 free(user_data);
 return ret; */

}
//END QUERY nº8


//QUERY nº9
typedef struct query9 {
    long id2;
    GSequence* seq;
    TAD_community com;
}* QUERY9;

/*
GCompareDataFunc query_9_cmp_func(gconstpointer a, gconstpointer b, gpointer cmp_data){
    QUESTION aa = (QUESTION) a;
    QUESTION bb = (QUESTION) b;

    MyDate ma = getCreationDate_question(aa);
    MyDate mb = getCreationDate_question(bb);

    return (gint) compare_dates(mb,ma);

}
*/

GFunc sequence_function(gpointer elem, void* data){
    POST p = (POST) elem;
    QUERY9 user_data = (QUERY9) data;
    QUESTION q;
    if(p == NULL) printf("I GOT EMPTY POST\n");

    if(getType_post(p) == 2){
        ANSWER a = getAnswer_post(p);
        if(a == NULL) printf("I GOT EMPTY ANSWER\n");

        q = getQuestion_post(getPost_TAD(user_data->com, getParentId_answer(a)));
        if(p == NULL) printf("I GOT EMPTY QUESTION AFTER ANSWER\n");

        if(getOwnerId_question(q) == user_data->id2){
            g_sequence_insert_sorted(user_data->seq, (gpointer) getId_question(q), (GCompareDataFunc) query_4_cmp_func, NULL);
        }
    }
    else{
        q = getQuestion_post(p);
        if(p == NULL) printf("I GOT EMPTY QUESTION\n");
    }

    GArray* ans = getIdAnswers_question(q);
    for(int i = 0; i < (int) ans->len; i++){
        long tmp_id = getOwnerId_answer(getAnswer_post(getPost_TAD(user_data->com, g_array_index(ans, long, i))));
        if(tmp_id == user_data->id2){
            g_sequence_insert_sorted(user_data->seq, (gpointer) getId_question(q), (GCompareDataFunc) query_4_cmp_func, NULL);
            break;
        }
    }
}


LONG_list both_participated(TAD_community com, long id1, long id2, int N){
    PROFILE p1 = getProfile_TAD(com, id1);
    if(p1 == NULL) return NULL;
    if (!(getNposts_profile(p1))) return NULL; //caso nao tenha respostas

    PROFILE p2 = getProfile_TAD(com, id2);
    if(p2 == NULL) return NULL;
    if (!(getNposts_profile(p2))) return NULL; //caso nao tenha respostas


    GSequence* seq = g_sequence_new(NULL);

    GSequence* a1 = getPosts_profile(p1);

    QUERY9 user_data = malloc(sizeof(struct query9));
    user_data->id2 = id2;
    user_data->seq = seq;
    user_data->com = com;

    g_sequence_foreach(a1, (GFunc)sequence_function,  (gpointer)user_data);

    if(g_sequence_is_empty(seq)) return NULL;

    LONG_list final;
    int g_size = g_sequence_get_length(seq);
    if(g_size < N){
        final = create_list(g_size);
        N = g_size;
    }
    else final = create_list(N);

    GSequenceIter* bg = g_sequence_get_begin_iter(seq);
    GSequenceIter* nd = g_sequence_get_end_iter(seq);

    for(int i = 0; i < N && bg != nd; i++, bg = g_sequence_iter_next(bg)){
        printf("%d ---- %ld\n", i, (long)g_sequence_get(bg));
        set_list(final, i, (long)g_sequence_get(bg));
    }

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

    //Setting up first values
    long id_ans = g_array_index(answers, long, 0);
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

    for(int i = 1; i < (int)answers->len; i++){
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
GFunc catamorfismo(gpointer data, gpointer user_data){
    QUESTION q = (QUESTION) data;
    QUERY2 userd = (QUERY2)user_data;
    int i = 0;
    int present = 0;
    long parent_id = getOwnerId_question(q);
    for(i=0; i < userd->len; i++){
        if(parent_id == getId_profile(userd->arrlist[i]))
          userd->present[userd->present_index++] = q;
    }

}

  LONG_list most_used_best_rep(TAD_community com, int N, Date begin, Date end){
    // get by dates
    GSequence* seq = getFromToF_TAD(com,create_date_with_teachers_date(begin),create_date_with_teachers_date(end),1,NULL);
    // get top n cancros
    PROFILE *arrlist = malloc(sizeof(PROFILE) * (N+1));
    PROFILE *presents = malloc(sizeof(PROFILE) * (g_sequence_get_length(seq)+1));
    QUERY2 user_data = malloc(sizeof(struct query2));
    user_data->arrlist = arrlist;
    user_data->size = N;
    user_data->len = 0;
    user_data->present =  presents;
    user_data->present_index = 0;
    profilesForEach_TAD(com, (GHFunc) query_2_hash_to_array, (gpointer) user_data);

    g_sequence_foreach(seq, catamorfismo,user_data);


    int i = 0;
    GString* tags = g_string_new(NULL);

    for(i=0; i < user_data->present_index-1; i++){
        g_string_append(tags, getTags_question(user_data->present[i]));
    }
    return NULL;

}
//END QUERY nº11
