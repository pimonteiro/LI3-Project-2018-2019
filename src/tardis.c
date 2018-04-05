#include "tardis.h"
#include "question.h"
#include "heap.h"
#include <stdlib.h>

struct tardis {
    GPtrArray* year_questions;
    GPtrArray* year_answers;
};



static int cmpDatesQ (const void* a, const void* b){
  int result;

  QUESTION q1 = (QUESTION)a;
  QUESTION q2 = (QUESTION)b;

  MyDate d1 = getCreationDate_question(q1);
  MyDate d2 = getCreationDate_question(q2);

  result = compare_dates(d2, d1);

  return result;
}


static int cmpDatesA (const void* a, const void* b){
  int result;

  ANSWER a1 = (ANSWER)a;
  ANSWER a2 = (ANSWER)b;

  MyDate d1 = getDate_answer(a1);
  MyDate d2 = getDate_answer(a2);

  result = compare_dates(d2, d1);

  return result;
}
void setFree_list(void* l){
    if(l == NULL) return;
    GSList* list = (GSList*)l;
    g_slist_free(list);
}

void setFree_year(void* year_ptrArray){
    if(year_ptrArray == NULL) return;
    GPtrArray* year = (GPtrArray*)year_ptrArray;
    g_ptr_array_free(year, TRUE);
}


TARDIS landing_tardis(){
    TARDIS type40 = malloc(sizeof(struct tardis));

    type40->year_questions = g_ptr_array_new_with_free_func(setFree_year);
    type40->year_answers = g_ptr_array_new_with_free_func(setFree_year);

    g_ptr_array_set_size(type40->year_questions, 10);
    g_ptr_array_set_size(type40->year_answers, 10);

    return type40;
}


void takeOf_tardis(void* sexy){
    TARDIS type40 = (TARDIS)sexy;

    g_ptr_array_free(type40->year_questions, TRUE);
    g_ptr_array_free(type40->year_answers, TRUE);
    free(type40);
}


void insertQuestion(TARDIS m, QUESTION q, int my_ano, int my_mes, int my_dia){
    int index_ano = my_ano - 2008;
    GPtrArray* array_mes = (GPtrArray*)g_ptr_array_index(m->year_questions, index_ano);

    if(array_mes == NULL){
      array_mes = g_ptr_array_new_with_free_func(setFree_list);
      g_ptr_array_set_size(array_mes, 31*12); // assumir que todos os meses tem 31 dias, gap nao é grande
      g_ptr_array_insert(m->year_questions, index_ano, (gpointer)array_mes); // mes // array_mes
    }

    int index_mes = my_dia + (31*(my_mes-1));
    GSList* l =(GSList*)g_ptr_array_index(array_mes, index_mes);
    if(l == NULL){
      l = g_slist_insert_sorted(l, (gpointer)q, cmpDatesQ);
      g_ptr_array_insert(array_mes, (gint)index_mes, (gpointer)l);
    }
    else
      l = g_slist_insert_sorted(l, (gpointer)q, cmpDatesQ);
}

void insertAnswer(TARDIS m, ANSWER a, int ano, int mes, int dia){
    int index_ano = ano - 2008;
    GPtrArray* array_mes = g_ptr_array_index(m->year_answers,index_ano);

    if(array_mes == NULL){
      array_mes =  g_ptr_array_new_with_free_func(setFree_list);
      g_ptr_array_set_size(array_mes, 31*12);
      g_ptr_array_insert(m->year_answers, (gint)index_ano, (gpointer)array_mes);
    }

    int index_mes = dia + (31*(mes-1));
    GSList* l =(GSList*)g_ptr_array_index(array_mes, index_mes);

    if(l == NULL){
      l = g_slist_insert_sorted(l, (gpointer)a, cmpDatesA);
      g_ptr_array_insert(array_mes, (gint)index_mes, (gpointer)l);
    }
    else
      l = g_slist_insert_sorted(l, (gpointer)a, cmpDatesA);
}

GSList* getQUestionHeap(TARDIS m, int ano, int mes, int dia){
    GPtrArray* mesa = (GPtrArray*)g_ptr_array_index(m->year_questions,ano-2008);
    return (GSList*)g_ptr_array_index(mesa, dia+(31*(mes-1)));
}
