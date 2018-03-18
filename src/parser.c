#include <stdio.h>
#include <libxml/SAX.h>
#include <libxml/parser.h>
#include <libxml/parserInternals.h>
#include <glib.h>


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

 void startElement(void* user_data, const xmlChar *fullname, const xmlChar **attrs) {
  GPtrArray* garray =  (GPtrArray*)user_data; // cast para o tipo da nossa estrutura

  if(!xmlStrcasecmp(fullname, (const xmlChar*)"posts"))
   printf("\n\n%s\n\n", fullname); // testar se estamos no posts

  while (attrs && *attrs) {
    xmlChar* s = xmlStrdup(attrs[1]); // passar de const xmlChar* para xmlChar*
    g_ptr_array_add(garray, s); // por na nossa estrutura

    attrs = &attrs[2]; // avançar para o proximo atributo
 }
}



int parse(const char* xml_path) {
  GPtrArray * garray = g_ptr_array_sized_new(1000);
  g_ptr_array_set_free_func(garray, xmlFree); // função para limpar os elementos do array

  xmlSAXHandler handler = {0};

  handler.initialized = XML_SAX2_MAGIC;
  handler.startElement = startElement;

  handler.warning = error;
  handler.error = error;
  handler.fatalError = error;


  int ctxt;
  ctxt = xmlSAXUserParseFile(&handler, garray, xml_path);

xmlCleanupParser(); // Limpar o parser
g_ptr_array_free (garray, TRUE); // Limpar o array
return ctxt;
}
