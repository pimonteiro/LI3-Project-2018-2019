package common.Comparators;

import engine.Question;

import java.util.Comparator;

public class AnswerCountComparator implements Comparator<Question> {

    public int compare(Question q1, Question q2){
        return (int) (q2.getN_answers() - q1.getN_answers());
    }
}
