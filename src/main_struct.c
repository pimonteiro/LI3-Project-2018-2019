#include "main_struct.h"
#include "profile.h"
#include "posts.h"
#include "date.h"
#include <sys/types.h>
#include <glib.h>
#include <stdlib.h>

struct  TCD_community{
	GHashTable * profiles; //Hash users
	GHashTable * posts; //Hash posts por id
	GHashTable * data_posts; //Doubt?
};

guint hash_func(gconstpointer key){
	return *((guint*) key) + 1;
}

gboolean key_equal_func(gconstpointer a, gconstpointer b){
	guint* tmp_a = (guint*) a;
	guint aux_a  = *tmp_a;

	guint* tmp_b = (guint*) b;
	guint aux_b  = *tmp_b;

	if ((aux_a )== (aux_b)) return TRUE;
	else return FALSE;
}

void value_destroy_func_profile(gpointer value){
	free_profile((PROFILE) value);
}

void value_destroy_func_post(gpointer value){
	free_profile((POST) value);
}

TAD_community create_main_struct(){
	TAD_community m = malloc(sizeof(struct TCD_community));
	m->profiles = g_hash_table_new_full(hash_func, key_equal_func, NULL, value_destroy_func_profile);
	m->posts = g_hash_table_new_full(hash_func, key_equal_func, NULL, value_destroy_func_post);

	return m;
}
