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


// Year array is made of gPtrArray
void setFree_year(void* year_ptrArray){
    if(year_ptrArray == NULL) return;
    GPtrArray* year = (GPtrArray*)year_ptrArray;
 //   g_ptr_array_set_free_func(year, free_heap);
    g_ptr_array_free(year, TRUE);
}


TARDIS lading_tardis(){
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

    //ANOS
    int index_ano = my_ano - 2008;
    GPtrArray* array_mes = NULL;
    array_mes = g_ptr_array_index(m->year_questions,index_ano);
   // void** array_mes = NULL;
    array_mes = g_ptr_array_index(m->year_questions,index_ano);
    // ACEDER OS MESES DIAS
    if(array_mes == NULL){
      array_mes = g_ptr_array_new_with_free_func(free_heap);
       // array_mes = calloc(31*12+1, sizeof(void*));
      g_ptr_array_set_size(array_mes, 31*12); // assumir que todos os meses tem 31 dias, gap nao é grande
      g_ptr_array_insert(m->year_questions, (gint)index_ano, (gpointer)array_mes); // mes // array_mes

     // array_mes = mes;
    }

    // MESES E DIAS
    int index_mes = my_dia + (31*(my_mes-1));
    HEAP h = NULL;
    h = g_ptr_array_index(array_mes, index_mes);
    //h = array_mes[index_mes];

    // ACEDER A HEAP POR SCORE
    if(h == NULL){
        HEAP heap_tmp = initHeap(1024, cmpScore);
       // array_mes[index_mes] = heap_tmp;
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
      GPtrArray* mes =  g_ptr_array_new_with_free_func(free_heap);
      g_ptr_array_set_size(mes, 31*12); // assumir que todos os meses tem 31 dias, gap nao é grande
      g_ptr_array_insert(m->year_answers, (gint)index_ano, (gpointer)mes);
      array_mes = mes;
    }

    // MESES E DIAS
    int index_mes = dia + (31*(mes-1));
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
HEAP getQUestionHeap(TARDIS m, int ano, int mes, int dia){
    GPtrArray* anoA = g_ptr_array_index(m->year_questions,ano-2008);
    return g_ptr_array_index(anoA, 31*(mes-1)+dia);
}
