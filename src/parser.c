#include <libxml/parser.h>
#include <libxml/parserInternals.h>
#include <glib.h>
#include "profile.h"
#include "post.h"
#include "question.h"
#include "answer.h"
#include "mydate.h"
#include "main_struct.h"
#include <string.h>

static int attr2int_user(const xmlChar* attr){
    if(attr[0] == 'I') // Id
        return 0;
    if(attr[0] == 'R') // Reputation
        return 1;
    if(attr[0] == 'D' && attr[1] == 'i') // DisplayName
        return 2;
    if(attr[0] == 'A' && attr[1] == 'b') // About me
        return 3;

    return -1;
}

static int attr2int_post(const xmlChar* attr){
    if(attr[0] == 'I') // Id
        return 0;
    if(attr[0] == 'T' && attr[1] == 'a') // Tags
        return 1;
    if(attr[0] == 'S') // Score
        return 2;
    if(attr[0] == 'T' && attr[1] == 'i') // Title
        return 3;
    if(attr[0] == 'P' && attr[1] == 'a') // ParentId
        return 4;
    if(attr[0] == 'A' && attr[1] == 'n') // AnswerCount
        return 5;
    if(attr[0] == 'O' && attr[5] == 'U') // OnwerUserId
        return 6;
    if(attr[0] == 'C' && attr[6] == 'o') // CreationDate
        return 7;
    if(attr[0] == 'C' && attr[6] == 't') // CommentCount
        return 8;
    return -1;
}

static void error(void* user_data, const char* msg, ...){
    va_list args;
    (void)user_data;
    va_start(args, msg);
    printf("\n%s\n", msg);
    va_end(args);
}

static void startElementUsers(void* user_data, const xmlChar* fullname, const xmlChar** attrs){

    TAD_community com = (TAD_community) user_data;


    char* about_me = NULL;
    char* name = NULL;
    long int id = 0;
    int reputation = 0;

    while(attrs && *attrs){
        int lvl = attr2int_user(*attrs);
        switch(lvl){
            case 0 :
                id = strtol((char*) attrs[1], NULL, 10);
                break;
            case 1 :
                reputation = (int) strtol((const char*) attrs[1], NULL, 10);
                break;
            case 2 :
                name = (char*) attrs[1];
                break;
            case 3 :
                about_me = (char*) attrs[1];
                break;
            default :
                break;
        }
        attrs = &attrs[2];
    }

    if(fullname[0] == 'r'){
        PROFILE u = create_profile(about_me, id, name, reputation);
        insertProfile_TAD(com, u, id);
    }

    //xmlFree(about_me);
    //xmlFree(name);
}

static void startElementPosts(void* user_data, const xmlChar* fullname, const xmlChar** attrs){
    TAD_community com = (TAD_community) user_data;


    long type = 0;
    if(attrs){
        type = strtol((const char*) attrs[3], NULL, 10);
        if(type != 1 && type != 2) return;
    }
    char* start_tmp = NULL;
    int dia, mes, ano, hora, minuto, segundo, milisegundo;
    MyDate start = NULL;
    long id = 0, owner_id = 0;
    int score = 0;
    // QUESTION
    char* title = NULL;
    char* tags = NULL;
    long nquestions = 0;
    long comments = 0;
    /////////////////////
    // ANSWER
    long parent_id = 0;
    ////////////////////

    while(attrs && *attrs){
        int lvl = attr2int_post(*attrs);
        switch(lvl){
            case 0 :
                id = strtol((const char*) attrs[1], NULL, 10);
                break;
            case 1 :
                tags = (char*) (attrs[1]);
                break;
            case 2 :
                score = atoi((const char*) attrs[1]);
                break;
            case 3 :
                title = (char*) (attrs[1]);
                break;
            case 4 :
                parent_id = strtol((const char*) attrs[1], NULL, 10);
                break;
            case 5 :
                nquestions = strtol((const char*) attrs[1], NULL, 10);
                break;
            case 6 :
                owner_id = strtol((const char*) attrs[1], NULL, 10);
                break;
            case 7 :
                start_tmp = (char*) (attrs[1]);
                sscanf(start_tmp, "%d-%d-%dT%d:%d:%d.%d", &ano, &mes, &dia, &hora, &minuto, &segundo, &milisegundo);
                start = create_date(milisegundo, segundo, minuto, hora, dia, mes, ano);
                break;
            case 8 :
                comments = strtol((const char*) attrs[1], NULL, 10);
            default:
                break;
        }
        attrs = &attrs[2]; // avançar para o proximo atributo
    }

    if(fullname[0] == 'r'){

        if(type == 1){

            QUESTION q = create_question(id, title, tags, owner_id, start, score, nquestions, comments);
            POST p = create_post(type, q, NULL);
            insertQuestion_TAD(com, q, id, owner_id, p, start);
        }

        if(type == 2){
            ANSWER a = create_answer(parent_id, owner_id, id, start, score, comments);
            POST p = create_post(type, NULL, a);
            insertAnswer_TAD(com, a, id, owner_id, parent_id, p, start);
        }


    }

    /*   g_free(title);
       g_free(tags);
       g_free(start_tmp);*/

}

static void startElementTags(void* user_data, const xmlChar* fullname, const xmlChar** attrs){
    (void)fullname;
    long id = 0; // 1
    char* tag_name = NULL; // 3
    if(!attrs) return;

    id = strtol((const char*) attrs[1], NULL, 10);
    tag_name = (char*) xmlStrdup(attrs[3]);
    insertTag_TAD((TAD_community) user_data, tag_name, id);
}

static int parse(const char* xml_path, void* user_data, long code){
    int ctxt;
    xmlSAXHandler handler = {0};

    if(code == 0)
        handler.startElement = startElementUsers;

    if(code == 1)
        handler.startElement = startElementPosts;

    if(code == 2)
        handler.startElement = startElementTags;

    handler.warning = error;
    handler.error = error;
    handler.fatalError = error;

    ctxt = xmlSAXUserParseFile(&handler, user_data, xml_path);

    xmlCleanupParser();
    return ctxt;
}

static int multiParse(const char* xml_path, void* user_data){
    int users, posts, tags;
    long pathLen = strlen(xml_path);
    pathLen += 10; // file.xml always 5 + 4 (.xml)
    char usersPath[pathLen], postsPath[pathLen], tagsPath[pathLen];

    strcpy(usersPath, xml_path);
    strcat(usersPath, "/Users.xml");
    users = parse(usersPath, user_data, 0);

    strcpy(postsPath, xml_path);
    strcat(postsPath, "/Posts.xml");
    posts = parse(postsPath, user_data, 1);

    strcpy(tagsPath, xml_path);
    strcat(tagsPath, "/Tags.xml");
    tags = parse(tagsPath, user_data, 2);

    return users || posts || tags;
}

TAD_community load(TAD_community com, char* dump_path){
    multiParse(dump_path, com);
    setNTags_TAD(com);
    return com;
}
