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

    STR_pair ret;

    if(post_ptr != NULL){
        if(getType_post(post_ptr) == 1){ //question
            ret = get_info_from_post(com, getQuestion_post(post_ptr));
        }else{
            long parent_id = getParentId_answer(getAnswer_post(post_ptr));
            post_ptr = g_hash_table_lookup(getPosts_TAD(com), &parent_id);
            ret = get_info_from_post(com, getQuestion_post(post_ptr));
        }
    }

    return ret=0;
}
//END QUERY nº1


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

long better_answer(TAD_community com, long id){
    QUESTION q = getQuestion_post(g_hash_table_lookup(getPosts_TAD(com), &id));
    long res = 0;
    GArray* answers = getIdAnswers_question(q);

    int tmp;
    int total;
    int scr;
    long owner_id;
    PROFILE p;
    long rep;

    //Setting up first values
    long id_ans = g_array_index(answers, long, 0);
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
