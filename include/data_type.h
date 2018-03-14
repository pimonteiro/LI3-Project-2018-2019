#include "date.h"
#include <sys/types.h>
#include <glib.h>
typedef struct profile {
    char* about_me;
    size_t id;
    char* name;
    long int reputation;

    GArray *id_questions;
    GArray *id_awnsers;
} *PROFILE;

typedef GHashTable* UserHash;

typedef struct answer {
    size_t id;   //guardamos o id do pai? compensa?
    Date creationDate;
    ssize_t score;
    // TODO TAGS?
} *ANSWER; // TUDO

typedef struct question {
    size_t id;
    char* title;
    // TODO TAGS?
    size_t owner_id;
} *QUESTION;


typedef struct question_answer {
    QUESTION* question;
    GArray *answers;
    Date start;
    Date end;
    size_t n_answer;
} *QUESTION_ANSWER;
