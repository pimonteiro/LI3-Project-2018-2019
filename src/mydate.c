#include <stdlib.h>
#include "mydate.h"
#include "date.h"

/**
 *  @brief
 *  @param
 *  @return
 */
/*Estrutura das datas */
struct mydate{
    int milisegundo;
    int segundo;
    int minuto;
    int hora;
    int dia;
    int mes;
    int ano;
};

/**
 *  @brief
 *  @param
 *  @return
 */
/*Função responsável pela criação de uma data */
MyDate create_date(int milisegundo, int segundo, int minuto, int hora, int dia, int mes, int ano){
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

/**
 *  @brief
 *  @param
 *  @return
 */
MyDate create_date_with_teachers_date(Date d){
    MyDate new = malloc(sizeof(struct mydate));
    new->ano = get_year(d);
    new->mes = get_month(d);
    new->dia = get_day(d);
    new->minuto = 0;
    new->hora = 0;
    new->segundo = 0;
    new->milisegundo = 0;

    return new;
}

/**
 *  @brief
 *  @param
 *  @return
 */
/*Função que faz free das datas */
void free_Mydate(MyDate d){
    free(d);
}

/**
 *  @brief
 *  @param
 *  @return
 */
/*As funções que se seguem são responsáveis pelos getters dos elementos das datas */
int get_dia(MyDate d){
    return d->dia;
}

/**
 *  @brief
 *  @param
 *  @return
 */
int get_mes(MyDate d){
    return d->mes;
}

/**
 *  @brief
 *  @param
 *  @return
 */
int get_ano(MyDate d){
    return d->ano;
}

/**
 *  @brief
 *  @param
 *  @return
 */
int get_hora(MyDate d){
    return d->hora;
}


/**
 *  @brief
 *  @param
 *  @return
 */
int get_minuto(MyDate d){
    return d->minuto;
}

/**
 *  @brief
 *  @param
 *  @return
 */
int get_segundo(MyDate d){
    return d->segundo;
}

/**
 *  @brief
 *  @param
 *  @return
 */
int get_milisegundo(MyDate d){
    return d->milisegundo;
}

/**
 *  @brief
 *  @param
 *  @return
 */

static int compare(int a, int b){
    return (a > b) - (a < b);
}

/**
 *  @brief
 *  @param
 *  @return
 */
/*Função que é responsável pela comparação entre 2 datas */
int compare_dates(MyDate a, MyDate b){
    int ano, mes, dia, hora, minuto, segundo, milisegundo;

    ano = compare(get_ano(a), get_ano(b));
    if(ano != 0) return ano;

    mes = compare(get_mes(a), get_mes(b));
    if(mes != 0) return mes;

    dia = compare(get_dia(a), get_dia(b));
    if(dia != 0) return dia;

    hora = compare(get_hora(a), get_hora(b));
    if(hora != 0) return hora;

    minuto = compare(get_minuto(a), get_minuto(b));
    if(minuto != 0) return minuto;

    segundo = compare(get_segundo(a), get_segundo(b));
    if(segundo != 0) return segundo;

    milisegundo = compare(get_milisegundo(a), get_milisegundo(b));
    if(milisegundo != 0) return milisegundo;


    return 0;
}
