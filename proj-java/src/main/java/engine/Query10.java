package engine;

import common.Exceptions.NoPostFoundException;
import common.Exceptions.NoProfileFoundException;
import common.Exceptions.PostIsNotOfRightTypeException;
import common.Pair;

import java.util.Collection;
import java.util.Iterator;

public class Query10 {

    /**
     * @param p Dono da Answer
     * @param a Answer a ser analisada
     * @return Score da resposta.
     *
     * @brief Calcula o score de uma resposta.
     */

    private static double calculate_score(Profile p, Answer a){
        return (a.getScore() * 0.65) + (p.getReputation() * 0.25) + (a.getN_comments() * 0.1);
    }


    /**
     * @param com Estrutura com os dados
     * @param id  ID da Question
     * @return ID da resposta com maior score.
     *
     * @throws NoPostFoundException          Caso o post nao exista.
     * @throws PostIsNotOfRightTypeException Caso se peça a resposta mais votada de uma resposta(impossivel acontecer).
     * @throws NoProfileFoundException       Caso o utilizador nao exista.
     * @brief Procura a resposta com maior score de uma dada questao.
     * Percorrendo cada Answer do Post pedido, vamos atualizando um par contendo o score e o ID da resposta com maior
     * score,
     * para no fim retornar o ID nesse par (que será o que tem maior score)
     */

    public static long betterAnswer(Main_Struct com, long id) throws
                                                              NoPostFoundException,
                                                              PostIsNotOfRightTypeException,
                                                              NoProfileFoundException{
        Post p = com.getPost(id);
        if(p instanceof Answer){
            throw new PostIsNotOfRightTypeException("Post não é uma pergunta");
        }

        Question q = (Question) p;
        Collection<Answer> tmp = q.getAnswers().values();
        if(tmp.size() == 0) return -1;
        Iterator<Answer> it = tmp.iterator();

        //Inicializacao dos primeiros valores
        Answer a = it.next();
        double tt = calculate_score(com.getProfile(a.getOwner_id()), a);
        Pair<Double,Long> ret = new Pair<>(tt, a.getId());

        //Passagem pelas respostas todas
        while(it.hasNext()){
            a = it.next();
            tt = calculate_score(com.getProfile(a.getOwner_id()), a);
            if(tt > ret.getFst()){
                ret.setFst(tt);
                ret.setSecond(a.getId());
            }
        }
        return ret.getSnd();
    }
}
