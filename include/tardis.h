#ifndef __TARDIS_H__
#define __TARDIS_H__

#include "mydate.h"
#include <glib.h>

typedef struct tardis* TARDIS;

TARDIS landing_tardis(int n_years);

void takeOf_tardis(void* sexy);

void insert_TARDIS(TARDIS type40, void* elem, MyDate d, int type);

GSequence* getRangeFilter_TARDIS(TARDIS m, MyDate inicio, MyDate fim, int type, GCompareDataFunc f);

#endif
