#include <stdio.h>
#include "interface.h" //por comment
#include "main_struct.h"
#include <glib.h>
#include "date.h"
#include "tardis.h"

#define RED "\033[31m"
#define BLUE "\033[34m"
#define GREEN "\033[32m"
#define RESET "\033[0m"


int main(int argc, char *argv[]){
    Date a = createDate(16, 5, 1997);
    Date b = createDate(10, 5, 1997);

    printf("\n%d\n", compare_dates(a, b));
    //TAD_community cum = init();
    //load(cum, "/home/herulume/Desktop");
    //printf("%d\n", g_hash_table_size(getProfiles_TAD(cum)));
}

