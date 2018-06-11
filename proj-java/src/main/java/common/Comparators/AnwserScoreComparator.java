package common.Comparators;

import engine.Answer;
import engine.Post;

import java.util.Comparator;

public class AnwserScoreComparator implements Comparator<Answer> {
    public int compare(Answer a1, Answer a2){
        return (int) (a2.getScore() - a1.getScore()); //Ordena por score por ordem decrescente
    }

}
