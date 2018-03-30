#ifndef __TARDIS_H__
#define __TARDIS_H__

#include <sys/types.h>
#include <glib.h>
#include "date.h"

typedef struct post * POST;

typedef struct tardis * TARDIS;

TARDIS lading_tardis(size_t n_years);
int compare_dates(Date a, Date b);

#endif
