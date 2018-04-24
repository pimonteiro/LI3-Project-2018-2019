#ifndef __PROFILE_H__
#define __PROFILE_H__

#include <glib.h>
#include "post.h"

typedef struct profile* PROFILE;


PROFILE create_profile(char* my_about, long my_id, char* my_name, int my_reputation);

void free_profile(void* p);

GSequence* getPosts_profile(PROFILE p);

char* getAboutMe_profile(PROFILE p);

char* getName_profile(PROFILE p);

long getNposts_profile(PROFILE p);

long getId_profile(PROFILE p);

int getReputation_profile(PROFILE p);

void insertLastest_profile(PROFILE p, POST post);

#endif /* __PROFILE_H__ */
