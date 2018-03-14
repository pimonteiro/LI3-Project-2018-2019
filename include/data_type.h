typedef struct profile {
    char* about_me;
    size_t id;
    char name[50];
    long int reputation;

} *PROFILE;

typedef GHashTable *UserHash;

typedef struct awnser {
    size_t id;   //guardamos o id do pai? compensa?
    Data creationDate;
    long int score;
    // TODO TAGS?
} AWNSER;

typedef struct question {
    size_t id;
    char title[70];
    // TODO TAGS?
    size_t owner_id;
} *QUESTION;


typedef struct question_awnser {
    QUESTION question;
    GArray *awnsers;  
    DATA init;
    DATA end;
    size_t n_awnser;
} *QUESTION_AWNSER;


