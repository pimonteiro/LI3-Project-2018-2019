#ifndef __PROFILE_H__
#define __PROFILE_H__

#include <stdlib.h>
#include <glib.h>
#include <string.h>
#include "post.h"
typedef struct profile* PROFILE;

GPtrArray* getTenPosts_profile(PROFILE p);
PROFILE create_profile(char * my_about, size_t my_id, char * my_name, ssize_t my_reputation);
void free_profile(void* p);

GArray* getId_answers_array_profile(PROFILE p);
char* getAboutMe_profile(PROFILE p);
char* getName_profile(PROFILE p);
size_t getNposts_profile(PROFILE p);
size_t getId_profile(PROFILE p);
ssize_t getReputation_profile(PROFILE p);


void setAboutMe_profile(PROFILE p, char* my_about);
void setId_profile(PROFILE p, size_t my_id);
void setName_profile(PROFILE p, char* my_name);
void setReputation_profile(PROFILE p, ssize_t my_reputation);

void addIdAnswer_profile(PROFILE p, size_t id);
void increaseNposts_profile(PROFILE p);
void insertLastest_profile(PROFILE p, POST post);
#endif /* __PROFILE_H__ */
