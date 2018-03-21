#ifndef __DATA_TYPES_H__
#define __DATA_TYPES_H__

#include "date.h"
#include <sys/types.h>
#include <glib.h>

#include "interface.h"
typedef struct profile {
    char* about_me;
    size_t id; // Just in case we change the order
    char* name;
    long int reputation;

    GArray id_questions; // since it's a GArray we can get the size
    GArray id_awnsers; // Same
} *PROFILE;

typedef GHashTable* UserHash;

typedef struct answer {
    size_t id;   //guardamos o id do pai? compensa?
    Date creationDate;
    ssize_t score;
    // TODO TAGS?
} *ANSWER; // TODO

typedef struct question {
    size_t id;
    char* title;
    // TODO TAGS?
    size_t owner_id;
} *QUESTION;


typedef struct question_answer {
    QUESTION* question;
    GArray answers;
    Date start;
    Date end;
    size_t n_answer;
} *QUESTION_ANSWER;


typedef struct TCD_istruct{
  size_t file;
  UserHash users;
  GArray question_awnsers;

} TCD_community;
#endif
