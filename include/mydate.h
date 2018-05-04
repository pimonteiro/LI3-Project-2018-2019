#ifndef __MYDATE_H__
#define __MYDATE_H__

#include "date.h"

/**
@file date.h
Ficheiro da class MyDate
*/

/**
 *  @brief Estrutura das datas, que vai desde milisegundo
 *  até ano.
 */
typedef struct mydate* MyDate;

/**
 *  @brief Função responsável pela criação de uma data
 *  de acordo com as suas componentes
 *  @param milisegundo,segundo,minuto,hora,dia,mes,ano
 *  @return inicialização da data
 */
MyDate create_date(int milisegundo, int segundo, int minuto, int hora, int dia, int mes, int ano);

/**
 *  @brief  Função que se segue é responsável
 *  pela criação de uma Data "aleatória" que é pedida em grande
 *  parte das queries
 *  @param d Data
 *  @return Uma Data
 */
MyDate create_date_with_teachers_date(Date d);

/**
 *  @brief Função que liberta as datas
 *  @param d Data
 */
void free_Mydate(MyDate d);

/**
 *  @brief Função responsável pela leitura do dia de uma data
 *  @param d Data
 *  @return dia de uma dada data
 */
int get_dia(MyDate d);

/**
 *  @brief Função responsável pela leitura do mês de uma data
 *  @param d Data
 *  @return mês de uma dada data
 */
int get_mes(MyDate d);

/**
 *  @brief Função responsável pela leitura do ano de uma data
 *  @param d Data
 *  @return ano de uma dada data
 */
int get_ano(MyDate d);

/**
 *  @brief Função responsável pela leitura da hora de uma data
 *  @param d Data
 *  @return hora de uma data
 */
int get_hora(MyDate d);

/**
 *  @brief Função responsável pela leitura dos minutos de uma data
 *  @param d Data
 *  @return minutos de uma data
 */
int get_minuto(MyDate d);

/**
 *  @brief Função responsável pela leitura dos segundos de uma data
 *  @param d Data
 *  @return segundos de uma data
 */
int get_segundo(MyDate d);

/**
 *  @brief Função responsável pela leitura dos milisegundos de uma data
 *  @param d Data
 *  @return milisegundos de uma data
 */
int get_milisegundo(MyDate d);

/**
 *  @brief Função que é responsável pela comparação
 *  das componentes de 2 Datas
 *  @param a Data1,b Data2
 *  @return componente da Data que é mais recente
 */
int compare_dates(MyDate a, MyDate b);

#endif
