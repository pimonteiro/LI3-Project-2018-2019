#include "tardis.h"
#include <stdlib.h>

struct tardis {
    GPtrArray* year_questions;
    GPtrArray* year_answers;
};

// Month/day array is made of GLIB TREES
void setFree_month(void * month_ptrArray){
    GPtrArray* month = (GPtrArray*)month_ptrArray;
    g_ptr_array_set_free_func(month, NULL);
}

// Year array is made of gPtrArray
void setFree_year(void * year_ptrArray){
    GPtrArray* year = (GPtrArray*)year_ptrArray;
    g_ptr_array_set_free_func(year, setFree_month);
}


TARDIS lading_tardis(size_t n_years){
    TARDIS type40 = malloc(sizeof(struct tardis));

    type40->year_questions = g_ptr_array_sized_new(n_years);
    type40->year_answers= g_ptr_array_sized_new(n_years);
    g_ptr_array_set_free_func(type40->year_questions, setFree_year);
    g_ptr_array_set_free_func(type40->year_answers, setFree_year);


    return type40;
}


int compare (int a, int b)
{
    __asm__ __volatile__ (
        "sub %1, %0 \n\t"
        "jno 1f \n\t"
        "cmc \n\t"
        "rcr %0 \n\t"
        "1: "
    : "+r"(a)
    : "r"(b)
    : "cc");
    return a;
}


int compare_dates(Date a, Date b){
    int ano, mes, dia;

    ano = compare(get_year(a), get_year(b));
    if(ano != 0) return ano;

    mes = compare(get_month(a), get_month(b));
    if(mes != 0) return mes;

    dia  = compare(get_day(a), get_day(b));
    if(dia != 0) return dia;


    return 0;
}
