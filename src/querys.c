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
    
    PROFILE profile_ptr = g_hash_table_lookup(getProfiles_TAD(com), &owner_ptr);

    if(profile_ptr != NULL){
        name = getName_profile(profile_ptr);
    }


    STR_pair ret = create_str_pair(name, titulo);

    return ret;
}




STR_pair info_from_post(TAD_community com, long id){
    POST post_ptr = g_hash_table_lookup(getPosts_TAD(com), &id);

    STR_pair ret = NULL;

    if(post_ptr != NULL){
        if(getType_post(post_ptr) == 1){ //question
            ret = get_info_from_post(com, getQuestion_post(post_ptr));
        }else{
            long parent_id = getParentId_answer(getAnswer_post(post_ptr));
            post_ptr = g_hash_table_lookup(getPosts_TAD(com), &parent_id);
            ret = get_info_from_post(com, getQuestion_post(post_ptr));
        }
    }

    return ret;
}
//END QUERY nº1

//QUERY nº2
LONG_list top_most_active(TAD_community com, int N){
    return NULL;
}
//END QUERY nº2


//QUERY nº3
LONG_pair total_posts(TAD_community com, Date begin, Date end){
    return NULL;
}
//END QUERY nº3


//QUERY nº4
LONG_list questions_with_tag(TAD_community com, char* tag, Date begin, Date end){
    return NULL;
}
//END QUERY nº4


//QUERY 5 
USER get_user_info(TAD_community com, long id){
    USER res = NULL;
    long post_history[10];

    PROFILE profile_ptr = g_hash_table_lookup(getProfiles_TAD(com), &id);

    if(profile_ptr != NULL){
        char *name = getName_profile(profile_ptr);
        char *aboutme = getAboutMe_profile(profile_ptr);
        int n = strlen(name) + strlen(aboutme) + 12;
        char short_bio[n];
        sprintf(short_bio, "Name: %s Bio: %s", name, aboutme);
        res = create_user(short_bio, post_history);
    }


    //Perante os dois arrays de id_questions e id_awnsers, como verifica los por ordem cronologica inversa? (sem destincao)
    //Maybe guardar, em vez de um array, uma struct que tem id e tipo_post (1/2), assim estariam por ordem cronologica e
    //seria mais eficiente procurar

    
    return res;
}
//END QUERY nº5


//QUERY nº6
LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end){
    return NULL;
}
//END QUERY nº6


//QUERY nº7
LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end){
    return NULL;
}
//END QUERY nº7


//QUERY nº8
LONG_list contains_word(TAD_community com, char* word, int N){
    return NULL;
}
//END QUERY nº8


//QUERY nº9


int exists_already(GArray* a, long n){
    if(!(a->len)) return 0;
    for(int i = 0; i < a-> len; i++){
        if(g_array_index(a, size_t, i) == n) return 1;
    }

    return 0;
} 


void get_common_posts(GArray* final, TAD_community com, long id1, long id2){
    GHashTable* posts = getPosts_TAD(com);
    GArray* a1 = getId_answers_array_profile(g_hash_table_lookup(getProfiles_TAD(com), &id1));

    for(int i = 0; i < a1->len; i++){
        size_t n = g_array_index(a1, size_t, i);
        size_t parent_a = getParentId_answer(g_hash_table_lookup(posts, &n));
        QUESTION q = getQuestion_post(g_hash_table_lookup(posts, &parent_a));

        //Verificacao das questoes
        if(getOwnerId_question(q) == id2)
            if(!exists_already(final, n)) g_array_append_val(final, n); //adiciona por nao existir

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
    PROFILE teste = g_hash_table_lookup(getProfiles_TAD(com), &id1);
    GArray* a1 = getId_answers_array_profile(teste);
    if (!(a1->len)) return NULL; //caso nao tenha respostas

    GHashTable* posts = getPosts_TAD(com);
    GArray* final = g_array_new(FALSE, FALSE, sizeof(size_t));
    
    get_common_posts(final, com, id1, id2);
    get_common_posts(final, com, id2, id1);
    

    //Ordenar por ordem inversa e retornar ultimas


    g_array_free(final, TRUE); //i think
    return NULL;
}
//END QUERY nº9


//QUERY nº10
long better_answer(TAD_community com, long id){
    QUESTION q = getQuestion_post(g_hash_table_lookup(getPosts_TAD(com), &id));
    long res = 0;
    GArray* answers = getIdAnswers_question(q);

    size_t tmp;
    size_t total;
    size_t scr;
    size_t owner_id;
    PROFILE p;
    size_t rep;

    //Setting up first values
    size_t id_ans = g_array_index(answers, size_t, 0);
    ANSWER a = getAnswer_post(g_hash_table_lookup(getPosts_TAD(com), &id_ans));       
    if(a != NULL){
        scr      = getScore_answer(a);
        //long comt   = getN_Comments_answer(a);
        owner_id = getOwnerId_answer(a);
        p        = g_hash_table_lookup(getProfiles_TAD(com), &owner_id);
        rep      = getReputation_profile(p);

        tmp   = (scr * 0.45) + (rep * 0.25) + (scr * 0.2) + (rep * 0.1);
        res   = getID_answer(a);
        total = tmp;
    }
    
    for(int i = 1; i < answers->len; i++){
        id_ans = g_array_index(answers, long, i);
        a = getAnswer_post(g_hash_table_lookup(getPosts_TAD(com), &id_ans));       
        if(a != NULL){
            scr      = getScore_answer(a);
            //long comt   = getN_Comments_answer(a);
            owner_id = getOwnerId_answer(a);
            p        = g_hash_table_lookup(getProfiles_TAD(com), &owner_id);
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


//QUERY 3
LONG_pair total_posts(TAD_community com, Date begin, Date end){
    LONG_pair res; // create_long_pair(0,0);

    TARDIS ord_posts = getTARDIS_TAD(com);



    return res;
}


typedef struct id_date {
    Date begin;
    long id;
} ID_DATE;

//QUERY 7
LONG_list most_answered_questions(TAD_community com, char* word, int N){
    LONG_list res = create_list(N);
    long i;
    GArray *dateB = g_array_new(FALSE, FALSE, sizeof(ID_DATE));

    GArray a = com->question_awnsers;
    while(N > 0){
    //Verificacao null?
        int tmp = g_array_index(a, QUESTION_ANWSER, 0)->n_awnser;
        ID_DATE new;
        for(i = 0; i < a->len;i++){
            if(g_array_index(a)->n_awnser > tmp){
                tmp = t_array_index(a, QUESTION_ANSWER, i)->n_awnser;
                new.begin = t_array_index(a, QUESTION_ANSWER, i)->start;
                new.id    = t_array_index(a, QUESTION_ANSWER, i)->question->id;
            }
        }
        append_val(dateB, new);

        N--;
    }

}


*/