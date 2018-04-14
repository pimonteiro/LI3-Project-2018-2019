#include <glib.h>
#include <stdio.h>
#include "profile.h"
#include "post.h"
#include "tardis.h"
#include "mydate.h"
#include "main_struct.h"
#include "interface.h"

#define error(query, test_case) printf("QUERY %d: %d ----- FAILED\n", query, test_case)
#define success(query, test_case) printf("QUERY %d: %d ----- SUCCESS\n", query, test_case)
#define start(query) printf("-------------START QUERY %d-------------\n", query)
#define end(query) printf("-------------END QUERY %d-------------\n\n", query)


int query_5_test_cases_aux(USER a, char* text, long l_posts[10], int id_case){
    if(a == NULL){
        error(5,id_case);
        return 1;
    }
    if(strcmp(get_bio(a), text)){
        error(5,id_case);
        return 1;
    }

    /* for(int i = 0; i < 10; i++){
        if(l_posts[i] != posts[i]){
            error(5,id_case);
            return 1;
    }
    */

   return 0;
}


void query5_test_cases(TAD_community com){
    start(5);

    USER a;
    char* text = "";
    long* l_posts;
    
    a = get_user_info(com, 7);
    text = "Name: \"Jonas\" Bio: \"&lt;p&gt;I'm a computer science student.&lt;/p&gt;&#xA;\"\n";
    l_posts = get_10_latest_posts(a);
    if(!query_5_test_cases_aux(a, text, l_posts, 1)) success(5,1);

    free_user(a);
    
    a = get_user_info(com, 114); //Nao existe
    if(a == NULL) success(5,2);

    free_user(a);

    a = get_user_info(com, 9999999); //Nao existe e vai alem do tamanho
    if(a == NULL) success(5,3);

    free_user(a);

    a = get_user_info(com, -1); //Negativo
    text = "Name: \"Community\" Bio: \"&lt;p&gt;Hi, I'm not really a person.&lt;/p&gt;&#xA;&#xA;&lt;p&gt;I'm a background process that helps keep this site clean!&lt;/p&gt;&#xA;&#xA;&lt;p&gt;I do things like&lt;/p&gt;&#xA;&#xA;&lt;ul&gt;&#xA;&lt;li&gt;Randomly poke old unanswered questions every hour so they get some attention&lt;/li&gt;&#xA;&lt;li&gt;Own community questions and answers so nobody gets unnecessary reputation from them&lt;/li&gt;&#xA;&lt;li&gt;Own downvotes on spam/evil posts that get permanently deleted&lt;/li&gt;&#xA;&lt;li&gt;Own suggested edits from anonymous users&lt;/li&gt;&#xA;&lt;li&gt;&lt;a href=&quot;http://meta.stackexchange.com/a/92006&quot;&gt;Remove abandoned questions&lt;/a&gt;&lt;/li&gt;&#xA;&lt;/ul&gt;&#xA;\"";
    l_posts = get_10_latest_posts(a);
    if(!query_5_test_cases_aux(a, text, l_posts, 4)) success(5,4);

    free_user(a);
    
    end(5);
}

int query_1_test_cases_aux(STR_pair a, char* fst_true, char* snd_true, int id_case){
    if(a == NULL){
        error(1,id_case);
        return 1;
    }

    if(strcmp(fst_true, get_fst_str(a))){
        error(1,id_case);
        return 1;
    }

    if(strcmp(snd_true, get_snd_str(a))){
        error(1,id_case);
        return 1;
    }

    return 0;
}

void query1_test_cases(TAD_community com){
    start(1);

    STR_pair a;
    char* fst_true;
    char* snd_true;

    a = info_from_post(com, 16); //Existe e é pergunta
    fst_true = "\"How do I stop from getting notified twice when I get a text to my Google Voice number?\"";
    snd_true = "\"Ravi Vyas\"";
    if(!query_1_test_cases_aux(a, fst_true, snd_true, 1)) success(1,1);

    free_str_pair(a);

    a = info_from_post(com, 15); //Existe e é resposta
    fst_true = "\"How do I keep my wi-fi on in sleep mode\"";
    snd_true = "\"danivovich\"";
    if(!query_1_test_cases_aux(a, fst_true, snd_true, 2)) success(1,2);

    free_str_pair(a);

    a = info_from_post(com, 18); //Nao existe
    if(a == NULL) success(1,3);
    
    free_str_pair(a);

    a = info_from_post(com, -9); //Existe e é resposta
    if(a == NULL) success(1,4);

    free_str_pair(a);

    end(1);

}

//Implementar load time and querys time
int unit_test(){
    printf("-------------------------------------- C CODE TESTER --------------------------------------\n\n");
    
    TAD_community com = init();

    load(com, "/home/pimonteiro/Desktop/android");
    
    query1_test_cases(com);
    
    
    query5_test_cases(com);
    
    //LONG_list a = both_participated(com, 136, 52, 1);
    Date begin = createDate(15, 2, 2010);
    Date end   = createDate(15, 6, 2010);

    

    STR_pair b = info_from_post(com, 5);
    LONG_list a = most_answered_questions(com, 5, begin, end);
    //long list = get_list(a,0);
    //long list2 = get_list(a,1);
    //printf("%ld ------ %ld\n", list, list2); 
    com = clean(com);

  	return 0;
}