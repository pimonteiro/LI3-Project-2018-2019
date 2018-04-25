#include <stdlib.h>
#include "mydate.h"
#include "date.h"

/**
 *  @brief Estrutura das datas, que vai desde milisegundo
 *  até ao ano em causa
 */

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
 *  @brief Função responsável pela criação de uma data
 *  de acordo com as suas componentes
 *  @param milisegundo,segundo,minuto,hora,dia,mes,ano
 *  @return inicialização da data
 */

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
 *  @param d Data
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
 *  @brief Função que liberta as datas
 *  @param d Data
 */
void free_Mydate(MyDate d){
    free(d);
}

/**
 *  @brief Função responsável pela leitura do dia de uma data
 *  @param d Data
 *  @return dia de uma dada data
 */

int get_dia(MyDate d){
    return d->dia;
}

/**
 *  @brief Função responsável pela leitura do mês de uma data
 *  @param d Data
 *  @return mês de uma dada data
 */
int get_mes(MyDate d){
    return d->mes;
}

/**
 *  @brief Função responsável pela leitura do ano de uma data
 *  @param d Data
 *  @return ano de uma dada data
 */
int get_ano(MyDate d){
    return d->ano;
}

/**
 *  @brief Função responsável pela leitura da hora de uma data
 *  @param d Data
 *  @return hora de uma data
 */
int get_hora(MyDate d){
    return d->hora;
}

/**
 *  @brief Função responsável pela leitura dos minutos de uma data
 *  @param d Data
 *  @return minutos de uma data
 */
int get_minuto(MyDate d){
    return d->minuto;
}

/**
 *  @brief Função responsável pela leitura dos segundos de uma data
 *  @param d Data
 *  @return segundos de uma data
 */
int get_segundo(MyDate d){
    return d->segundo;
}

/**
 *  @brief Função responsável pela leitura dos milisegundos de uma data
 *  @param d Data
 *  @return milisegundos de uma data
 */
int get_milisegundo(MyDate d){
    return d->milisegundo;
}

/**
 *  @brief Função auxiliar de compare_dates que
 *  compara 2 inteiros
 *  @param a,b 2 inteiros
 *  @return maior dos 2 inteiros
 */

static int compare(int a, int b){
    return (a > b) - (a < b);
}

/**
 *  @brief Função que é responsável pela comparação entre 2 componentes
 *  @param a Data1,b Data2
 *  @return
 */
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
