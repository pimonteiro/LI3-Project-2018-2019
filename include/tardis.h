#ifndef __TARDIS_H__
#define __TARDIS_H__

#include <glib.h>
#include "date.h"
#include "question.h"

typedef struct tardis * TARDIS;

TARDIS lading_tardis();
int compare_dates(Date a, Date b);
void insertQuestion(TARDIS m, QUESTION q, int ano, int mes, int dia);
#endif
