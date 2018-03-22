#include <stdio.h>
#include <libxml/SAX.h>
#include <libxml/parser.h>
#include <libxml/parserInternals.h>
#include <glib.h>
#include <string.h>

/*

  XML SAX Insanity.

  Message to professors, classmates and the compiler:


  If you want to understand this, you have to hit a blunt.
  I don't care if you're at work. Roll a fat one and smoke it. Right now.

  If your boss questions this, feel free to tell him to contact me. I'll explain how crucial THC is for this shit.


  Once you're done trying to 'optimize' this routine, and have realized what a terrible mistake that was,
  please increment the following counter as a warning for the next guy:

  total_hours_wated_here = 42
*/

static void error(void *user_data, const char *msg, ...){
  va_list args;

  va_start(args, msg);
  printf("\n%s\n", msg);
  va_end(args);
}

 void startElementUsers(void* user_data, const xmlChar *fullname, const xmlChar **attrs) {
  GPtrArray* garray =  (GPtrArray*)user_data; // cast para o tipo da nossa estrutura

  if(!xmlStrcasecmp(fullname, (const xmlChar*)"posts"))
   printf("\n\n%s\n\n", fullname); // testar se estamos no posts

  while (attrs && *attrs) {
    xmlChar* s = xmlStrdup(attrs[1]); // passar de const xmlChar* para xmlChar*
    g_ptr_array_add(garray, s); // por na nossa estrutura

    attrs = &attrs[2]; // avançar para o proximo atributo
 }
}



int parse(const char* xml_path, void* user_data){

 // handler.initialized = XML_SAX2_MAGIC;
  int ctxt;
  int i;
  char** names = {
    "Users.xml",
    "Posts.xml",
    "Votes.xml"
  };
  char buffer[100];

  for(i=0; i<2;i++){
    xmlSAXHandler handler = {0};

    handler.startElement = startElementUsers;

    handler.warning = error;
    handler.error = error;
    handler.fatalError = error;


    strcat(buffer,names[1]);
    ctxt = xmlSAXUserParseFile(&handler,  user_data, xml_path);
    xmlCleanupParser(); // Limpar o parser
  }

  return 0;
}
