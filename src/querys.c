#include "date.h"
#include "user.h"
#include "pair.h"
#include "list.h"

#include "post.h"
#include "profile.h"

#include <stdlib.h>
#include "interface.h"
#include <glib.h>
#include <gmodule.h>

//QUERY nº1
gboolean finder(gpointer key, gpointer value, gpointer user_data){
    return g_int_64_equal(user_data, key);
}


STR_pair get_info_from_post(TAD_community com, POST p){
    char* titulo;
    char* name;

    titulo = getTitle_question(p->(union content).q);

    guint owner_ptr = g_int64_hash(getOwner_id_question(p->content.q));
    
    gpointer profile_ptr = g_hash_table_find(com->profiles, (GHRFunc)finder(owner_ptr), NULL);

    if(profile_ptr != NULL){
        PROFILE p = (PROFILE) profile_ptr;
        name = getName_profile(p);
    }


    STR_pair ret = create_str_pair(name, titulo);

    return ret;
}


STR_pair info_from_post(TAD_community com, long id){
    guint user_data = g_int64_hash(id);
    gpointer post_ptr = g_hash_table_find(com->posts, (GHRFunc)finder(user_data), NULL);

    POST ptr1;
    STR_pair ret;

    if(post_ptr != NULL){
        ptr1 = (POST) post_ptr;
        if(ptr1->type == 1){
            ret = get_info_from_post(com, ptr1);
        }else{
            guint owner_ptr = g_int64_hash(getParent_id_answer(ptr1->content.a));
            post_ptr = g_hash_table_find(com->posts, (GHRFunc)finder(owner_ptr), NULL);
            ptr1 = (POST) post_ptr;
            ret = get_info_from_post(com, ptr1);
        }
    }

    return ret;
}



/*//QUERY nº2
LONG_list top_most_active(TAD_community com, int N){
    LONG_list res = create_list(N);

    GHashTableIter i;
    gpointer key, value;

    for(int i= 0; i < N; i++){
        g_hash_table_iter_next (i, com->users);
        //Conseguir o primeiro numero de posts da pessoa no primeiro index da hash
        size_t tmp_total;
        long tmp_id; //dara warning por termos size_t na estrutura?

        while(g_hash_table_iter_next(&i, &key, &value)){
            size_t aux = value->id_questions->len + value->id_awnsers->len;
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

    return res;
}


//QUERY 5
USER get_user_info(TAD_community com, long id){
    USER res;
    char *short_bio;
    long *post_history;
    size_t id;

    if(gpointer item_prt = g_hash_table_lookup(com->users, id) != NULL){
        //works??
        short_bio = "Name: " + item_ptr->name + "Bio: " + item_ptr->about_me;
        id = item_ptr->id;
    }


    //Perante os dois arrays de id_questions e id_awnsers, como verifica los por ordem cronologica inversa? (sem destincao)
    //Maybe guardar, em vez de um array, uma struct que tem id e tipo_post (1/2), assim estariam por ordem cronologica e
    //seria mais eficiente procurar

}

typedef struct id_date {
    Date begin;
    size_t id;
} ID_DATE;

//QUERY 7
LONG_list most_answered_questions(TAD_community com, char* word, int N){
    LONG_list res = create_list(N);
    size_t i;
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