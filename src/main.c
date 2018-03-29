#include <stdio.h>
//#include "interface.h" //por comment
#include <string.h>
#include "parser.h"
#include "profile.h"
#include "question.h"
#include <glib.h>

#define RED "\033[31m"
#define BLUE "\033[34m"
#define GREEN "\033[32m"
#define RESET "\033[0m"


/*#include "profile.h"
#include "question.h"
*/
int main(int argc, char *argv[]){

  GPtrArray* test = g_ptr_array_sized_new(500000);
	//g_ptr_array_set_free_func(test, free_profile);
   multiParse("/home/herulume/Desktop/", test);
  //parse("/home/herulume/Desktop/Users.xml", test, 0);
  printf("%s%d data units.\n%s", GREEN, test->len, RED);
  //g_ptr_array_free(test, TRUE);
  return 0;

 /*GHashTable* table = g_hash_table_new_full(g_int64_hash, g_int64_equal, g_free, free_profile);
  parse("/home/herulume/Desktop/Users.xml", table, 0);
  printf("%d cabroes foram inseridos", g_hash_table_size(table));
  g_hash_table_destroy(table);*/
  return 0;
}

