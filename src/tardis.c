#include "tardis.h"
#include <stdlib.h>
#include <glib.h>
#define DIAS_MESES 31*12

struct tardis {
    GSequence*** year_questions;
    GSequence*** year_answers;
    int years;
};



/*static int cmpDatesQ (const void* a, const void* b){
  int result;

  QUESTION q1 = (QUESTION)a;
  QUESTION q2 = (QUESTION)b;

  MyDate d1 = getCreationDate_question(q1);
  MyDate d2 = getCreationDate_question(q2);

  result = compare_dates(d2, d1);

  return result;
}*/


/*static int cmpDatesA (const void* a, const void* b){
  int result;

  ANSWER a1 = (ANSWER)a;
  ANSWER a2 = (ANSWER)b;

  MyDate d1 = getDate_answer(a1);
  MyDate d2 = getDate_answer(a2);

  result = compare_dates(d2, d1);

  return result;
}*/


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

GSequence* getRangeFilter_TARDIS(TARDIS m, MyDate inicio, MyDate fim, int type, GFunc f){
    GSequence* return_value = g_sequence_new(NULL);
    int index_ano_inicio = get_ano(inicio) - 2008;
    int index_mes_inicio = (get_dia(inicio)-1) + (31*(get_mes(inicio)-1));
    int mes_inicio = get_mes(inicio)-1;
    int dia_inicio = get_dia(inicio)-1;

    int index_ano_fim = get_ano(fim) - 2008;
    int index_mes_fim = (get_dia(fim)-1) + (31*(get_mes(fim)-1));
    int mes_fim = get_mes(fim) -1;


    if(index_ano_fim < index_ano_inicio) return NULL;
    if(index_ano_inicio == index_ano_fim && index_mes_fim < index_mes_inicio) return NULL;

    // ano inicio == ano fim // score
    if(index_ano_inicio == index_ano_fim){
      int i = index_mes_inicio;
      while(i != index_mes_fim){
        g_sequence_foreach(m->year_questions[index_ano_inicio][i], g_sequence_prepend, return_value);
        if(dia_inicio < 31) dia_inicio++;
        if(dia_inicio == 31 && mes_inicio < 31) mes_inicio++;
        i = dia_inicio-1 + (31*mes_inicio-1);
      }
    }

    return return_value;
}
