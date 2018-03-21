#include "main_struct.h"
#include "profile.h"
#include "date.h"
#include <sys/types.h>
#include <glib.h>

struct  TCD_community{
	GHashTable * users; //Hash users
	GHashTable * posts; //Hash posts por id
	GHashTable * data_posts; //Doubt?
}

TCD_community create_main_struct(){
	TCD_community m = malloc(sizeof(struct main_struct));
	m->users = g_hash_table_new(g_str_hash, g_str_equal); //How?
}
