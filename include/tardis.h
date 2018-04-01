#ifndef __TARDIS_H__
#define __TARDIS_H__

#include <glib.h>
#include "date.h"
#include "question.h"

typedef struct tardis * TARDIS;

TARDIS lading_tardis();
void takeOf_tardis(void* sexy);
void insertQuestion(TARDIS m, QUESTION q, int ano, int mes, int dia);
void insertAnswer(TARDIS m, ANSWER a, int ano, int mes, int dia);
#endif
