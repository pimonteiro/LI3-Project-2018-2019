#ifndef __TARDIS_H__
#define __TARDIS_H__

#include "mydate.h"
#include <glib.h>
typedef struct tardis * TARDIS;

TARDIS landing_tardis(int n_years);
void takeOf_tardis(void* sexy);
void insert_TARDIS(TARDIS type40, void* elem, MyDate d, int type);
GSequence* getFromDate_TARDIS(TARDIS m, MyDate d, int type);
#endif
