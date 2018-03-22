#ifndef __PROFILE_H__
#define __PROFILE_H__

#include <stdlib.h>
#include <glib.h>

typedef struct profile * PROFILE;

PROFILE create_profile(char * my_about, size_t my_id, char * my_name, long int my_reputation, GArray my_avl_posts);
void free_profile(PROFILE d);
char getAboutMe_profile(PROFILE d);
size_t getId_profile(PROFILE d);
size_t getId_profile(PROFILE d);
long int getReputation_profile(PROFILE d);
void setAboutme_profile(PROFILE d, char * my_about);
void setId_profile(PROFILE d, size_t my_id);
void setName_profile(PROFILE d, char * my_name);
void setReputation_profile(PROFILE d, long int my_reputation);


#endif /* __PROFILE_H__ */