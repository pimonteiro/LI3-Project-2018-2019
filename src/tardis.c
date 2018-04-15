#include "tardis.h"
#include <assert.h>
#include <glib.h>
#include "question.h"
#define DIAS_MESES 31*12

struct tardis {
    GSequence*** year_questions;
    GSequence*** year_answers;
    int years;
};


TARDIS landing_tardis(int n_years){
    TARDIS type40 = malloc(sizeof(struct tardis));

    type40->years = n_years;
    type40->year_questions = calloc(n_years, sizeof(GSequence**));
    type40->year_answers = calloc(n_years, sizeof(GSequence**));

    return type40;
}


void takeOf_tardis(void* sexy){
    TARDIS type40 = (TARDIS)sexy;
    int i, j;

    for(i=0; i < type40->years; i++){
      if(type40->year_questions[i] != NULL){
        GSequence** array_mes = type40->year_questions[i];
        for(j=0; j < DIAS_MESES; j++){
          if(array_mes[j] != NULL)
          g_sequence_free(array_mes[j]);
        }
      free(array_mes);
      }
    }

    for(i=0; i < type40->years; i++){
      if(type40->year_answers[i] != NULL){
        GSequence** array_mes = type40->year_answers[i];
        for(j=0; j < DIAS_MESES; j++){
          if(array_mes[j] != NULL)
          g_sequence_free(array_mes[j]);
        }
      free(array_mes);
      }
    }


    free(type40->year_questions);
    free(type40->year_answers);
    free(type40);
}


void insert_TARDIS(TARDIS type40, void* elem, MyDate d, int type){
    int index_ano = get_ano(d) - 2008;
    int index_mes = (get_dia(d)-1) + (31*(get_mes(d)-1));


    GSequence** array_mes = NULL;

    if(type == 1){
      array_mes = type40->year_questions[index_ano];
      if(array_mes == NULL){
        array_mes = calloc(DIAS_MESES, sizeof(GSequence*));
        type40->year_questions[index_ano] = array_mes;
      }
    }

    if(type == 2){
      array_mes = type40->year_answers[index_ano];
      if(array_mes == NULL){
        array_mes = calloc(DIAS_MESES, sizeof(GSequence*));
        type40->year_answers[index_ano] = array_mes;
      }
    }


    GSequence* sequence = array_mes[index_mes];
    if(sequence == NULL){
      sequence = g_sequence_new(NULL);
      g_sequence_prepend(sequence, (gpointer)elem);
      array_mes[index_mes] = sequence;
    }
    else{
      g_sequence_prepend(sequence, (gpointer)elem);
    }
}

void prependGSequence_TARDIS(void* elem, void* g){
  if(g == NULL) return;
  gpointer e = (gpointer)elem;
  GSequence* s = (GSequence*)g;
  g_sequence_prepend(s, e);
}

GSequence* getRangeFilter_TARDIS(TARDIS m, MyDate inicio, MyDate fim, int type, GCompareDataFunc f){
    GSequence* sorted = g_sequence_new(NULL);
    GSequence** anos = NULL;
    int index_ano_inicio = get_ano(inicio) - 2008;
    int index_mes_inicio = (get_dia(inicio)-1) + (31*(get_mes(inicio)-1));
    int mes_inicio = get_mes(inicio)-1;
    int dia_inicio = get_dia(inicio)-1;

    int index_ano_fim = get_ano(fim) - 2008;
    int index_mes_fim = (get_dia(fim)-1) + (31*(get_mes(fim)-1));

    if(type == 1)
      anos = m->year_questions[index_ano_inicio];
    if(type == 2)
      anos = m->year_answers[index_ano_inicio];

    assert(index_ano_inicio <= index_ano_fim);
    if(index_ano_inicio == index_ano_fim)
      assert(index_mes_inicio <= index_mes_fim);

    while(index_ano_inicio <= index_ano_fim){
      while(index_mes_inicio <= index_mes_fim){
        if(!anos) break;
        if(anos[index_mes_inicio]){
          g_sequence_foreach(anos[index_mes_inicio], prependGSequence_TARDIS, sorted);
        }
        if(dia_inicio < 31) dia_inicio++;
        if(dia_inicio == 31 && mes_inicio < 12){ ++mes_inicio; dia_inicio = 0; }
        index_mes_inicio = dia_inicio + (31*mes_inicio);
      }
      ++index_ano_inicio;
    }

    if(f != NULL) g_sequence_sort(sorted, f, NULL);
    return sorted;
}
