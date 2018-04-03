#include <stdio.h>
#include "interface.h" //por comment
#include "main_struct.h"
#include <glib.h>
#include "date.h"
#include "tardis.h"
#include "profile.h"
#define RED "\033[31m"
#define BLUE "\033[34m"
#define GREEN "\033[32m"
#define RESET "\033[0m"


int main(){

    TAD_community cum = init();
    load(cum, "/home/herulume/Desktop");
    long kek = 10;
    PROFILE q = NULL;
    GHashTable* g = getProfiles_TAD(cum);
    q = (PROFILE)g_hash_table_lookup(g, &kek);

    cum = clean(cum);
  	return 0;
}
