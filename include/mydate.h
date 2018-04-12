#ifndef __MYDATE_H__
#define __MYDATE_H__

#include "date.h"

typedef struct mydate * MyDate;

MyDate create_date(int milisegundo, int segundo, int minuto, int hora, int dia, int mes, int ano);
MyDate create_date_with_teachers_date(Date d);
void free_Mydate(MyDate d);

int get_dia(MyDate d);
int get_mes(MyDate d);
int get_ano(MyDate d);
int get_hora(MyDate d);
int get_minuto(MyDate d);
int get_segunudo(MyDate d);
int get_milisegundo(MyDate d);

int compare_dates(MyDate a, MyDate b);

#endif