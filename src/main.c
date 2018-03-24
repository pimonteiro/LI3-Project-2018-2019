#include <stdio.h>
//#include "interface.h"
#include <string.h>
#include "parser.h"
#include <glib.h>

#define RED "\033[31m"
#define BLUE "\033[34m"
#define GREEN "\033[32m"
#define RESET "\033[0m"


int main(int argc, char *argv[]){
	GPtrArray* test = g_ptr_array_sized_new(1000);
	g_ptr_array_set_free_func(test, xmlFree);
	parse("/home/herulume/Desktop/Users.xml", test, 0);
	xmlChar* s = g_ptr_array_index(test, 2);
	printf("Works! Proof? HERE: %s\n", s);

	g_ptr_array_free(test, TRUE);
}

