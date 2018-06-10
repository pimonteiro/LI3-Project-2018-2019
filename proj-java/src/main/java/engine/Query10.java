package engine;

import common.NoPostFoundException;
import common.NoProfileFoundException;
import common.Pair;
import common.PostIsNotOfRightTypeException;

import java.util.Collection;
import java.util.Iterator;

public class Query10 {

    //Calcula o score de uma resposta
    private static double calculate_score(Profile p, Answer a){
        return (a.getScore() * 0.65) + (p.getReputation() * 0.25) + (a.getN_comments() * 0.1);
    }


    public static long betterAnswer(Main_Struct com, long id) throws NoPostFoundException, PostIsNotOfRightTypeException, NoProfileFoundException{
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
