#include <stdio.h>
#include <libxml/SAX.h>
#include <libxml/parser.h>
#include <libxml/parserInternals.h>
#include <glib.h>
#include <string.h>

#include "profile.h"
#include "question.h"
#include <sys/types.h>
static void error(void *user_data, const char *msg, ...) {
    va_list args;

    va_start(args, msg);
    printf("\n%s\n", msg);
    va_end(args);
}

void startElementUsers(void* user_data, const xmlChar *fullname, const xmlChar **attrs) {
    
    GHashTable* hash = (GHashTable*)user_data;
    size_t need=0;
    
    xmlChar* about_me = NULL;
    xmlChar* name = NULL;
    long int id = 0;
    ssize_t reputation = 0;

    while (attrs && *attrs) {

        if (!xmlStrcasecmp(attrs[0], (const xmlChar*)"AboutMe")){
            about_me = xmlStrdup(attrs[1]);
            ++need;
        }

        if (!xmlStrcasecmp(attrs[0], (const xmlChar*)"DisplayName")){
            name  = xmlStrdup(attrs[1]);
            ++need;
        }

        if (!xmlStrcasecmp(attrs[0], (const xmlChar*)"Id")){
            id = strtol((const char*)attrs[1], NULL, 10);
            ++need;
        }

        if (!xmlStrcasecmp(attrs[0], (const xmlChar*)"Reputation")){
            reputation = strtol((const char*)attrs[1], NULL, 10);
            ++need;
        }

        if((need==3 && about_me==NULL) || need==4) break;
        attrs = &attrs[2]; // avançar para o proximo atributo
    }

    if (xmlStrcasecmp(fullname, (const xmlChar*)"Users")) {
        if (about_me == NULL) {
            about_me = malloc(sizeof(char));
            strcpy((char*)about_me, "");
            ++need;
        }

        PROFILE u = create_profile((char*)about_me, id, (char* )name, reputation);

        uint64_t *key = malloc(sizeof(uint64_t));
        *key = id + 1;
        g_hash_table_insert(hash, key, (gpointer)u);
    }
    xmlFree(about_me);
    xmlFree(name);

}


void startElementPosts(void* user_data, const xmlChar *fullname, const xmlChar **attrs) {

    GPtrArray* garray = (GPtrArray*)user_data;
    int long type = 0;
    size_t need=0;
    if (attrs)
        type = strtol((const char*)attrs[3], NULL, 10);


    xmlChar* start_tmp = NULL;
    int dia, mes, ano;
    Date start = NULL;
    size_t id=0,  owner_id=0;
    ssize_t score=0;
    // QUESTION
    xmlChar* title = NULL;
    xmlChar* tags = NULL;
    /////////////////////
    // ANSWER
    size_t parent_id=0;
    ////////////////////

    if (type == 1) {
        while (attrs && *attrs) {
            if (!xmlStrcasecmp(attrs[0], (const xmlChar*)"Id")){
                id = strtol((const char*)attrs[1], NULL, 10);
                ++need;
            }

            if (!xmlStrcasecmp(attrs[0], (const xmlChar*)"OwnerUserId")){
                owner_id = strtol((const char*)attrs[1], NULL, 10);
                ++need;
            }

            if (!xmlStrcasecmp(attrs[0], (const xmlChar*)"Score")){
                score = strtol((const char*)attrs[1], NULL, 10);
                ++need;
            }

            if (!xmlStrcasecmp(attrs[0], (const xmlChar*)"Title")){
                title  = xmlStrdup(attrs[1]);
                ++need;
            }

            if (!xmlStrcasecmp(attrs[0], (const xmlChar*)"Tags")){
                tags  = xmlStrdup(attrs[1]);
                ++need;
            }


            if (!xmlStrcasecmp(attrs[0], (const xmlChar*)"CreationDate")) {
                start_tmp  = xmlStrdup(attrs[1]);
                sscanf((char*)start_tmp, "%d-%d-%d", &ano, &dia, &mes);
                start = createDate(dia, mes, ano);
                ++need;
            }

            if((need==5 && tags==NULL) || need==6) break;
            attrs = &attrs[2]; // avançar para o proximo atributo
        }
        if (xmlStrcasecmp(fullname, (const xmlChar*)"Posts")) {

            if (tags == NULL) {
                tags = malloc(sizeof(char));
                strcpy((char*)tags, "");
            }

            QUESTION q = create_question(id, (char*)title, (char*)tags, owner_id, start, score);
            g_ptr_array_add(garray, q);
        }

        xmlFree(title);
        xmlFree(tags);
        xmlFree(start_tmp);
    }
    if (type == 2) {
        while (attrs && *attrs) {
            if (!xmlStrcasecmp(attrs[0], (const xmlChar*)"Id")){
                id = strtol((const char*)attrs[1], NULL, 10);
                ++need;
            }

            if (!xmlStrcasecmp(attrs[0], (const xmlChar*)"OwnerUserId")){
                owner_id = strtol((const char*)attrs[1], NULL, 10);
                ++need;
            }

            if (!xmlStrcasecmp(attrs[0], (const xmlChar*)"Score")){
                score = strtol((const char*)attrs[1], NULL, 10);
                ++need;
            }

            if (!xmlStrcasecmp(attrs[0], (const xmlChar*)"ParentId")){
                parent_id  = strtol((const char*)attrs[1], NULL, 10);
                ++need;
            }

            if (!xmlStrcasecmp(attrs[0], (const xmlChar*)"CreationDate")) {
                start_tmp  = xmlStrdup(attrs[1]);
                sscanf((char*)start_tmp, "%d-%d-%d", &ano, &dia, &mes);
                start = createDate(dia, mes, ano);
                ++need;
            }

            if(need==5) break;
            attrs = &attrs[2]; // avançar para o proximo atributo
        }
        if (xmlStrcasecmp(fullname, (const xmlChar*)"Posts")) {

            ANSWER a = create_answer(parent_id, owner_id, id, start, score);
            g_ptr_array_add(garray, a);
        }

        xmlFree(title);
        xmlFree(tags);
        xmlFree(start_tmp);
    }
}


int parse(const char* xml_path, void* user_data, size_t code) {
    int ctxt;
    xmlSAXHandler handler = {0};

    if (code == 0)
        handler.startElement = startElementUsers;

    if (code == 1)
        handler.startElement = startElementPosts;


    handler.warning = error;
    handler.error = error;
    handler.fatalError = error;


    ctxt = xmlSAXUserParseFile(&handler, user_data, xml_path);

    xmlCleanupParser();
    return ctxt;
}

int multiParse(const char* xml_path, void* user_data) {
    int users, posts;
    size_t pathLen = strlen(xml_path);
    pathLen += 10; // file.xml always 5 + 4 (.xml)
    char usersPath[pathLen], postsPath[pathLen];

    strcpy(usersPath, xml_path);
    strcat(usersPath, "/Users.xml");
    users = parse(usersPath, user_data, 0);

    strcpy(postsPath, xml_path);
    strcat(postsPath, "/Posts.xml");
    posts = parse(postsPath, user_data, 1);

    return users && posts;
}
