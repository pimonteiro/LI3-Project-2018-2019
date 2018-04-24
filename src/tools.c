#include <glib.h>
#include <stdio.h>
#include "profile.h"
#include "post.h"
#include "tardis.h"
#include "mydate.h"
#include "main_struct.h"
#include "interface.h"
#include "tools.h"


void print_question(QUESTION q){
    printf("-------------------\n");
    printf("ID: %ld\n", getId_question(q));
    printf("Titulo: %s\n", getTitle_question(q));
    printf("Tags: %s\n", getTags_question(q));
    printf("OwnerID: %ld\n", getOwnerId_question(q));
    printf("N_answers: %ld\n", getNanswers_question(q));
    printf("Score: %d\n", getScore_question(q));
    GArray* answers = getIdAnswers_question(q);
    printf("Array Answers:\n");
    for(int i = 0; i < (int) answers->len; i++){
        printf("\a%d --> %ld\n", i, g_array_index(answers, long, i));
    }
    MyDate d = getCreationDate_question(q);
    printf("Data: %d/%d/%d\n\n", get_dia(d), get_mes(d), get_ano(d));
}

void print_answer(ANSWER a){
    printf("-------------------\n");
    printf("ID: %ld\n", getID_answer(a));
    printf("OwnerID: %ld\n", getOwnerId_answer(a));
    printf("ParentID: %ld\n", getParentId_answer(a));
    printf("Score: %d\n", getScore_answer(a));
    MyDate d = getDate_answer(a);
    printf("Data: %d/%d/%d\n\n", get_dia(d), get_mes(d), get_ano(d));
}

void get_all_posts(TAD_community com){
    int b_day, b_month, b_year, e_day, e_month, e_year, type;
    printf("Beginning date: dd/mm/yyyy\n");
    scanf("%d/%d/%d", &b_day, &b_month, &b_year);
    printf("Ending date: dd/mm/yyyy\n");
    scanf("%d/%d/%d", &e_day, &e_month, &e_year);

    printf("1 - QUESTION || 2 - ANSWER\n");
    scanf("%d\n", &type);
    MyDate begin = create_date(0, 0, 0, 0, b_day, b_month, b_year);
    MyDate end = create_date(0, 0, 0, 0, e_day, e_month, e_year);

    GSequence* seq = getFromToF_TAD(com, begin, end, type, NULL);

    int l_seq = g_sequence_get_length(seq);
    for(int i = 0; i < l_seq; i++){
        if(type == 1)
            print_question(g_sequence_get(g_sequence_get_iter_at_pos(seq, i)));
        if(type == 2)
            print_answer(g_sequence_get(g_sequence_get_iter_at_pos(seq, i)));
    }
}

void print_post(TAD_community com, long id){
    POST p = getPost_TAD(com, id);
    if(getType_post(p) == 1)
        print_question(getQuestion_post(p));
    else
        print_answer(getAnswer_post(p));
}

void get_single_post(TAD_community com){
    long id;
    printf("ID: ");
    scanf("%ld\n", &id);
    print_post(com, id);
}

void tool_posts(){
    int choice;

    TAD_community com = init();
    load(com, "/home/pimonteiro/Desktop/ubuntu");

    do{
        printf("0 - Get single Post\n");
        printf("1 - Get all Posts between two dates\n");
        printf("Other to exit\n");
        scanf("%d", &choice);

        if(choice == 1)
            get_all_posts(com);
        else if(choice == 0)
            get_single_post(com);
    }while(choice == 1 || choice == 0);
}

void print_user(TAD_community com, long id){
    PROFILE p = getProfile_TAD(com, id);
    if(p == NULL) return;
    printf("--------------\n");
    printf("ID: %ld\n", getId_profile(p));
    printf("Name: %s\n", getName_profile(p));
    printf("About me: %s\n", getAboutMe_profile(p));
    printf("N_posts: %ld\n", getNposts_profile(p));
    printf("Reputation: %d\n", getReputation_profile(p));
    //Falta POSTS
    printf("--------------\n\n");
}

void tool_users(){
    TAD_community com = init();
    load(com, "/home/pimonteiro/Desktop/ubuntu");
    long id;
    do{
        printf("ID: (0 to exit)\n");
        scanf("%ld\n", &id);
        if(id != 0) print_user(com, id);
    }while(id != 0);
}