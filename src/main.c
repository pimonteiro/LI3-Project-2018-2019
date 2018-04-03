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

    //load(cum, "/home/herulume/Desktop");
    load(cum, "/home/pimonteiro/Documents/XML_DUMPS/dump exemplo/android/android");

    USER a = get_user_info(cum, 20);

    printf("%s\n", get_bio(a));

    return 0;

    long kek = 10;
    PROFILE q = NULL;
    GHashTable* g = getProfiles_TAD(cum);
    q = (PROFILE)g_hash_table_lookup(g, &kek);
    printf("%ld\n", getNposts_profile(q));

    cum = clean(cum);
  	return 0;
}
