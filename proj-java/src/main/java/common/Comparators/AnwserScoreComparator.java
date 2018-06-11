package common.Comparators;

import engine.Answer;

import java.util.Comparator;
/**
 *  @brief Método que dadas 2 respostas compara os seus scores
 *  @param a1,a2 2 respostas distintas
 *  @return Score ordenado decrescente
 */
public class AnwserScoreComparator implements Comparator<Answer> {

    public int compare(Answer a1, Answer a2){
        return (int) (a2.getScore() - a1.getScore()); //Ordena por score por ordem decrescente
    }

}
