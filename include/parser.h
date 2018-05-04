#ifndef __PARSER_H__
#define __PARSER_H__

#include "main_struct.h"

/**
@file parser.h
Ficheiro do parser
*/

/**
 * @brief Função que carrega os ficheiros para
 * a Estrutura escolhida
 * @param com Estrutura
 * @param dump_path Diretoria onde se encontram os ficheiros dump
 * @return Estrutura com os ficheiros carregados
 */

TAD_community load(TAD_community com, char* dump_path);

#endif
