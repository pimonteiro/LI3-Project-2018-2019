#include <stdio.h>
#include <libxml/SAX.h>
#include <libxml/parser.h>
#include <libxml/parserInternals.h>
#include <glib.h>
#include <string.h>

#include "profile.h"
static void error(void *user_data, const char *msg, ...){
  va_list args;

  va_start(args, msg);
  printf("\n%s\n", msg);
  va_end(args);
}

void startElementUsers(void* user_data, const xmlChar *fullname, const xmlChar **attrs) {
  //GHashTable* hash = (GHashTable*)user_data;
  GPtrArray* garray = (GPtrArray*)user_data;
  xmlChar* about_me=NULL;
  xmlChar* name=NULL;
  long int id=0;
  ssize_t reputation=0;

  while (attrs && *attrs) {

    if(!xmlStrcasecmp(attrs[0], (const xmlChar*)"AboutMe"))
      about_me = xmlStrdup(attrs[1]);

    if(!xmlStrcasecmp(attrs[0], (const xmlChar*)"DisplayName"))
      name  = xmlStrdup(attrs[1]);

    if(!xmlStrcasecmp(attrs[0], (const xmlChar*)"Id"))
      id = strtol((const char*)attrs[1], NULL, 10);

    if(!xmlStrcasecmp(attrs[0], (const xmlChar*)"Reputation"))
      reputation = strtol((const char*)attrs[1], NULL, 10);

    attrs = &attrs[2]; // avançar para o proximo atributo
 }

    if(xmlStrcasecmp(fullname, (const xmlChar*)"Users")){
      if(about_me == NULL){
        about_me=malloc(sizeof(char));
        strcpy((char*)about_me,"");
      }

      PROFILE u = create_profile((char*)about_me, id, (char* )name, reputation);
      //uint64_t *mer_p = malloc(sizeof(uint64_t));

      //*mer_p=id;

      //g_hash_table_insert(hash, mer_p , (gpointer)u);
      g_ptr_array_add(garray, u);
    }
         xmlFree(about_me);
         xmlFree(name);

}


 void startElementPosts(void* user_data, const xmlChar *fullname, const xmlChar **attrs) {

  if(!xmlStrcasecmp(fullname, (const xmlChar*)"posts"))
   printf("\n\n%s\n\n", fullname); // testar se estamos no posts

  while (attrs && *attrs) {
    //xmlChar* s = xmlStrdup(attrs[1]); // passar de const xmlChar* para xmlChar*

    attrs = &attrs[2]; // avançar para o proximo atributo
 }
}


 void startElementVotes(void* user_data, const xmlChar *fullname, const xmlChar **attrs) {

  if(!xmlStrcasecmp(fullname, (const xmlChar*)"posts"))
   printf("\n\n%s\n\n", fullname); // testar se estamos no posts

  while (attrs && *attrs) {
     //xmlChar* s = xmlStrdup(attrs[1]); // passar de const xmlChar* para xmlChar*

    attrs = &attrs[2]; // avançar para o proximo atributo
 }
}
int parse(const char* xml_path, void* user_data, size_t code){
	int ctxt;
	xmlSAXHandler handler = {0};

	if(code == 0)
		handler.startElement = startElementUsers;

	if(code == 1)
		handler.startElement = startElementPosts;

	if(code == 2)
		handler.startElement = startElementVotes;


	handler.warning = error;
    	handler.error = error;
    	handler.fatalError = error;


	ctxt = xmlSAXUserParseFile(&handler, user_data, xml_path);

	xmlCleanupParser();
	return ctxt;
}

int multiParse(const char* xml_path, void* user_data){
	int users, posts, votes;
	size_t pathLen = strlen(xml_path);
	pathLen += 9; // file.xml always 5 + 4 (.xml)
	char usersPath[pathLen], postsPath[pathLen], votesPath[pathLen];

	strcpy(usersPath, xml_path);
	strcat(usersPath, "Users.xml");
	users = parse(usersPath, user_data, 0);

	strcpy(postsPath, xml_path);
	strcat(postsPath, "Posts.xml");
	posts = parse(xml_path, user_data, 1);

	strcpy(votesPath, xml_path);
	strcat(votesPath, "Votes.xml");
	votes = parse(xml_path, user_data, 2);

	return users && posts && votes;
}
