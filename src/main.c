#include <stdio.h>
//#include "interface.h" //por comment
#include <string.h>
#include "parser.h"
#include "profile.h"
#include "post.h"
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


  GHashTable* table = g_hash_table_new_full(g_int64_hash, g_int64_equal, g_free, free_post);
  parse("/home/herulume/Desktop/Posts.xml", table, 1);
  printf("%d cabroes foram inseridos", g_hash_table_size(table));
  g_hash_table_destroy(table);
  return 0;
}

