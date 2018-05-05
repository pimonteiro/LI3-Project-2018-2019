#ifndef __TARDIS_H__
#define __TARDIS_H__

#include "mydate.h"
#include <glib.h>

/**
@file tardis.h
Ficheiro da class TARDIS
*/

/**
 *@brief Estrutura que armazena a Tardis.
 Consiste num array de arrays com GSequences
 */

typedef struct tardis* TARDIS;

/**
 * @brief  Função que cria uma tardis com apenas os
 * arrays de anos inicializados com tamanho n_years
 * @param n_years Tamanho anos
 * @return A Tardis correspondente ao tamanho dos anos
 */

TARDIS landing_tardis(int n_years);

/**
 * @brief Função que faz free da Tardis
 * @param t Tardis
 */

void takeOf_tardis(void* t);

/**
 * @brief Função que insere uma questão ou resposta na
 * Tardis, cria o array de meses e dias caso seja a
 * primeira questão/resposta desse alcance temporal
 * @param type40 Estrutura Principal,elem Tardis
 * @param d Data,type 1-Questão e 2-Resposta
*/

void insert_TARDIS(TARDIS type40, void* elem, MyDate d, int type);

/**
 * @brief Função que se segue retorna perguntas ou questões
 * entre 2 datas,organizadas pela ordem que for pedida
 * @param m Estrura,inicio Data de começo
 * @param fim Data de desfecho type 1-Question e 2-Resposta
 * @param f Para organizar segundo o que é pedido
 * (ordem cronológica inversa por exemplo)
 * @return GSequence com perguntas/respostas organizadas
 * pelo que for pedido
 */

GSequence* getRangeFilter_TARDIS(TARDIS m, MyDate inicio, MyDate fim, int type, GCompareDataFunc f);

#endif
