#ifndef __MAIN_STRUCT_H__
#define __MAIN_STRUCT_H__

#include <glib.h>
#include "tardis.h"
#include "profile.h"
#include "mydate.h"

typedef struct TCD_community * TAD_community;


TAD_community create_main_struct();
GHashTable* getProfiles_TAD(TAD_community com);
GHashTable* getPosts_TAD(TAD_community com);
GHashTable* getTags_TAD(TAD_community com);
TARDIS getTARDIS_TAD(TAD_community com);
TAD_community init();
void insertProfile_TAD(TAD_community com, PROFILE p, long id);
void insertQuestion_TAD(TAD_community com, QUESTION q, long id, long owner_id, POST p, MyDate start);
void insertAnswer_TAD(TAD_community com, ANSWER a, long id, long owner_id, long parent_id, POST p, MyDate start);
PROFILE getProfile_TAD(TAD_community com, long id);
POST getProfile_TAD(TAD_community com, long id);
GSequence* getFromToF_TAD(TAD_community com, MyDate inicio, MyDate fim, int type, GCompareDataFunc f);

#endif //__MAIN_STRUCT_H__
