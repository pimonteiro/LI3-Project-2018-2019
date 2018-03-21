#ifndef __PARSER_H__
#define __PARSER_H__

#include <libxml/parserInternals.h>

void xmlSAX2StartElement(void* user_data, const xmlChar *fullname, const xmlChar **attrs);
int parse(const char* xml_path);

#endif