#ifndef __PROFILE_H__
#define __PROFILE_H__

#include <stdlib.h>
#include <glib.h>
#include <string.h>

typedef struct profile * PROFILE;

PROFILE create_profile(char * my_about, size_t my_id, char * my_name, ssize_t my_reputation);
void free_profile(void* d);
char* getAboutMe_profile(PROFILE d);
size_t getId_profile(PROFILE d);
char* getName_profile(PROFILE d);
ssize_t getReputation_profile(PROFILE d);
GArray* getId_answers_array_profile(PROFILE d);
void setAboutme_profile(PROFILE d, char * my_about);
void setId_profile(PROFILE d, size_t my_id);
void setName_profile(PROFILE d, char * my_name);
void setReputation_profile(PROFILE d, ssize_t my_reputation);
void setId_answers_array_profile(PROFILE d, GArray* my_id_answers);

void profile_add_answers_array(PROFILE d, size_t id);
#endif /* __PROFILE_H__ */
