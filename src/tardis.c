#include "tardis.h"
#include "question.h"
#include "heap.h"
#include <stdlib.h>

struct tardis {
    GPtrArray* year_questions;
    GPtrArray* year_answers;
};

int cmpScore (void* a, void* b){
    QUESTION q1 = (QUESTION)a;
    QUESTION q2 = (QUESTION)b;

    ssize_t score1 = getScore_question(q1);
    ssize_t score2 = getScore_question(q2);

    if(score1 > score2) return 1;
    if(score1 < score2) return -1;
    return 0;
}

// Month/day array is made of HEAPS
void setFree_month(void * month_ptrArray){
    GPtrArray* month = (GPtrArray*)month_ptrArray;
    g_ptr_array_set_free_func(month, free_heap);
}

// Year array is made of gPtrArray
void setFree_year(void * year_ptrArray){
    GPtrArray* year = (GPtrArray*)year_ptrArray;
    g_ptr_array_set_free_func(year, setFree_month);
}


TARDIS lading_tardis(){
    TARDIS type40 = malloc(sizeof(struct tardis));

    type40->year_questions = g_ptr_array_new_full(10, setFree_year);
    type40->year_answers = g_ptr_array_new_full(10, setFree_year);

    //g_ptr_array_set_size(type40->year_questions, 10);
    //g_ptr_array_set_size(type40->year_answers, 10);

    return type40;
}


void takeOf_tardis(void* sexy){
    TARDIS type40 = (TARDIS)sexy;

    g_ptr_array_free(type40->year_questions, TRUE);
    g_ptr_array_free(type40->year_answers, TRUE);

    free(type40);
}


void insertQuestion(TARDIS m, QUESTION q, int ano, int mes, int dia){

    //ANOS
    int index_ano = ano - 2008;
    GPtrArray* array_mes = NULL;
    array_mes = g_ptr_array_index(m->year_questions,index_ano);

    // ACEDER OS MESES DIAS
    if(array_mes == NULL){
      GPtrArray* mes = g_ptr_array_new_with_free_func(setFree_month);
      g_ptr_array_set_size(mes, 31*12); // assumir que todos os meses tem 31 dias, gap nao é grande
      g_ptr_array_insert(m->year_questions, (gint)index_ano, (gpointer)mes);
      array_mes = mes;
    }

    // MESES E DIAS
    int index_mes = dia + (31*mes);
    HEAP h = NULL;
    h = g_ptr_array_index(array_mes, index_mes);

    // ACEDER A HEAP POR SCORE
    if(h == NULL){
        HEAP heap_tmp = initHeap(1024, cmpScore);
        g_ptr_array_insert(array_mes, (gint)index_mes, (gpointer)heap_tmp);
        h = heap_tmp;
    }

    // FINALMENTE
    insertHeap(h, q);
}

void insertAnswer(TARDIS m, ANSWER a, int ano, int mes, int dia){

    //ANOS
    int index_ano = ano - 2008;
    GPtrArray* array_mes = NULL;
    array_mes = g_ptr_array_index(m->year_answers,index_ano);

    // ACEDER OS MESES DIAS
    if(array_mes == NULL){
      GPtrArray* mes =  g_ptr_array_new_with_free_func(setFree_month);
      g_ptr_array_set_size(mes, 31*12); // assumir que todos os meses tem 31 dias, gap nao é grande
      g_ptr_array_insert(m->year_answers, (gint)index_ano, (gpointer)mes);
      array_mes = mes;
    }

    // MESES E DIAS
    int index_mes = dia + (31*mes);
    HEAP h = NULL;
    h = g_ptr_array_index(array_mes, index_mes);

    // ACEDER A HEAP POR SCORE
    if(h == NULL){
        HEAP heap_tmp = initHeap(1024, cmpScore);
        g_ptr_array_insert(array_mes, (gint)index_mes, (gpointer)heap_tmp);
        h = heap_tmp;
    }

    // FINALMENTE
    insertHeap(h, a);
}
