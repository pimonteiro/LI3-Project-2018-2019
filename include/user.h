#ifndef __USER__
#define __USER__
typedef struct user* USER;
/**
 @brief Função que se segue é responsável pela devolução
* da informação de um perfil e do histórico de posts
* de um utilizador
 @param short_bio informação de perfil,
 @param post_history Lista de Posts de um utilizador
 @return User
*/
USER create_user(char* short_bio, long* post_history);

/**
 @brief Função que se segue é responsável pela devolução
* da biografia de um perfil de um Utilizador
* de um utilizador
 @param u Utilizador
 @return Informação da biografia de um Utilizador
*/
char* get_bio(USER u);

/**
 @brief Função que se segue é responsável pela devolução
* da informação dos últimos 10 posts de um utilizador.Caso
* tenha menos de 10, pôr -1 como padding
 @param u Utilizador
 @return informação de últimos Posts
*/
long* get_10_latest_posts(USER u);

/**
 @brief Função que se segue é responsável pela
*libertação da estrutura do utilizador
 @param u Utilizador
*/
void free_user(USER u);

#endif
