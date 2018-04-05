#include <libxml/parser.h>
#include <libxml/parserInternals.h>
#include <glib.h>
#include "profile.h"
#include "post.h"
#include "question.h"
#include "interface.h"
#include "mydate.h"
#include "tardis.h"
#include <sys/types.h>
#include "main_struct.h"


static void error(void *user_data, const char *msg, ...) {
    va_list args;

    va_start(args, msg);
    printf("\n%s\n", msg);
    va_end(args);
}

void startElementUsers(void* user_data, const xmlChar *fullname, const xmlChar **attrs) {

    GHashTable* hash = getProfiles_TAD((TAD_community)user_data);


    xmlChar* about_me = NULL;
    xmlChar* name = NULL;
    long int id = 0;
    int reputation = 0;

    while (attrs && *attrs) {

        if (!xmlStrcasecmp(attrs[0], (const xmlChar*)"AboutMe")){
            about_me = xmlStrdup(attrs[1]);
        }

        if (!xmlStrcasecmp(attrs[0], (const xmlChar*)"DisplayName")){
            name  = xmlStrdup(attrs[1]);
        }

        if (!xmlStrcasecmp(attrs[0], (const xmlChar*)"Id")){
            id = strtol((const char*)attrs[1], NULL, 10);
        }

        if (!xmlStrcasecmp(attrs[0], (const xmlChar*)"Reputation")){
            reputation = strtol((const char*)attrs[1], NULL, 10);
        }

        attrs = &attrs[2];
    }

    if (xmlStrcasecmp(fullname, (const xmlChar*)"Users")) {
        if (about_me == NULL) {
            about_me = malloc(sizeof(char));
            strcpy((char*)about_me, "");
        }

        PROFILE u = create_profile((char*)about_me, id, (char* )name, reputation);
        gint64 *key = malloc(sizeof(gint64));
        *key = id;

        g_hash_table_insert(hash, key, (gpointer)u);
    }

    xmlFree(about_me);
    xmlFree(name);
}



void startElementPosts(void* user_data, const xmlChar *fullname, const xmlChar **attrs) {

    TAD_community com = (TAD_community)user_data;

    GHashTable* hash = getPosts_TAD(com);
    TARDIS type40 = getTARDIS_TAD(com);
    GHashTable* hash_users = getProfiles_TAD(com);


    long type = 0;
    if (attrs)
        type = strtol((const char*)attrs[3], NULL, 10);


    xmlChar* start_tmp = NULL;
    int dia, mes, ano, hora, minuto, segundo, milisegundo;
    MyDate start = NULL;
    long id=0,  owner_id=0;
    int score=0;
    // QUESTION
    xmlChar* title = NULL;
    xmlChar* tags = NULL;
    long nquestions=0;
    /////////////////////
    // ANSWER
    long parent_id=0;
    ////////////////////

    if (type == 1) {
        while (attrs && *attrs) {
            if (!xmlStrcasecmp(attrs[0], (const xmlChar*)"Id")){
                id = strtol((const char*)attrs[1], NULL, 10);
            }

            if (!xmlStrcasecmp(attrs[0], (const xmlChar*)"OwnerUserId")){
                owner_id = strtol((const char*)attrs[1], NULL, 10);
            }

            if (!xmlStrcasecmp(attrs[0], (const xmlChar*)"Score")){
                score = atoi((const char*)attrs[1]);
            }

            if (!xmlStrcasecmp(attrs[0], (const xmlChar*)"AnswerCount")){
                nquestions = strtol((const char*)attrs[1], NULL, 10);
            }
            if (!xmlStrcasecmp(attrs[0], (const xmlChar*)"Title")){
                title  = xmlStrdup(attrs[1]);
            }

            if (!xmlStrcasecmp(attrs[0], (const xmlChar*)"Tags")){
                tags  = xmlStrdup(attrs[1]);
            }


            if (!xmlStrcasecmp(attrs[0], (const xmlChar*)"CreationDate")) {
                start_tmp  = xmlStrdup(attrs[1]);
                sscanf((char*)start_tmp, "%d-%d-%dT%d:%d:%d.%d", &ano, &mes, &dia, &hora, &minuto, &segundo, &milisegundo);
                start = create_date(milisegundo, segundo, minuto, hora, dia, mes, ano);
            }

            attrs = &attrs[2]; // avançar para o proximo atributo
        }

        if (xmlStrcasecmp(fullname, (const xmlChar*)"Posts")) {

            if (tags == NULL) {
                tags = malloc(sizeof(char));
                strcpy((char*)tags, "");
            }

            QUESTION q = create_question(id, (char*)title, (char*)tags, owner_id, start, score, nquestions);
            POST p = create_post(type, q, NULL);

            gint64 *key = malloc(sizeof(gint64));
            *key = id;


            g_hash_table_insert(hash, key, (gpointer)p);

            insertQuestion(type40, q, ano, mes, dia);

            PROFILE prof = (PROFILE)g_hash_table_lookup(hash_users, &owner_id);
            if(prof != NULL){
              insertLastest_profile(prof, p);
              increaseNposts_profile(prof);
            }
        }

        xmlFree(title);
        xmlFree(tags);
        xmlFree(start_tmp);
    }

    if (type == 2) {
        while (attrs && *attrs) {
            if (!xmlStrcasecmp(attrs[0], (const xmlChar*)"Id")){
                id = strtol((const char*)attrs[1], NULL, 10);
            }

            if (!xmlStrcasecmp(attrs[0], (const xmlChar*)"OwnerUserId")){
                owner_id = strtol((const char*)attrs[1], NULL, 10);
            }

            if (!xmlStrcasecmp(attrs[0], (const xmlChar*)"Score")){
                score = atoi((const char*)attrs[1]);
            }

            if (!xmlStrcasecmp(attrs[0], (const xmlChar*)"ParentId")){
                parent_id  = strtol((const char*)attrs[1], NULL, 10);
            }

            if (!xmlStrcasecmp(attrs[0], (const xmlChar*)"CreationDate")) {
                start_tmp  = xmlStrdup(attrs[1]);
                sscanf((char*)start_tmp, "%d-%d-%dT%d:%d:%d.%d", &ano, &mes, &dia, &hora, &minuto, &segundo, &milisegundo);
                start = create_date(milisegundo, segundo, minuto, hora, dia, mes, ano);
            }

            attrs = &attrs[2]; // avançar para o proximo atributo
        }
        if (xmlStrcasecmp(fullname, (const xmlChar*)"Posts")) {

            ANSWER a = create_answer(parent_id, owner_id, id, start, score);
            POST p = create_post(type, NULL, a);
            gint64 *key = malloc(sizeof(gint64));
            *key = id;

            g_hash_table_insert(hash, key, (gpointer)p);
            insertAnswer(type40, a, ano, mes, dia);


            PROFILE prof = (PROFILE)g_hash_table_lookup(hash_users, &owner_id);
            if(prof != NULL){
             // insertLastest_profile(prof, p);
              increaseNposts_profile(prof);
            }

            POST q =(POST)g_hash_table_lookup(hash, &parent_id);
            if(q != NULL)
                setAnswers_array_question(getQuestion_post(q), (long)id);
        }
        xmlFree(title);
        xmlFree(tags);
        xmlFree(start_tmp);
    }
}


void startElementTags(void* user_data, const xmlChar *fullname, const xmlChar **attrs) {
    long id = 0; // 1
    char* tag_name = NULL; // 3
    if(!attrs) return;
    GHashTable* hash = getTags_TAD((TAD_community)user_data);
    id = strtol((const char*)attrs[1], NULL, 10);
    tag_name = (char*)xmlStrdup(attrs[3]);
    g_hash_table_insert(hash, tag_name, (gpointer)id);

}

static int parse(const char* xml_path, void* user_data, long code) {
    int ctxt;
    xmlSAXHandler handler = {0};

    if (code == 0)
        handler.startElement = startElementUsers;

    if (code == 1)
        handler.startElement = startElementPosts;

    if (code == 2)
        handler.startElement = startElementTags;


    handler.warning = error;
    handler.error = error;
    handler.fatalError = error;


    ctxt = xmlSAXUserParseFile(&handler, user_data, xml_path);

    xmlCleanupParser();
    return ctxt;
}

static int multiParse(const char* xml_path, void* user_data) {
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
    tags = parse(postsPath, user_data, 2);


    return users || posts || tags;
}

TAD_community load(TAD_community com, char* dump_path){
    multiParse(dump_path, com);
    return com;
}
