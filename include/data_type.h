typedef struct profile {
    char* about_me;
    size_t id;
    char name[50];
    long int reputation;

    GArray *id_questions;
    GArray *id_awnsers;
} *PROFILE;

typedef GHashTable* UserHash;

typedef struct answer {
    size_t id;   //guardamos o id do pai? compensa?
    Data creationDate;
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
    DATA start;
    DATA end;
    size_t n_answer;
} *QUESTION_ANSWER;
