package engine;

import common.Exceptions.NoPostFoundException;
import common.Exceptions.NoProfileFoundException;
import common.Pair;

public class Query1 {


    /**
     * @brief Metodo auxiliar que acede á informação de uma Question.
     * @param com Estrutura com os dados
     * @param q Question a analisar
     * @return Par contendo a informação
     * @throws NoProfileFoundException Caso já nao exista o utilizador no banco de dados.
     */
    private static Pair<String,String> get_info_from_post(Main_Struct com, Question q) throws NoProfileFoundException{
        String titulo = q.getTitle();
        String name;

        long owner_id = q.getOwner_id();
        Profile p = com.getProfile(owner_id);
        name = p.getName();

        return new Pair<>(titulo, name);

    }

    /**
     * @brief Retorna o titulo de um dado post e o nome do seu autor.
     * Caso o ID pertença a uma Question, acede diretamente á informaçáo, caso contrário procura a Question a que pertence
     * a reposta continua normalmente.
     * @param com Estrutura com os dados
     * @param id ID do Post
     * @return Par contendo o titulo do post e o nome do utilizador.
     * @throws NoPostFoundException Caso nao existe um Post com este ID.
     * @throws NoProfileFoundException Caso já nao exista o utilizador no banco de dados.
     */
    static Pair<String,String> info_from_post(Main_Struct com, long id) throws NoPostFoundException, NoProfileFoundException{
        Post p = com.getPost(id);
        Pair<String,String> ret;
        if(p instanceof Question){
            ret = get_info_from_post(com, (Question) p);
        }else{
            long parent_id = ((Answer) p).getParent_id();
            Question q = (Question) com.getPost(parent_id);
            ret = get_info_from_post(com, q);
        }
        System.out.println(ret);
        return ret;
    }
}
