#ifndef __DATE_H__
#define __DATE_H__

typedef struct date* Date;

/**
 *  @brief Função responsável pela criação de uma data
 *  de acordo com o dia, mês e ano
 *  @param day Dia,month Mês,year Ano
 *  @return inicialização de uma Data
 */
Date createDate(int day, int month, int year);

/**
 *  @brief Função responsável pela leitura do dia de uma data
 *  @param d Data
 *  @return dia de uma dada data
 */
int get_day(Date d);

/**
 *  @brief Função responsável pela leitura do mês de uma data.
 *  Retorna um valor entre 0 e 11
 *  @param d Data
 *  @return mês de uma dada data
 */
int get_month(Date d);

/**
 *  @brief Função responsável pela leitura do ano de uma data
 *  @param d Data
 *  @return ano de uma dada data
 */
int get_year(Date d);

/**
 *  @brief Função que liberta a data
 *  @param d Data
 */
void free_date(Date d);

#endif
