#include <stdio.h>
//#include "interface.h" //por comment
#include <string.h>
#include "parser.h"
#include <glib.h>

#define RED "\033[31m"
#define BLUE "\033[34m"
#define GREEN "\033[32m"
#define RESET "\033[0m"


/*#include "profile.h"
#include "question.h"
*/
int main(int argc, char *argv[]){
	GPtrArray* test = g_ptr_array_sized_new(1000);
	g_ptr_array_set_free_func(test, xmlFree);
	parse("/home/herulume/Desktop/Users.xml", test, 0);
	xmlChar* s = g_ptr_array_index(test, 2);
	printf("Works! Proof? HERE: %s\n", s);

	g_ptr_array_free(test, TRUE);


/*	PROFILE a = create_profile("im sick, get it?", 1, "Filipe Monteiro", 999, 10, 7);
	PROFILE b = create_profile("fuck life and li3?", 100, "Pitagoras", -10, 5, 3);

	setId_profile(a, 2);
	printf("%d\n", getReputation_profile(b));

	free_profile(a);
	free_profile(b);

	Date data1 = createDate(10, 2, 2018);

	GArray* new1 = g_array_new(FALSE, FALSE, sizeof(size_t));


	QUESTION c = create_question(1000, "Hack Linux", 1, data1, data1, 3, new1);

	int x[2] = {150,200};
	g_array_append_vals(new1, &x, 2);
	//g_array_append_val(new1, 200);

	setAnswers_array(c, new1);

	add_answers_array(c, 250);

	free_question(c);	*/
	return 0;
}

