#include "main_struct.h"
#include "profile.h"
#include "date.h"
#include <sys/types.h>
#include <glib.h>

struct  TCD_community{
	GHashTable * profiles; //Hash users
	GHashTable * posts; //Hash posts por id
	GHashTable * data_posts; //Doubt?
}

guint hash_func(gconstpointer key){
	long int* tmp = (long int*) key;
	long int aux  = *tmp;
	return aux + 1;
}

gboolean key_equal_func(gconstpointer a, gconstpointer b){
	long int* tmp_a = (long int*) a;
	long int aux_a  = *tmp_a;

	long int* tmp_b = (long int*) b;
	long int aux_b  = *tmp_b;

	if *aux_a == *aux_b return TRUE;
	else return FALSE;
}

void value_destroy_func_profile(gointer value){
	free_profile((PROFILE) value);
}

void value_destroy_func_post(gointer value){
	free_profile((POST) value);
}

TCD_community create_main_struct(){
	TCD_community m = malloc(sizeof(struct main_struct));
	m->profiles = g_hash_table_new_full(hash_func, key_equal_func, NULL, value_destroy_func_profile);
	m->posts = g_hash_table_new_full(hash_func, key_equal_func, NULL, value_destroy_func_post)
}
