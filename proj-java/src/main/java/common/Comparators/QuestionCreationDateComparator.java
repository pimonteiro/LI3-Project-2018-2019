package common.Comparators;

import engine.Question;

import java.util.Comparator;

public class QuestionCreationDateComparator implements Comparator<Question> {

    public int compare(Question q1, Question q2){
        return q2.getCreation_date().compareTo(q1.getCreation_date());
    }
}
