//Query nº2
LONG_list top_most_active(TAD_community com, int N){
    LONG_list res = create_list(N);
    
    GHashTableIter i;
    gpointer key, value;
    
    for(int i= 0; i < N; i++){
        g_hash_table_iter_next (&i, com->users);
        //Conseguir o primeiro numero de posts da pessoa no primeiro index da hash
        size_t tmp_total; 
        long tmp_id; //dara warning por termos size_t na estrutura?

        while(g_hash_table_iter_next(&iter, &key, &value)){
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
    DATE begin;
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
                tmp = t_array_index(a, QUESTION_AWNSER, i)->n_awnser;
                new.begin = t_array_index(a, QUESTION_AWNSER, i)->start;
                new.id    = t_array_index(a, QUESTION_AWNSER, i)->question->id;
            }
        }
        append_val(dateB, new);        
        
        N--;
    }
    
}


