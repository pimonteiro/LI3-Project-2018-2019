#ifndef __MAIN_STRUCT_H__
#define __MAIN_STRUCT_H__

#include <glib.h>
#include "tardis.h"

typedef struct TCD_community * TAD_community;

TAD_community create_main_struct();
GHashTable* getProfiles_TAD(TAD_community com);
GHashTable* getPosts_TAD(TAD_community com);
TARDIS getTARDIS_TAD(TAD_community com);
TAD_community init();


#endif //__MAIN_STRUCT_H__
