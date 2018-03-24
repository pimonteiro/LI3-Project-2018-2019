#include "main_struct.h"
#include "profile.h"
#include "posts.h"
#include "date.h"
#include <sys/types.h>
#include <glib.h>
#include <stdlib.h>

struct  TCD_community{
	GPtrArray* profiles; //PtrArray que funcs like hashtable :D
	
	GHashTable * posts; //Hash posts por id TODO

	GPtrArray* data_answers;
	GPtrArray* data_posts; 
};

guint hash_func(gconstpointer key){
	return *((guint*) key);
}

gboolean key_equal_func(gconstpointer a, gconstpointer b){
	guint* tmp_a = (guint*) a;
	guint aux_a  = *tmp_a;

	guint* tmp_b = (guint*) b;
	guint aux_b  = *tmp_b;

	if ((aux_a )== (aux_b)) return TRUE;
	else return FALSE;
}


void value_destroy_func_post(gpointer value){
	POST tmp = (POST)value;
	free_profile(tmp);
}

TAD_community create_main_struct(){
	TAD_community m = malloc(sizeof(struct TCD_community));
	
	m->profiles = g_ptr_array_sized_new(500000);
	g_ptr_array_set_free_func(m->profiles, free_profile);


	m->data_posts = g_ptr_array_sized_new(10000);
	g_ptr_array_set_free_func(m->data_posts, free_post);
	
	
	m->data_answers = g_ptr_array_sized_new(10000);
	g_ptr_array_set_free_func(m->data_answers, free_answer);


	m->posts = g_hash_table_new_full(hash_func, key_equal_func, NULL, value_destroy_func_post);

	return m;
}
