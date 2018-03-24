#include <stdio.h>
#include <libxml/SAX.h>
#include <libxml/parser.h>
#include <libxml/parserInternals.h>
#include <glib.h>
#include <string.h>


static void error(void *user_data, const char *msg, ...){
  va_list args;

  va_start(args, msg);
  printf("\n%s\n", msg);
  va_end(args);
}

void startElementUsers(void* user_data, const xmlChar *fullname, const xmlChar **attrs) {

GHashTable* hash = (GHashTable*)user_data;

  if(!xmlStrcasecmp(fullname, (const xmlChar*)"posts"))
   printf("\n\n%s\n\n", fullname); // testar se estamos no posts

  while (attrs && *attrs) {
	xmlChar* tmp = xmlStrdup(attrs[1]);
	g_hash_table_replace(hash, (guint)0, tmp);
    attrs = &attrs[2]; // avançar para o proximo atributo
 }
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
