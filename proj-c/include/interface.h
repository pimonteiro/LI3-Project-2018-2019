#include "date.h"
#include "pair.h"
#include "list.h"
#include "user.h"

/**
 * @brief Estrutura que armazena a Estrutura Principal
 */

typedef struct TCD_community * TAD_community;

/**
 * @brief Função que inicializa a Estrutura Principal
 * @return Estrutura inicializada
 */

TAD_community init();

/**
 * QUERY0
 *
 * @brief Função que carrega os ficheiros para
 * a Estrutura escolhida
 * @param com Estrutura
 * @param dump_path Diretoria onde se encontram os ficheiros dump
 * @return Estrutura com os ficheiros
 */

TAD_community load(TAD_community com, char* dump_path);

/**
 * QUERY1
 *
 * @brief Dado o Id de um Post vai-se buscá-lo consultando a Hash
Table e verifica-se se é uma Question ou uma Answer. Caso
seja uma Answer obtém-se o Id da Question correspondente.
No fim, é chamada uma função auxiliar que recebe uma
Question e devolve o título e o nome do criador. O nome
é obtido consultando a Hash Table dos Users
 *@param com Estrutura Principal, id ID de um Post
 *@return Par com titulo e nome do user do autor do Post
*/

STR_pair info_from_post(TAD_community com, long id);

/**
 * QUERY2
 *
 * @brief Todos os Users são percorridos e é feito um insertion sort
num array com N+1 elementos tendo por base o número
de Posts. No fim removemos o elemento N+1.
 * @param com Estrutura Principal, N número Utilizadores
 * @return LONG_list com os N utilizadores com mais Posts
 */

LONG_list top_most_active(TAD_community com, int N);

/**
 * QUERY3
 *
 * @brief A TARDIS é percorrida duas vezes dentro desses intervalos
de tempo, uma para cada tipo de Post. No fim é visto o
tamanho das GSequence e é feito o return
 * @param com Estrutura Principal
 * @param begin Data de começo
 * @param end Data de desfecho
 * @return LONG_pair correspondente aos Posts(questões e respostas)
 */

LONG_pair total_posts(TAD_community com, Date begin, Date end);

/**
 * QUERY4
 *
 * @brief A TARDIS é percorrida entre as datas, percorre-se as tags
de cada Question à procura da tag e se existir é posta num
array.
 * @param com Estrutura Principal, tag Tags das questões
 * @param begin Data de começo, end Data de desfecho
 * @return LONG_list com as tags de questões
 */

LONG_list questions_with_tag(TAD_community com, char* tag, Date begin, Date end);

/**
 * QUERY5
 *
 * @brief Dado o ID de um User obtém-se o seu perfil. Do perfil con-
seguimos a short bio e ordenamos a GSequence inversamente
e tiramos os 10 primeiros.
 * @param com Estrutura Principal, id ID do user
 * @return USER com informação do perfil e ID dos últimos 10 posts
 */

USER get_user_info(TAD_community com, long id);

/**
 * QUERY6
 *
 * @brief A TARDIS é percorrida entre as datas dadas e devolve uma
GSequence ordenada por score, que é convertida para um array
com N IDs.
 * @param com Estrutura Principal, N Número de respostas
 * @param begin Data de começo,end Data de desfecho
 * @return LONG_list com os IDs das respostas com mais votos
 */

LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end);

/**
 * QUERY7
 *
 * @brief A TARDIS é percorrida entre as datas dadas e devolve uma
GSequence ordenada por número de respostas.
 * @param com Estrutura Principal, N Número de questões
 * @param begin Data de começo,end Data de desfecho
 * @return LONG_list com os IDs das N perguntas com mais respostas
 */

LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end);

/**
 * QUERY8
 *
 * @brief A TARDIS é percorrida entre as datas dadas e devolve uma
GSequence ordenada inversamente por datas. É feito um for
each na GSquence que verifica se contém a palavra e em caso
afirmativo é guardado o Id
 * @param com Estrutura Principal, word Palavra que se quer ver se encontra
 * nos titulos das questões, N Número de questões
 * @return LONG_list com os IDs das N perguntas que contenham essa palavra
 */

LONG_list contains_word(TAD_community com, char* word, int N);

/**
 * QUERY9
 *
 * @brief Dados os Ids dos dois utilizadores, vê-se qual dos dois têm
menos Posts consultando a GSequence. No User com menos
Posts percorre-se a GSquence por ordem cronológica inversa
e em cada Post verifica-se se o outro User participa na thread.
 * @param com Estrutura Principal,id1 ID do 1ºUtilizador
 * @param id2 ID do 2ºUtilizador, N Número de perguntas
 * @return LONG_list com N perguntas em que participaram os 2 utilizadores
 */

LONG_list both_participated(TAD_community com, long id1, long id2, int N);

/**
 * QUERY10
 *
 * @brief Dado o Id consulta-se o GArray com as respostas e para
cada aplica-se a fórmula dada.
 * @param com Estrutura Principal, id ID da pergunta
 * @return long com a melhor resposta depois de aplicada
 * a fórmula matemática (Scr×0.45)+(Rep×0.25)+(V ot×0.2)+(Comt×0.1)
 */

long better_answer(TAD_community com, long id);

/**
 * QUERY11
 *
 *@brief Obtemos os Top N Users. Percorremos a TARDIS entre das
datas dadas e filtramos as Questions que não foram feitas por
nenhum dos top Users. Finalmente as Questions são percor-
ridas, as tags removidas e processadas. É criado um array de
correspondência para a Tags que sempre é encontrada dada
tag é incrementado numa unidade. No fim verificamos nos N
indices com maiores elementos e fazemos a correspondência
inversa.
 *@param com Estrutura Principal, N Número de tags
 *@return LONG_list com as tags mais usadas pelos Utilizadores
 com melhor reputação
 */

LONG_list most_used_best_rep(TAD_community com, int N, Date begin, Date end);

/**
 *@brief Função que trata de apagar
 a Estrutura Principal
 *@param com Estrutura
 *@return libertação da Estrutura
 */

TAD_community clean(TAD_community com);
