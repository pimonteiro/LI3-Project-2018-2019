#include <stdlib.h>
#include "mydate.h"

struct mydate {
  int milisegundo;
  int segundo;
  int minuto;
  int hora;
  int dia;
  int mes;
  int ano;
};

MyDate create_date(int milisegundo, int segundo, int minuto, int hora, int dia, int mes, int ano) {
    MyDate d = malloc(sizeof(struct mydate));
    d->milisegundo = milisegundo;
    d->segundo = segundo;
    d->minuto = minuto;
    d->hora = hora;
    d->dia = dia;
    d->mes = mes;
    d->ano = ano;


    return d;
}

int get_dia(MyDate d) {
    return d->dia;
}

int get_mes(MyDate d) {
    return d->mes;
}

int get_ano(MyDate d) {
    return d->ano;
}

int get_hora(MyDate d) {
    return d->hora;
}


int get_minuto(MyDate d) {
    return d->minuto;
}

int get_segundo(MyDate d) {
    return d->segundo;
}


int get_milisegundo(MyDate d) {
    return d->milisegundo;
}

void free_Mydate(MyDate d) {
    free(d);
}
