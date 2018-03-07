#include <stdio.h>
#include <libxml/SAX.h>
#include <libxml/parser.h>
#include <libxml/parserInternals.h>
#include <glib.h>


/**Função que é chamada quando um elemento é encontrado
r* @ void* user_data: apontador para a nossa estrutura de dados
 * @ const xmlChar* fullname: nome do elemento encontrado
 * @ const xmlChar** attrs: atributos dos elementos encontrados (o nossa informação)
 *
 */
void xmlSAX2StartElement(void* user_data, const xmlChar *fullname, const xmlChar **attrs) {
  GPtrArray* garray =  (GPtrArray*)user_data; // cast para o tipo da nossa estrutura

  if(!xmlStrcasecmp(fullname, (const xmlChar*)"posts"))
   printf("\n\n%s\n\n", fullname); // testar se estamos no posts

  // verifica se existe atributo
  while (attrs && *attrs) {
    xmlChar* s = xmlStrdup(attrs[1]); // passar de const xmlChar* para xmlChar*
    g_ptr_array_add(garray, s); // por na nossa estrutura

    attrs = &attrs[2]; // avançar para o proximo atributo
 }
}

void my_error(void* user_data, const char* msg,...){
  va_list args;

  va_start(args, msg);
  g_logv("XML", G_LOG_LEVEL_CRITICAL, msg, args);
  va_end(args);

}
/**Função que faz parse aos ficheiros :D
 * Recebe o caminho do xml
 */
int parse(const char* xml_path) {
  /** A nossa estrutura:
   *  Array de apontadores do Glib
   *  Assumo que tenho 500 pointers pelo menos
   *    fica mais rapido
   */
  GPtrArray * garray = g_ptr_array_sized_new(1000);
  g_ptr_array_set_free_func(garray, xmlFree); // função para limpar os elementos do array

  // Estrutura que guarda o estado do XML e trata de o processar
  xmlSAXHandler handler = {0};
  // Atribuir a função que é chamada quando um elemento é encontrado
  handler.startElement = xmlSAX2StartElement;
  handler.error = my_error;


  int ctxt;
  // Carregar o ficheiro
  ctxt = xmlSAXUserParseFile(&handler, garray, xml_path);

//char* s = g_ptr_array_index(garray, 99);
//printf("retrieving %s\n", s);


xmlCleanupParser(); // Limpar o parser
g_ptr_array_free (garray, TRUE); // Limpar o array
return ctxt;
}
